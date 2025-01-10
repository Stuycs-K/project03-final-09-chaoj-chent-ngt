#include "dependencies.h"

void server_connect(int * sockfd, struct sockaddr_in * serverAddr) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(serverAddr, '\0', sizeof(*serverAddr));

    serverAddr -> sin_family = AF_INET;
    serverAddr -> sin_port = htons(PORT);
    serverAddr -> sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(*sockfd, (struct sockaddr*)serverAddr, sizeof(*serverAddr));

    listen(*sockfd, 4);
}

void client_connect(int * clientSocket) {
   struct sockaddr_in * dest_addr = (struct sockaddir_in*)malloc(1*sizeof(struct sockaddr_in));
   *clientSocket = socket(AF_INET, SOCK_STREAM, 0);

   memset(dest_addr, '\0', sizeof(dest_addr[0]));

   dest_addr -> sin_family = AF_INET;
   dest_addr -> sin_port = htons(PORT);
   dest_addr -> sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(*clientSocket, (struct sockaddr*)dest_addr, sizeof(dest_addr[0]));
}

int check_word(char * word, char * typed_word) {
    printf("\n"); // for formatting purposes

    if (strlen(typed_word)-1 > strlen(word)) {
        printf("Too long!");
        return 0;
    } else {
        int correct_status = 1;
        // Check each character of the word and prints w/ appropriate background color.
        for (int i = 0; i < strlen(word); i++) {
            char temp_string[BUFFER_SIZE];
            if (word[i] == typed_word[i]) {
                printf("\033[30;48;5;120m%c\033[0m", word[i]); // black text w/ green background
            } else {
                printf("\033[30;48;5;209m%c\033[0m", word[i]); // black text w/ red background
                correct_status = 0;
            }
        }

        printf(" "); // for formatting purposes

        return correct_status;
    }
}
