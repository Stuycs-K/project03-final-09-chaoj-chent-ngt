#include "dependencies.h"

int main() {
    // allocate memory for dynamic array of pipes
    int subservers = 0;
    // allocate memory for dynamic array of struct player

    int num_ready = 0;

    int sockfd;
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in con_addr;

    server_connect(&sockfd, &serverAddr);

    socklen_t addr_size;

    while (1) {
        // server_setup
        clientSocket = accept(sockfd, (struct sockaddr*)&con_addr, &addr_size);
        pid_t p = fork();

        // create subprocess and pipes between subserver and server

        // subprocess

            // subprocess does handshake

            // read username from client

            // create struct player and populate

            // send struct player to main process

            // copy over int subserver as array_index (shm)

            // increment subserver (shm)


        // main process

            // read struct player and reallocate array of struct players

        // subprocess

            // listen from client for ready

            // increment num_ready (shm)

        // main process

            // stall until num_ready == subservers

            // send a string to all servers

        // subprocess

            // block until read the above string

            // send string to client

            // access total array of leaderboard using shm and send to client

        // while (condition) {
          // after start loop
        // }

        // subprocess

          // send leaderboard to clients


    }
}

void server_connect(int * sockfd, struct sockaddr_in * serverAddr) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(serverAddr, '\0', sizeof(*serverAddr));

    serverAddr -> sin_family = AF_INET;
    serverAddr -> sin_port = htons(PORT);
    serverAddr -> sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(*sockfd, (struct sockaddr*)serverAddr, sizeof(*serverAddr));

    listen(*sockfd, 4);
}