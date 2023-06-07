#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define BUFF_LEN 150
#define LOCAL_IP "192.168.1.178"
#define PORT 8080
#define SA struct sockaddr

#include "client.h"


int main()
{
	printf("------- IoT CLIENT APPLICATION -------\n\n");

	// For calculating time that client spends running
	int program_msec = 0;
	clock_t program_before = clock();

	// Client struct initialization
	struct client my_client;
	initialize_client(&my_client);
	
    // Socket creation and verification   
	int sockfd;
    struct sockaddr_in servaddr;
 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else {
        printf("Socket successfully created..\n");
	}

	// Initialize servaddr struct with zeros
    bzero(&servaddr, sizeof(servaddr));
 
    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(LOCAL_IP);
    servaddr.sin_port = htons(PORT);
 
    // Connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed...\n");
        exit(0);
    } else {
		printf("Connected to the server..\n");
	}

	// do-while() loop executes every 10+n ms
	int trigger = 10 + my_client.n;
	int msec = 0;
	int iterations = 0;
	clock_t before = clock();
	char buff[BUFF_LEN];

	// Send n-number to server
	bzero(buff, sizeof(buff));
	sprintf(buff, "%d", my_client.n);
	write(sockfd, buff, sizeof(buff));
	// Send client description to server
	bzero(buff, sizeof(buff));
	sprintf(buff, "%s", my_client.about);
	write(sockfd, buff, sizeof(buff));

	// Send sin()-data to server
	for (int i = 0; i < 100; i++) {
		// Empty sending buffer
		bzero(buff, sizeof(buff));
		float val = my_client.value[i];
		sprintf(buff, "%f", val);
		write(sockfd, buff, sizeof(buff));

		do {
			clock_t difference = clock() - before;
			msec = difference * 1000 / CLOCKS_PER_SEC;
			iterations++;
		} while (msec < trigger);
		msec = 0;
		iterations = 0;
	}

	// Close the socket
    close(sockfd);

	// Calculating time spent
	clock_t program_after = clock() - program_before;
	program_msec = program_after * 1000 / CLOCKS_PER_SEC;
	program_msec *= 100; // scaling

	printf("Client program execution took %d seconds and %d milliseconds!\n",
			program_msec/1000, program_msec%1000);

	return 0;
}
