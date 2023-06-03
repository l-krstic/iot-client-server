#pragma once

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MAX_THREADS 10
#define MAX_CLIENTS 10
#define MIN_N_VALUE 1
#define MAX_N_VALUE 10
#define LOCAL_IP "192.168.1.178"
#define BUFF_LEN 150
#define PORT 8080
#define SA struct sockaddr



typedef struct server
{
    int num_of_clients;
    int clients[MAX_CLIENTS];
} server;

typedef struct client_args
{
    int client_num;
    int connfd;
    int sockfd;
    struct sockaddr_in cli;
    unsigned int len;
} client_args;


// The function will be executed by all threads
void *thread_func(void *args);

// Concatenate strings
void concatenate_string(char* s, char* s1);