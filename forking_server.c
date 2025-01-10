#include "dependencies.h"

// void send_string(int * clientSocket, char * string) {
//     int word_count = 0;
//     char * remaining_string;
//     char * current_word;
//     while (current_word = strsep(&remaining_string, " ")) {
//         send(clientSocket, current_word, 256, 0);
//         word_count++;
//     }
// }

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

    // char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";

    while (1) {
        // create subprocess and pipes between subserver and server
        clientSocket = accept(sockfd, (struct sockaddr*)&con_addr, &addr_size);
        pid_t p = fork();
        // subprocess
        if (p == 0) {
            char username[30];
            recv(clientSocket, username, 30, 0);
            // printf("Received username: %s\n", username);

            struct player * pl = (struct player *)malloc(sizeof(struct player));

            strcpy(pl -> username, username);
            pl -> words = 0;

            char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";
            printf("Sending to client: %s\n", string_to_type);
            send(clientSocket, string_to_type, strlen(string_to_type) + 1, 0);

            char from_client_message[300];
            recv(clientSocket, from_client_message, 300, 0);
            printf("Received from client: %s\n", from_client_message);

            // send_string(&clientSocket, string_to_type);
        }
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

