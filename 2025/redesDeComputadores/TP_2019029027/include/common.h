#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

// A string do handshake
#define PEER_HANDSHAKE "P2P_HANDSHAKE_SECRET_v1.2"

// Constantes do projeto
#define MAX_CLIENTS 15
#define BUFFER_SIZE 1024

// Estrutura para armazenar dados do sensor no Servidor de Status (SS)
typedef struct {
    char id[11];
    int risk_detected; // 0 ou 1
} SensorStatus;

// Estrutura para armazenar dados de localização no Servidor de Localização (SL)
typedef struct {
    char id[11];
    int location; // -1 ou 1-10
} SensorLocation;


// Função para reportar erros e terminar o programa
void error(const char *msg);

// PROTOCOL

// Estrutura padrão para todas as mensagens da rede
typedef struct {
    int code;
    char sensor_id[11];
    char payload[256];
} ProtocolMessage;

// === MENSAGENS DE CONTROLE ===
#define REQ_CONN_PEER 20
#define RES_CONN_PEER 21
#define REQ_DISC_PEER 22
#define REQ_CONN_SEN  23
#define RES_CONN_SEN  24
#define REQ_DISC_SEN  25

// === MENSAGENS DE DADOS ===
#define REQ_CHECK_ALERT  36
#define RES_CHECK_ALERT  37
#define REQ_SENS_LOC     38
#define RES_SENS_LOC     39
#define REQ_SENS_STATUS  40
#define RES_SENS_STATUS  41
#define REQ_LOC_LIST     42
#define RES_LOC_LIST     43

// === MENSAGENS DE SINCRONIZAÇÃO (Nossa extensão) ===
#define P2P_SYNC_NEW_SENSOR 100
#define P2P_SYNC_ACK        101

// === MENSAGENS DE ERRO E OK ===
#define MSG_OK    0
#define MSG_ERROR 255

// Protótipos das funções do módulo
void create_message_string(char* dest, int code, const char* sensor_id, const char* payload);
int parse_message_string(const char* src, ProtocolMessage* msg);

#endif // COMMON_H