#include "server.h"

#define LOCAL_IP "192.168.1.178"
#define BUFF_LEN 150
#define PORT 8080
#define SA struct sockaddr


int main()
{
	printf("------- IoT SERVER APPLICATION -------\n");

    // Socket create and verification
	int sockfd;
	int connfd;
	unsigned int len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else {
        printf("Socket successfully created..\n");
	}

	// Initilize with zeros
	bzero(&servaddr, sizeof(servaddr));
   
    // Sign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else {
        printf("Socket successfully binded..\n");
	}

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else {
        printf("Server listening..\n");
	}
	len = sizeof(cli);
   



    /*
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed...\n");
        exit(0);
    }
    else {
        printf("Server accept the client...\n");
	}





    // Read client description
    char buff[BUFF_LEN];
    bzero(buff, BUFF_LEN);
    read(connfd, buff, sizeof(buff));
    printf("From client[description]: %s\n", buff);
    // Read client n-number
    bzero(buff, BUFF_LEN);
    read(connfd, buff, sizeof(buff));
    printf("From client[n]: %s\n", buff);
    // Read client sin()-value
    for (int i = 0; i < 100; i++) {
        bzero(buff, BUFF_LEN);
        read(connfd, buff, sizeof(buff));
        printf("From client[value(%i)]: %s\n", i+1, buff);
    }
    */



	// Server struct initialization
	struct server my_server;
    int num_of_clients = -1;
    printf("num_of_clients> ");
    scanf("%d", &num_of_clients);
    while (num_of_clients < MIN_N_VALUE || num_of_clients > MAX_N_VALUE) {
        printf("Invalid value for n, try again...\n");
        printf("n = ");
        scanf("%d", &num_of_clients);
    }
    my_server.num_of_clients = num_of_clients;



    pthread_t thread_id;
    // Create 'num_of_clients' threads
    for (int i = 0; i < num_of_clients; i++)
        pthread_create(&thread_id, NULL, thread_func, (void *)&thread_id);
  
    pthread_exit(NULL);




	// Close the socket
    close(sockfd);

	return 0;
}