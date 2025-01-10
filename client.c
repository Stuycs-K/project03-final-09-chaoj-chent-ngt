#include "dependencies.h"

// ESCAPE CODE = \033

int err() {
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
}

int main() {
    int clientSocket;
    client_connect(&clientSocket);

    printf("\033[2J\033[1;1H"); // clear screen

    printf("Username: ");
    char in[30];
    char username[30];
    fgets(in, 29, stdin);
    sscanf(in, "%[^\n]", username);
    send(clientSocket, username, strlen(username), 0);


    printf("\n");
    char start[30];
    while (strcmp(start, "start\n") != 0) {
        printf("Type 'start' to start: ");
        fgets(start, 29, stdin);
        printf("\n");
    }
    send(clientSocket, "start", 5, 0);



    char test_string[BUFFER_SIZE] = "Hello world! Said the program.";

    char * remaining_string = test_string;
    char * current_word;
    char user_typed_word[BUFFER_SIZE];
    while (current_word = strsep(&remaining_string, " ")) {
        // Prevents printing (null) when remaining_string is NULL (i.e. last word).
        if (remaining_string == NULL) {
            printf("\033[1;31m%s\033[0m\n", current_word);
        } else {
            printf("\033[1;31m%s\033[0m %s\n", current_word, remaining_string); // red, bolded text (use 4;31m if bold doesn't work)
        }

        // Initial prompt for user, without testing.
        printf("Type: %s\n", current_word);
        printf(">> ");
        fgets(user_typed_word, BUFFER_SIZE, stdin);

        // If initial input is incorrect, continue requesting input until correct.
        while (check_word(current_word, user_typed_word) == 0) {
            printf("\n\nIncorrect. Try again.\n");
            printf("Type: %s\n", current_word);
            printf(">> ");
            fgets(user_typed_word, BUFFER_SIZE, stdin);
        }
    }

    printf("\n\nYou have completed the typeracer!\n");

    return 0;
}