#include "dependencies.h"

int err() {
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
}

int main() {
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