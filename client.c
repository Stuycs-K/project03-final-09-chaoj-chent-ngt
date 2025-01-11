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

    username_setup(&clientSocket);


    // printf("\n");

    // ready_up(&clientSocket);



    // char test_string[BUFFER_SIZE] = "Hello world! Said the program.";
    char string_to_type[256];
    recv(clientSocket, string_to_type, 256, 0);

    printf("String to type: %s\n", string_to_type);

    char * remaining_string = string_to_type;
    char * current_word;
    int typed_words = 0;
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

        typed_words++;
        char to_server_message[300];
        sprintf(to_server_message, "Word %d: %s", typed_words, user_typed_word);
        send(clientSocket, to_server_message, 300, 0);
    }

    printf("\n\nYou have completed the typeracer!\n");

    return 0;
}
