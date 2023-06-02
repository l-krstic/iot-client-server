#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DESC_MAX_SIZE 150
#define ARRAY_OF_VALUES_SIZE 101
#define MIN_N_VALUE 1
#define MAX_N_VALUE 10
#define DESC_OK       0
#define DESC_NO_INPUT 1
#define DESC_TOO_LONG 2
#define RADIAN_INC_FACTOR 0.0628

typedef struct client
{
	int n;
	char about[DESC_MAX_SIZE];
	float value[ARRAY_OF_VALUES_SIZE];
};

// Initialize client data
void initialize_client(struct client *my_client);

// Get description string about client, from stdin
int get_client_desc(char* prmpt, char* buff, size_t sz);

// Calculate n*sin() value
void calculate_value(struct client *my_client);