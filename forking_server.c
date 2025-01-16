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

int randint(int num) { // num is amount of prompts in the txt file
	srand(time(NULL) + getpid());
	return rand() % num + 1;
}

void promptReader() {
  FILE * ptr = fopen("prompts.txt", "r");
  if (ptr < 0) {
    perror("file open error");
    exit(1);
  }
int shmid;
int * shm;

static void sighandler(int signo) {
  if (SIGINT) {
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(1);
  }
}

}

int main() {
    // allocate memory for dynamic array of pipes
    int fds[4][2];
    for (int i = 0; i < 4; i++) {
      pipe(fds[i]);
    }
    // allocate memory for dynamic array of struct player
    int shmid = shmget(intkey, 3 * sizeof(int), 0666 | IPC_CREAT);
    int * shm = (int *)shmat(shmid, NULL, 0);


    int *num_ready = &shm[0];
    int * num_done = &shm[1];
    int * subservers = &shm[2];

    *num_ready = 0;
    *num_done = 0;
    *subservers = 0;

    int sd;
    server_connect(&sd);

    // char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";

    while (1) {
        // create subprocess and pipes between subserver and server
        socklen_t sock_size;
        struct sockaddr_storage client_address;
        sock_size = sizeof(client_address);
        int client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

        pid_t p = fork();
        // subprocess
        if (p == 0) {
            int ind = *subservers; //shm
            (*subservers)++;
            // close(fds[ind][WRITE]);
            char username[30];
            read(client_socket, username, 30);
            printf("Received username: %s\n", username);

            struct player * pl = (struct player *)malloc(sizeof(struct player));

            strcpy(pl -> username, username);
            pl -> words = 0;

            // send_string(&sd, string_to_type);
            char start[30];
            read(client_socket, start, 30);
            (*num_ready)++; // need to use shm
            printf("%d\n", *num_ready);
            int i;
            while (*num_ready != *subservers);
            // read(fds[ind][READ], &i, 4);
            char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";
            int length = len(string_to_type);


            printf("Sending to client: %s\n", string_to_type);
            write(client_socket, string_to_type, strlen(string_to_type) + 1);

            int words;
            while (pl -> words < length) {
                read(client_socket, &words, 4);
                pl -> words = words;
            }
            (*num_done)++; //need to use shm
            int j;
            printf("num_done: %d\n", *num_done);


            // send_string(&sd, string_to_type);

        }

            // subprocess does handshake

            // read username from client

            // create struct player and populate

            // send struct player to main process

            // copy over int subserver as array_index (shm)

            // increment subserver (shm)


        // main process

            // read struct player and reallocate array of struct players

        // subprocess

            // listen from client for ready

            // increment num_ready (shm)

        // main process

            // stall until num_ready == subservers

            // send a string to all servers

        // subprocess

            // block until read the above string

            // send string to client

            // access total array of leaderboard using shm and send to client

        // while (condition) {
          // after start loop
        // }

        // subprocess

          // send leaderboard to clients


    }
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
}
