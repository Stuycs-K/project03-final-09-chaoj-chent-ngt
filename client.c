#include "dependencies.h"

int err() {
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
}

int main() {
    int clientSocket;
    client_connect(&clientSocket);

    char test_string[BUFFER_SIZE] = "Once upon a time, there was a boy.";

    printf("%s\n", test_string);

    char * remaining_string = test_string;
    char * current_word;
    char user_typed_string[BUFFER_SIZE];
    while (current_word = strsep(&remaining_string, " ")) {
        fgets(user_typed_string, BUFFER_SIZE, stdin);

        // ADD CODE TO CHECK IF USER_TYPED_STRING IS EQUAL TO REMOVED WORD

        printf("%s\n", remaining_string);
        printf("%s", user_typed_string);
    }

    return 0;
}

void client_connect(int * clientSocket) {
   struct sockaddr_in * dest_addr = (struct sockaddir_in*)malloc(1*sizeof(struct sockaddr_in));
   *clientSocket = socket(AF_INET, SOCK_STREAM, 0);

   memset(dest_addr, '\0', sizeof(dest_addr[0]));

   dest_addr.sin_family = AF_INET;
   dest_addr.sin_port = htons(PORT);
   dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

   ret = connect(clientSocket, (struct sockaddr*)dest_addr, sizeof(dest_addr[0]));
}
