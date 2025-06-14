#include "common.h"

// ===================================================================
// ESTRUTURAS E VARIÁVEIS GLOBAIS
// ===================================================================

// Enum para identificar o tipo de consulta P2P pendente
typedef enum {
    QUERY_TYPE_NONE,
    QUERY_CHECK_FAILURE,
    QUERY_DIAGNOSE
} QueryType;

// Estrutura para guardar o estado de uma consulta que depende de uma resposta do peer
typedef struct {
    QueryType type;
    int original_client_socket; // Socket do cliente que fez o pedido original
    char sensor_id[11];         // ID do sensor a que a query se refere
    char data[256];             // Dados adicionais (ex: a localização para um 'diagnose')
} PendingQuery;

// "Bases de dados" em memória
SensorLocation location_database[MAX_CLIENTS];
SensorStatus status_database[MAX_CLIENTS];
PendingQuery pending_queries[MAX_CLIENTS]; // Array para gerir consultas pendentes
long long next_sensor_id = 2025061301;      // ID inicial para os sensores

// Protótipos das funções do servidor
void setup_listening_socket(int *master_socket, int port);
void attempt_peer_connection(int *peer_socket, const char *peer_ip, int peer_port);
void handle_new_connection(int master_socket, int *client_sockets);
void handle_client_command(int client_socket, const char *raw_buffer, int *peer_socket, int *client_sockets);
void handle_peer_message(int *peer_socket, const char *raw_buffer, int *client_sockets);
void handle_keyboard_input(int *peer_socket);
void initialize_databases();

// ===================================================================
// FUNÇÃO PRINCIPAL (main)
// ===================================================================
int main(int argc, char *argv[]) {
    // Validação dos argumentos de linha de comando
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <IP_peer> <porta_peer> <porta_clientes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Variáveis principais
    int master_socket, peer_socket = -1;
    int client_sockets[MAX_CLIENTS] = {0};
    
    // Inicialização
    initialize_databases();
    setup_listening_socket(&master_socket, atoi(argv[3]));
    attempt_peer_connection(&peer_socket, argv[1], atoi(argv[2]));

    printf("Aguardando conexões...\n");

    // Loop principal de eventos do servidor
    while (1) {
        fd_set read_fds;
        FD_ZERO(&read_fds);

        // Adiciona todos os sockets de interesse ao conjunto 'read_fds'
        FD_SET(STDIN_FILENO, &read_fds);       // Teclado do servidor
        FD_SET(master_socket, &read_fds);      // Novas conexões
        int max_sd = master_socket;

        // Adiciona o socket do peer, se existir
        if (peer_socket != -1) {
            FD_SET(peer_socket, &read_fds);
            if (peer_socket > max_sd) max_sd = peer_socket;
        }

        // Adiciona os sockets dos clientes
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] > 0) {
                FD_SET(client_sockets[i], &read_fds);
                if (client_sockets[i] > max_sd) max_sd = client_sockets[i];
            }
        }

        // Bloqueia e espera por atividade em qualquer um dos sockets monitorizados
        if (select(max_sd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("Erro no select");
        }

        // --- Processa as atividades detetadas ---

        // Atividade no teclado do administrador
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            handle_keyboard_input(&peer_socket);
        }

        // Nova conexão a chegar no socket principal
        if (FD_ISSET(master_socket, &read_fds)) {
            handle_new_connection(master_socket, client_sockets);
        }

        // Mensagem recebida do outro servidor (peer)
        if (peer_socket != -1 && FD_ISSET(peer_socket, &read_fds)) {
            char buffer[BUFFER_SIZE] = {0};
            int valread = read(peer_socket, buffer, sizeof(buffer) - 1);
            if (valread <= 0) {
                printf("Peer desconectou.\n");
                close(peer_socket);
                peer_socket = -1;
            } else {
                buffer[valread] = '\0';
                handle_peer_message(&peer_socket, buffer, client_sockets);
            }
        }

        // Mensagem recebida de um dos sensores/clientes
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];
            if (sd > 0 && FD_ISSET(sd, &read_fds)) {
                char buffer[BUFFER_SIZE] = {0};
                int valread = read(sd, buffer, sizeof(buffer) - 1);
                if (valread <= 0) {
                    printf("Sensor [socket %d] desconectado.\n", sd);
                    client_sockets[i] = 0;
                    close(sd);
                } else {
                    buffer[valread] = '\0';
                    handle_client_command(sd, buffer, &peer_socket, client_sockets);
                }
            }
        }
    }
    return 0;
}

// ===================================================================
// FUNÇÕES DE GESTÃO DE CONEXÕES
// ===================================================================

/**
 * @brief Aceita uma nova conexão e adiciona o seu socket à lista de clientes.
 * A primeira mensagem desta conexão será tratada no loop principal para determinar
 * se é um peer ou um cliente normal.
 */
void handle_new_connection(int master_socket, int *client_sockets) {
    int new_socket = accept(master_socket, NULL, NULL);
    if (new_socket < 0) {
        perror("Accept falhou");
        return;
    }
    printf("Nova conexão recebida [socket %d]\n", new_socket);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == 0) {
            client_sockets[i] = new_socket;
            return;
        }
    }
    printf("Servidor cheio. Rejeitando nova conexão.\n");
    close(new_socket);
}

// ===================================================================
// FUNÇÕES DE PROCESSAMENTO DE MENSAGENS
// ===================================================================

/**
 * @brief Processa uma mensagem recebida de um socket que pode ser um cliente ou um peer.
 * A primeira mensagem (REQ_CONN_PEER) é usada para o handshake.
 */
void handle_client_command(int client_socket, const char *raw_buffer, int *peer_socket, int *client_sockets) {
    ProtocolMessage msg;
    char response_str[BUFFER_SIZE];
    if (parse_message_string(raw_buffer, &msg) != 0) return;

    // --- LÓGICA DE HANDSHAKE P2P ---
    // Se a mensagem for um pedido de conexão de peer, trata-a de forma especial.
    if (msg.code == REQ_CONN_PEER) {
        if (*peer_socket != -1) {
            printf("Aviso: Conexão peer já existente. Rejeitando.\n");
            close(client_socket);
        } else {
            printf("Conexão Peer validada! [socket %d]\n", client_socket);
            *peer_socket = client_socket;
            handle_peer_message(peer_socket, raw_buffer, client_sockets);
        }
        // Remove o socket da lista de clientes, pois agora é o peer.
        for (int i = 0; i < MAX_CLIENTS; i++) { if (client_sockets[i] == client_socket) { client_sockets[i] = 0; break; } }
        return;
    }
    
    printf("Comando do cliente [socket %d]: Code=%d, ID=%s, Payload=%s\n", client_socket, msg.code, msg.sensor_id, msg.payload);

    // --- LÓGICA DE COMANDOS DE CLIENTE (SENSOR) ---
    switch (msg.code) {
        case REQ_CONN_SEN: { // 23
            int added = -1;
            long long new_id_val = next_sensor_id;
            char new_id_str[11];
            sprintf(new_id_str, "%lld", new_id_val);

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (strcmp(location_database[i].id, "0") == 0) {
                    strcpy(location_database[i].id, new_id_str);
                    strcpy(status_database[i].id, new_id_str);
                    added = i;
                    break;
                }
            }
            if (added != -1) {
                create_message_string(response_str, RES_CONN_SEN, new_id_str, "0");
                next_sensor_id++;
            } else {
                create_message_string(response_str, MSG_ERROR, "0", "09");
            }
            send(client_socket, response_str, strlen(response_str), 0);
            break;
        }

        case P2P_SYNC_NEW_SENSOR: { // 100
            int added = 0;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (strcmp(location_database[i].id, "0") == 0) {
                    strcpy(location_database[i].id, msg.sensor_id);
                    strcpy(status_database[i].id, msg.sensor_id);
                    added = 1;
                    break;
                }
            }
            if (added) { create_message_string(response_str, P2P_SYNC_ACK, msg.sensor_id, "");
            } else { create_message_string(response_str, MSG_ERROR, msg.sensor_id, "09"); }
            send(client_socket, response_str, strlen(response_str), 0);
            break;
        }

        case REQ_SENS_LOC: { // 38
            // Se o payload for um número pequeno, é um update. Senão, é uma consulta.
            if (strlen(msg.payload) <= 2 && atoi(msg.payload) > 0) {
                for(int i=0; i<MAX_CLIENTS; ++i) if(strcmp(location_database[i].id, msg.sensor_id) == 0) { location_database[i].location = atoi(msg.payload); break; }
                create_message_string(response_str, MSG_OK, msg.sensor_id, "02");
            } else {
                int found = 0;
                for(int i=0; i<MAX_CLIENTS; ++i) { if(strcmp(location_database[i].id, msg.payload) == 0) { char loc_str[10]; sprintf(loc_str, "%d", location_database[i].location); create_message_string(response_str, RES_SENS_LOC, msg.payload, loc_str); found = 1; break; } }
                if(!found) create_message_string(response_str, MSG_ERROR, msg.payload, "10");
            }
            send(client_socket, response_str, strlen(response_str), 0);
            break;
        }

        case REQ_SENS_STATUS: { // 40
            if (strlen(msg.payload) == 1) { // Update de risco
                for(int i=0; i<MAX_CLIENTS; ++i) if(strcmp(status_database[i].id, msg.sensor_id) == 0) { status_database[i].risk_detected = atoi(msg.payload); break; }
                create_message_string(response_str, MSG_OK, msg.sensor_id, "02");
            } else { // Consulta de status
                int found = 0;
                for(int i=0; i<MAX_CLIENTS; ++i) { if(strcmp(status_database[i].id, msg.payload) == 0) { char risk_str[2]; sprintf(risk_str, "%d", status_database[i].risk_detected); create_message_string(response_str, RES_SENS_STATUS, msg.payload, risk_str); found = 1; break; } }
                if(!found) create_message_string(response_str, MSG_ERROR, msg.payload, "10");
            }
            send(client_socket, response_str, strlen(response_str), 0);
            break;
        }

        case REQ_CHECK_ALERT: { // 36
            int in_risk = 0;
            for(int i=0; i<MAX_CLIENTS; ++i) if(strcmp(status_database[i].id, msg.sensor_id) == 0) { if (status_database[i].risk_detected == 1) in_risk = 1; break; }
            if (in_risk) {
                printf("Sensor %s em risco. A consultar localização ao peer...\n", msg.sensor_id);
                pending_queries[client_socket].type = QUERY_CHECK_FAILURE;
                pending_queries[client_socket].original_client_socket = client_socket;
                strcpy(pending_queries[client_socket].sensor_id, msg.sensor_id);
                create_message_string(response_str, REQ_CHECK_ALERT, msg.sensor_id, "");
                send(*peer_socket, response_str, strlen(response_str), 0);
            } else {
                create_message_string(response_str, MSG_OK, msg.sensor_id, "03");
                send(client_socket, response_str, strlen(response_str), 0);
            }
            break;
        }

        case REQ_LOC_LIST: { // 42
            printf("Pedido de diagnóstico para a localização %s. A consultar o peer...\n", msg.payload);
            pending_queries[client_socket].type = QUERY_DIAGNOSE;
            pending_queries[client_socket].original_client_socket = client_socket;
            strcpy(pending_queries[client_socket].data, msg.payload);
            create_message_string(response_str, REQ_LOC_LIST, msg.sensor_id, msg.payload);
            send(*peer_socket, response_str, strlen(response_str), 0);
            break;
        }

        default:
            create_message_string(response_str, MSG_ERROR, msg.sensor_id, "Comando desconhecido");
            send(client_socket, response_str, strlen(response_str), 0);
            break;
    }
}

void handle_peer_message(int *peer_socket, const char *raw_buffer, int *client_sockets) {
    (void)client_sockets; // Por enquanto não é usado, mas mantém-se para futura extensibilidade
    ProtocolMessage msg; char response_str[BUFFER_SIZE];
    if (parse_message_string(raw_buffer, &msg) != 0) return;
    printf("Mensagem P2P recebida: Code=%d, ID=%s, Payload=%s\n", msg.code, msg.sensor_id, msg.payload);
    
    switch(msg.code) {
        case RES_CONN_PEER:
            printf("Conexão P2P confirmada pelo peer.\n");
            break;

        case REQ_CHECK_ALERT: { // 36 - Recebido pelo SL
            int found = 0;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (strcmp(location_database[i].id, msg.sensor_id) == 0) {
                    char loc_str[10]; sprintf(loc_str, "%d", location_database[i].location);
                    create_message_string(response_str, RES_CHECK_ALERT, msg.sensor_id, loc_str); // 37
                    found = 1; break;
                }
            }
            if (!found) create_message_string(response_str, MSG_ERROR, msg.sensor_id, "10");
            send(*peer_socket, response_str, strlen(response_str), 0);
            break;
        }
        case RES_CHECK_ALERT: { // 37 - Recebido pelo SS
            for(int i = 0; i < MAX_CLIENTS; ++i) {
                if(pending_queries[i].type == QUERY_CHECK_FAILURE && strcmp(pending_queries[i].sensor_id, msg.sensor_id) == 0) {
                    create_message_string(response_str, RES_SENS_STATUS, msg.sensor_id, msg.payload); // 41
                    send(pending_queries[i].original_client_socket, response_str, strlen(response_str), 0);
                    pending_queries[i].type = QUERY_TYPE_NONE;
                    break;
                }
            }
            break;
        }
        case REQ_LOC_LIST: { // 42 - Recebido pelo SL
            int loc = atoi(msg.payload);
            char id_list[256] = ""; int count = 0;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (location_database[i].location == loc) {
                    if (count++ > 0) strcat(id_list, ",");
                    strcat(id_list, location_database[i].id);
                }
            }
            if(count == 0) { create_message_string(response_str, MSG_ERROR, msg.sensor_id, "11"); }
            else { create_message_string(response_str, RES_LOC_LIST, msg.sensor_id, id_list); } // 43
            send(*peer_socket, response_str, strlen(response_str), 0);
            break;
        }
        case RES_LOC_LIST: { // 43 - Recebido pelo SS
            int client_sock = -1;
            char loc_data[10];
            for(int i=0; i<MAX_CLIENTS; ++i) {
                if(pending_queries[i].type == QUERY_DIAGNOSE) {
                    client_sock = pending_queries[i].original_client_socket;
                    strcpy(loc_data, pending_queries[i].data);
                    pending_queries[i].type = QUERY_TYPE_NONE;
                    break;
                }
            }
            if (client_sock != -1) {
                 char final_payload[512] = ""; sprintf(final_payload, "Diagnostico Area %s: ", loc_data);
                 char* saveptr; char* token = strtok_r(msg.payload, ",", &saveptr);
                 while(token != NULL) {
                     for(int j=0; j<MAX_CLIENTS; ++j) {
                         if(strcmp(status_database[j].id, token) == 0) {
                             char info[64]; sprintf(info, "Sensor %s (Risco:%d), ", token, status_database[j].risk_detected);
                             strcat(final_payload, info); break;
                         }
                     }
                     token = strtok_r(NULL, ",", &saveptr);
                 }
                 create_message_string(response_str, MSG_OK, msg.sensor_id, final_payload);
                 send(client_sock, response_str, strlen(response_str), 0);
            }
            break;
        }
    }
}

// ===================================================================
// FUNÇÕES DE SETUP E UTILITÁRIAS
// ===================================================================

void initialize_databases() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        strcpy(location_database[i].id, "0");
        location_database[i].location = -1;
        strcpy(status_database[i].id, "0");
        status_database[i].risk_detected = 0;
        pending_queries[i].type = QUERY_TYPE_NONE;
    }
}
void setup_listening_socket(int *master_socket, int port) {
    struct sockaddr_in address;
    if ((*master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) error("Falha ao criar socket");
    int opt = 1;
    if (setsockopt(*master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) error("setsockopt falhou");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(*master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) error("Bind falhou");
    printf("Servidor ouvindo clientes na porta %d\n", port);
    if (listen(*master_socket, 5) < 0) error("Listen falhou");
}
void attempt_peer_connection(int *peer_socket, const char *peer_ip, int peer_port) {
    int temp_socket;
    if ((temp_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) return;
    struct sockaddr_in peer_addr;
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(peer_port);
    if (inet_pton(AF_INET, peer_ip, &peer_addr.sin_addr) <= 0) return;
    if (connect(temp_socket, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) == 0) {
        char msg_str[BUFFER_SIZE];
        create_message_string(msg_str, REQ_CONN_PEER, "0", "");
        printf("Conectado ao peer em %s:%d. Enviando REQ_CONN_PEER...\n", peer_ip, peer_port);
        send(temp_socket, msg_str, strlen(msg_str), 0);
        *peer_socket = temp_socket;
    } else {
        printf("Nenhum peer encontrado, a aguardar conexões...\n");
        close(temp_socket);
    }
}
void handle_keyboard_input(int *peer_socket) {
    (void)peer_socket; // Apenas para evitar o warning de não usado
}
