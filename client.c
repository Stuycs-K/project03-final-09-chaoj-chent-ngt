#include "dependencies.h"

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

    char string_to_type[256];
    int read_string_status = read(sd, string_to_type, 256);
    if (read_string_status == -1) {
        err();
    }

    // Countdown
    sleep(1);
    for (int i = 5; i >= 1; i--) {
        printf("\033[2J\033[1;1H");
        printf("String to type: %s\n", string_to_type);
        printf("Starting in %d...\n", i);
        sleep(1);
    }
    printf("\033[2J\033[1;1H");

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

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

        printf("\033[2J\033[1;1H");
        for (int i = 0; i < strlen(current_word); i++) {
            printf("\033[30;48;5;120m%c\033[0m", current_word[i]);
        }
        printf("\n"); // for formatting purposes

        typed_words++;
        send(sd, &typed_words, 4, 0);
        // printf("sent\n");
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time taken: %f\n", time);
    printf("You have completed the typeracer!\n");

    return 0;
}
