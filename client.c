#include "dependencies.h"

// ESCAPE CODE = \033

int err() {
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
}

int main() {
    // printf("\033[2J\033[1;1H"); // clear screen

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