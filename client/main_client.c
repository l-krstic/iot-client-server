#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "client.h"


int main()
{
	printf("------- IoT CLIENT APPLICATION -------\n\n");

	struct client my_client;
	initialize_client(&my_client);

	

	int trigger = 10 + my_client.n; // 10+n ms
	int msec = 0;
	int iterations = 0;
	clock_t before = clock();
	// This loop executes every (10+n)ms
	do {
		clock_t difference = clock() - before;
		msec = difference * 1000 / CLOCKS_PER_SEC;
		iterations++;
	} while (msec < trigger);

	return 0;
}
