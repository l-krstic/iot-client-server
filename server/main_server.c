#include "server.h"


int main()
{
	printf("------- IoT SERVER APPLICATION -------\n");

    // For calculating time that client spends running
	int program_msec = 0;
	clock_t program_before = clock();

    // Socket create and verification
	int sockfd = -1;
	int connfd = -1;
	unsigned int len = 0;
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed!\n");
        exit(0);
    }
    else {
        printf("Socket successfully created..\n");
	}

	// Initilize with zeros
	bzero(&servaddr, sizeof(servaddr));
    bzero(&cli, sizeof(cli));
   
    // Sign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed!\n");
        exit(0);
    }
    else {
        printf("Socket successfully binded...\n");
	}

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listening failed!\n");
        exit(0);
    }
    else {
        printf("Server listening...\n");
	}
	len = sizeof(cli);

	// Server struct initialization
	struct server my_server;
    int num_of_clients = -1;
    printf("Number of clients> ");
    scanf("%d", &num_of_clients);
    while (num_of_clients < MIN_N_VALUE || num_of_clients > MAX_N_VALUE) {
        printf("Invalid value for n, try again!\n");
        printf("Number of clients> ");
        scanf("%d", &num_of_clients);
    }
    // Assign number of clients in server struct
    my_server.num_of_clients = num_of_clients;

    // Initialize array of clients n's
    for (int i = 0; i < num_of_clients; i++)
        my_server.clients[i] = i + 1;

    // Create 'num_of_clients' threads
    pthread_t thread_id[MAX_THREADS];
    for (int i = 0; i < num_of_clients; i++) {
        client_args *args = malloc(sizeof *args);
        args->cli = cli;
        args->connfd = connfd;
        args->len = len;
        args->sockfd = sockfd;
        args->client_num = my_server.clients[i];
        
        if(pthread_create(&thread_id[i], NULL, thread_func, args)) {
            free(args);
            printf("Error creating thread number [%d]!\n", i+1);
            goto thread_error;
        }
    }


thread_error:
    // Threads closing
    for (int i = 0; i < num_of_clients; i++)
        pthread_join(thread_id[i], NULL);

	// Close the socket
    close(sockfd);

	// Calculating time spent
	clock_t program_after = clock() - program_before;
	program_msec = program_after * 1000 / CLOCKS_PER_SEC;
	program_msec *= 50; // scaling

	printf("Server program execution took %d seconds and %d milliseconds!\n",
			program_msec/1000, program_msec%1000);


	return 0;
}