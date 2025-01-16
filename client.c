#include "dependencies.h"

// ESCAPE CODE = \033

int err() {
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
}



int main() {
    int sd;
    client_connect(&sd);


    printf("\033[2J\033[1;1H"); // clear screen
    username_setup(&sd);


    printf("\n");

    ready_up(&sd);



    // char test_string[BUFFER_SIZE] = "Hello world! Said the program.";
    char string_to_type[256];
    read(sd, string_to_type, 256);

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
        send(sd, &typed_words, 4, 0);
        printf("sent\n");
    }

    // USE GETTIMEOFDAY() TO CALCULATE WPM
    printf("\n\n%d\n", typed_words);
    printf("You have completed the typeracer!\n");
    
    char finish[20];
    read(sd, finish, 20);
    printf("%s\n", finish);
    return 0;
}
