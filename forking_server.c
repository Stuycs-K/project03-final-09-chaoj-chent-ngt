#include "dependencies.h"

// void send_string(int * sd, char * string) {
//     int word_count = 0;
//     char * remaining_string;
//     char * current_word;
//     while (current_word = strsep(&remaining_string, " ")) {
//         send(sd, current_word, 256, 0);
//         word_count++;
//     }
// }

int shmid;
int * shm;

static void sighandler(int signo) {
  if (SIGINT) {
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(1);
  }
}


int main() {
    int shmid = shmget(intkey, 3 * sizeof(int) + sizeof(struct player *), 0666 | IPC_CREAT);
    int * shm = (int *)shmat(shmid, NULL, 0);


    int *num_ready = &shm[0];
    int * num_done = &shm[1];
    int * subservers = &shm[2];
    struct player ** pls = (struct player **)&shm[3];

    *num_ready = 0;
    *num_done = 0;
    *subservers = 0;
    *pls = (struct player *)malloc(4 * sizeof(struct player));

    int sd;
    server_connect(&sd);


    while (1) {
        socklen_t sock_size;
        struct sockaddr_storage client_address;
        sock_size = sizeof(client_address);
        int client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

        pid_t p = fork();

        if (p == 0) {
            int ind = *subservers;
            (*subservers)++;

            char username[30];
            read(client_socket, username, 30);
            printf("Received username: %s\n", username);

            strcpy((*pls) -> username, username);
            printf("%s\n", (*pls) -> username);
            (*pls)[ind].words = 0;

            char start[30];
            read(client_socket, start, 30);
            (*num_ready)++;
            printf("%d\n", *num_ready);

            while (*num_ready != *subservers);
            char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";
            int length = len(string_to_type);


            printf("Sending to client: %s\n", string_to_type);
            write(client_socket, string_to_type, strlen(string_to_type) + 1);

            int words;
            while ((*pls)[ind].words < length) {
                read(client_socket, &words, 4);
                (*pls)[ind].words = words;
            }
            (*num_done)++;

            char finish[20] = "finish";
            while (*num_done != *subservers);
            write(client_socket, finish, 20);
            printf("us: %s, wrd: %d\n", (*pls)[ind].username, (*pls)[ind].words);

        }
    }
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
}
