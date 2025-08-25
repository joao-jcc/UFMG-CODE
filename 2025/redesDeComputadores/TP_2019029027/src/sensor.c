#include "common.h"

// Protótipos das funções do cliente
int connect_to_server(const char *ip, int port);
void print_prompt(const char* sensor_id);
void handle_server_response(const char* raw_buffer, const char* server_name, int ss_socket);
void handle_user_input(int sl_socket, int ss_socket);

// Variáveis globais para guardar o estado do cliente
char my_sensor_id[11] = {0}; // Guarda o ID do próprio sensor após o registo
int is_fully_registered = 0;   // Flag que controla se o sensor pode enviar comandos

// ===================================================================
// FUNÇÃO PRINCIPAL (main)
// ===================================================================
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <IP_servidores> <porta_servidor_status> <porta_servidor_localizacao>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Conecta-se aos dois servidores
    int ss_socket = connect_to_server(argv[1], atoi(argv[2]));
    int sl_socket = connect_to_server(argv[1], atoi(argv[3]));
    int max_fd = (sl_socket > ss_socket) ? sl_socket : ss_socket;

    // Imprime o menu de ajuda
    printf("Cliente pronto. A iniciar o processo de registo...\n");
    printf("--- Comandos Disponiveis ---\n");
    printf("  update_loc <loc>        - Atualiza sua localizacao (1-10).\n");
    printf("  update_risk <0|1>       - Atualiza seu estado de risco (0: normal, 1: risco).\n");
    printf("  locate <ID>             - Consulta localizacao de um sensor.\n");
    printf("  check_status <ID>       - Consulta o estado de risco de um sensor.\n");
    printf("  check_failure           - Verifica o proprio estado e localizacao se houver risco.\n");
    printf("  diagnose <loc>          - Diagnostico completo dos sensores numa area.\n");
    printf("  close                   - Fecha o cliente.\n");
    printf("----------------------------\n");

    // Envia o pedido de registo inicial (Fase 1) para o Servidor de Localização
    char msg_buffer[BUFFER_SIZE];
    create_message_string(msg_buffer, REQ_CONN_SEN, "0", "");
    send(sl_socket, msg_buffer, strlen(msg_buffer), 0);

    // Loop principal de eventos do cliente
    while (1) {
        print_prompt(my_sensor_id);
        
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(sl_socket, &read_fds);
        FD_SET(ss_socket, &read_fds);

        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("Select no cliente falhou");
            break;
        }

        // Verifica se há resposta do Servidor de Status
        if (FD_ISSET(ss_socket, &read_fds)) {
            char buffer[BUFFER_SIZE] = {0};
            if (read(ss_socket, buffer, sizeof(buffer) - 1) <= 0) { printf("\nServidor de Status desconectou.\n"); break; }
            handle_server_response(buffer, "SS", ss_socket);
        }
        
        // Verifica se há resposta do Servidor de Localização
        if (FD_ISSET(sl_socket, &read_fds)) {
            char buffer[BUFFER_SIZE] = {0};
            if (read(sl_socket, buffer, sizeof(buffer) - 1) <= 0) { printf("\nServidor de Localização desconectou.\n"); break; }
            handle_server_response(buffer, "SL", ss_socket);
        }

        // Verifica se há input do teclado
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (!is_fully_registered) {
                printf("\rAguarde, registo em andamento...\n");
                char temp[BUFFER_SIZE]; read(STDIN_FILENO, temp, sizeof(temp)); // Limpa o input
            } else {
                handle_user_input(sl_socket, ss_socket);
            }
        }
    }

    close(sl_socket);
    close(ss_socket);
    return 0;
}

// ===================================================================
// FUNÇÕES DE GESTÃO DE MENSAGENS E INPUT
// ===================================================================

/**
 * @brief Processa e interpreta as respostas recebidas dos servidores.
 */
void handle_server_response(const char* raw_buffer, const char* server_name, int ss_socket) {
    ProtocolMessage msg;
    if (parse_message_string(raw_buffer, &msg) != 0) {
        printf("<< Mensagem mal formada recebida de %s: %s\n", server_name, raw_buffer);
        return;
    }

    printf("\r%*s\r", 80, ""); // Limpa a linha do prompt para uma UI mais limpa

    switch (msg.code) {
        case RES_SENS_STATUS: { // 41
            // Se o payload for longo, é uma consulta de status de outro sensor
            if (strlen(msg.payload) > 2) { 
                 printf("<< Status do sensor %s: %s\n", msg.sensor_id, (atoi(msg.payload) == 1) ? "RISCO" : "NORMAL");
            } else { // Se for curto, é a resposta do check_failure
                int loc = atoi(msg.payload);
                const char* area_nome = "Desconhecida";
                if (loc >= 1 && loc <= 3) area_nome = "Norte";
                else if (loc >= 4 && loc <= 5) area_nome = "Sul";
                else if (loc >= 6 && loc <= 7) area_nome = "Leste";
                else if (loc >= 8 && loc <= 10) area_nome = "Oeste";
                printf("<< Alerta recebido da area: %d (%s)\n", loc, area_nome);
            }
            break;
        }

        case MSG_OK: {
            if(strcmp(msg.payload, "03") == 0) printf("<< Status do sensor: OK (Normal)\n");
            else printf("<< Response (%s): OK (Code: %s)\n", server_name, msg.payload);
            break;
        }

        case RES_CONN_SEN: // 24: Fase 1 do registo concluída
            if (strcmp(server_name, "SL") == 0) {
                strcpy(my_sensor_id, msg.sensor_id);
                char sync_msg_str[BUFFER_SIZE];
                // Inicia a Fase 2: sincroniza com o Servidor de Status
                create_message_string(sync_msg_str, P2P_SYNC_NEW_SENSOR, my_sensor_id, "");
                send(ss_socket, sync_msg_str, strlen(sync_msg_str), 0);
            }
            break;
        
        case P2P_SYNC_ACK: // 101: Fase 2 do registo concluída
            if (strcmp(server_name, "SS") == 0) {
                is_fully_registered = 1;
                printf("Registo completo! Sistema operacional.\n");
            }
            break;
        
        default:
            printf("<< Response (%s): Code=%d, ID=%s, Payload=%s\n", server_name, msg.code, msg.sensor_id, msg.payload);
            break;
    }
}

/**
 * @brief Processa os comandos digitados pelo utilizador.
 */
void handle_user_input(int sl_socket, int ss_socket) {
    char input_buffer[BUFFER_SIZE] = {0};
    if (read(STDIN_FILENO, input_buffer, sizeof(input_buffer)) <= 0) return;
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) == 0) return;
    
    char msg_to_send[BUFFER_SIZE];
    int code = -1;
    char payload[256] = "";
    int target_socket = ss_socket;

    // Mapeia o comando do utilizador para o código de protocolo correto
    if (strcmp(input_buffer, "check_failure") == 0) {
        code = REQ_CHECK_ALERT;
    } else if (strncmp(input_buffer, "update_loc", 10) == 0) {
        int loc; sscanf(input_buffer, "update_loc %d", &loc);
        snprintf(payload, sizeof(payload), "%d", loc);
        code = REQ_SENS_LOC; target_socket = sl_socket;
    } else if (strncmp(input_buffer, "update_risk", 11) == 0) {
        int risk; sscanf(input_buffer, "update_risk %d", &risk);
        snprintf(payload, sizeof(payload), "%d", risk);
        code = REQ_SENS_STATUS; target_socket = ss_socket;
    } else if (strncmp(input_buffer, "locate", 6) == 0) {
        sscanf(input_buffer, "locate %s", payload);
        code = REQ_SENS_LOC; target_socket = sl_socket;
    } else if (strncmp(input_buffer, "check_status", 12) == 0) {
        sscanf(input_buffer, "check_status %s", payload);
        code = REQ_SENS_STATUS; target_socket = ss_socket;
    } else if (strncmp(input_buffer, "diagnose", 8) == 0) {
        sscanf(input_buffer, "diagnose %s", payload);
        code = REQ_LOC_LIST; target_socket = ss_socket;
    } else if (strcmp(input_buffer, "close") == 0) {
        printf("Fechando cliente...\n");
        create_message_string(msg_to_send, REQ_DISC_SEN, my_sensor_id, "");
        send(sl_socket, msg_to_send, strlen(msg_to_send), 0);
        send(ss_socket, msg_to_send, strlen(msg_to_send), 0);
        sleep(1); exit(0); 
    }

    if (code != -1) {
        create_message_string(msg_to_send, code, my_sensor_id, payload);
        send(target_socket, msg_to_send, strlen(msg_to_send), 0);
    } else {
        printf("Comando desconhecido: %s\n", input_buffer);
    }
}

// ===================================================================
// FUNÇÕES DE SETUP E UTILITÁRIAS
// ===================================================================

/**
 * @brief Imprime o prompt do sensor no terminal.
 */
void print_prompt(const char* sensor_id) {
    if (is_fully_registered) { printf("Sensor[%s]> ", sensor_id); }
    else { printf("Sensor[REGISTERING...]> "); }
    fflush(stdout);
}

/**
 * @brief Conecta-se a um servidor.
 */
int connect_to_server(const char *ip, int port) {
    int sockfd; struct sockaddr_in serv_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("Socket falhou");
    serv_addr.sin_family = AF_INET; serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) error("Endereço inválido");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Conexão com a porta %d falhou", port);
        error(error_msg);
    }
    printf("Conectado com sucesso ao servidor na porta %d\n", port);
    return sockfd;
}
