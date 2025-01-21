#include "dependencies.h"

void server_connect(int * sd) {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, PORT, hints, &results);

    *sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    bind(*sd, results->ai_addr, results->ai_addrlen);
    listen(*sd, 4);
}

void client_connect(int * sd, char * ip) {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    getaddrinfo(ip, PORT, hints, &results);

    *sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    connect(*sd, results->ai_addr, results->ai_addrlen);
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

void username_setup(int * sd) {
    printf("Username: ");
    char in[30];
    char username[30];
    fgets(in, 29, stdin);
    sscanf(in, "%[^\n]", username);
    write(*sd, username, strlen(username));
}

void ready_up(int * sd) {
    char ready[30];
    while (strcmp(ready, "ready\n") != 0) {
        printf("Type 'ready' to ready up: ");
        fgets(ready, 29, stdin);
        printf("\n");
    }
    write(*sd, "ready\0", 6);
}

int len(char * string) {
    int n = 0;
    char cp[30];
    strcpy(cp, string);
    char * c = cp;
    while (c) {
        strsep(&c, " ");
        n++;
    }
    return n;
}

int calcwpm(int words, int time) {
    return 60. / time * words;
}

char * sortlb(struct player * pls, int size) {
    char * out = (char *)malloc(400);
    for (int i = 0; i < size; i++) {
        char form[100];
        int a = sprintf(form, "%s wpm: %d time elapsed: %.2f\n", (pls + i) -> username, (pls + i) -> wpm, (pls + i) -> time);
        strcat(out, form);
    }
    return out;
}

