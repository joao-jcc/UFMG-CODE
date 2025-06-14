#include "common.h"

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

/**
 * @brief Monta uma string de protocolo formatada a partir dos dados.
 * Formato: "CODE:SENSOR_ID:PAYLOAD\n"
 * @param dest Buffer de destino para a string.
 * @param code Código numérico da mensagem.
 * @param sensor_id ID do sensor (ou "0" se não aplicável).
 * @param payload Dados da mensagem.
 */
void create_message_string(char* dest, int code, const char* sensor_id, const char* payload) {
    // Garante que os campos não são nulos para evitar falhas no snprintf
    const char* id_to_use = (sensor_id == NULL) ? "0" : sensor_id;
    const char* payload_to_use = (payload == NULL) ? "" : payload;
    
    snprintf(dest, 500, "%d:%s:%s\n", code, id_to_use, payload_to_use);
}

/**
 * @brief Extrai os dados de uma string de protocolo para uma struct ProtocolMessage.
 * @param src A string recebida da rede.
 * @param msg Ponteiro para a struct onde os dados serão guardados.
 * @return 0 em sucesso, -1 em falha de parsing.
 */
int parse_message_string(const char* src, ProtocolMessage* msg) {
    char buffer[512];
    strncpy(buffer, src, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char* saveptr;
    
    // 1. Extrai o código (CODE)
    char* token = strtok_r(buffer, ":", &saveptr);
    if (token == NULL) return -1;
    msg->code = atoi(token);

    // 2. Extrai o ID do sensor (SENSOR_ID)
    token = strtok_r(NULL, ":", &saveptr);
    if (token == NULL) return -1;
    strncpy(msg->sensor_id, token, sizeof(msg->sensor_id) - 1);
    msg->sensor_id[sizeof(msg->sensor_id) - 1] = '\0';
    
    // 3. Extrai o payload (PAYLOAD)
    token = strtok_r(NULL, "\n", &saveptr); // Lê até à quebra de linha
    if (token == NULL) {
        // Payload pode ser vazio
        msg->payload[0] = '\0';
    } else {
        strncpy(msg->payload, token, sizeof(msg->payload) - 1);
        msg->payload[sizeof(msg->payload) - 1] = '\0';
    }

    return 0;
}
