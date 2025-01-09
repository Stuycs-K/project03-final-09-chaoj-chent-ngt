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


#define PORT 80
#define BUFFER_SIZE 256

void client_connect(int * clientSocket);
void server_connect(int * serverSocket);

int err();
