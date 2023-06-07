#include "server.h"



void *thread_func(void *args)
{
    // Store values argument passed to this thread
    client_args *actual_args = args;
    int my_id = actual_args->client_num;
    int connfd = actual_args->connfd;
    int sockfd = actual_args->sockfd;
    struct sockaddr_in cli = actual_args->cli;
    unsigned int len = actual_args->len;

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed!\n");
        exit(0);
    }
    else {
        printf("Server accept the client %d...\n", my_id);
	}
    
    // Making file name 
    char *filename_1 = "output/client_";
    int length = snprintf(NULL, 0, "%d", my_id);
    char *filename_2 = malloc(length);
    snprintf(filename_2, length + 1, "%d", my_id);
    char *filename = malloc(14 + length + 5 + 1);
    char *filename_3 = ".txt";

    concatenate_string(filename, filename_1);
    concatenate_string(filename, filename_2);
    concatenate_string(filename, filename_3);

    // Open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file [%s]!\n", filename);
        return NULL;
    }

    char buff[BUFF_LEN];
    // Write client's n-number
    bzero(buff, BUFF_LEN);
    read(connfd, buff, sizeof(buff));
    fprintf(fp, "Num: [%s], desc: ", buff);
    // Write client description in file
    bzero(buff, BUFF_LEN);
    read(connfd, buff, sizeof(buff));
    fprintf(fp, "[%s]\n", buff);
    // Write client's sin()-values
    for (int i = 0; i < 100; i++) {
        bzero(buff, BUFF_LEN);
        read(connfd, buff, sizeof(buff));
        fprintf(fp, "%s\n", buff);
    }
    float last_value = 0.000000;
    bzero(buff, BUFF_LEN);
    sprintf(buff, "%f", last_value);
    fprintf(fp, "%s", buff);

    printf("Data writen to client %s, in file: %s\n",
            filename_2, filename);

    // Close the file
    fclose(fp);
    // Deallocate resources
    free(filename_2);
    free(filename);

    return NULL;
}

void concatenate_string(char* s, char* s1)
{
    int i = 0;
    int j = strlen(s);
 
    for (i = 0; s1[i] != '\0'; i++)
        s[i + j] = s1[i];
    s[i + j] = '\0';

    return;
}