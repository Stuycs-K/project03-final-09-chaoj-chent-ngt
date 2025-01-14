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
#include <signal.h>
#include <sys/types.h>
#include <netdb.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H
#define PORT "9876"
#define BUFFER_SIZE 256
#define READ 0
#define WRITE 1
#define intkey 239248239

struct player {
    char username[30];
    int words;
};

void client_connect(int * sd);
void server_connect(int * sd);

int err();

int check_word(char * word, char * typed_word);

void username_setup(int * clientSocket);
void ready_up(int * clientSocket);

void send_string(int * clientSocket);

int len(char * string);
#endif
