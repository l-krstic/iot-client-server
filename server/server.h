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
#define MIN_N_VALUE 1
#define MAX_N_VALUE 10


typedef struct server
{
    int num_of_clients;
} server;


// The function will be executed by all threads
void *thread_func(void *thread_param);