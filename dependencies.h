#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H
#define PORT 8080
#define BUFFER_SIZE 256

struct player {
    char username[30];
    int words;
};

void client_connect(int * clientSocket);
void server_connect(int * sockfd, struct sockaddr_in * serverAddr);

int err();

int check_word(char * word, char * typed_word);


#endif