#include "dependencies.h"

int shmid;
int * shm;

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

static void sighandler(int signo) {
  if (SIGINT) {
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(1);
  }
}

int main() {
    shmid = shmget(intkey, 3 * sizeof(int), 0666 | IPC_CREAT);
    shm = (int *)shmat(shmid, NULL, 0);

    int *num_ready = &shm[0];
    int * num_done = &shm[1];
    int * subservers = &shm[2];
    *num_ready = 0;
    *num_done = 0;
    *subservers = 0;

    int fd = open("mapping", O_RDWR | O_CREAT | O_TRUNC, 0666);
    lseek(fd, 4 * sizeof(struct player) - 1, SEEK_SET);
    write(fd, "", 1);
    struct player * pls = (struct player *)mmap(0, 4 * sizeof(struct player), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 4; i++) {
      struct player o;
      memset(&o, 0, sizeof(o));
      o.words = 0;
      o.time = 0;
      o.wpm = 0;
      pls[i] = o;
    }

    int semd = semget(intkey, 1, IPC_CREAT | IPC_EXCL | 0644);
    union semun d;
    d.val = 1;
    semctl(semd, 0, SETVAL, d);



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
            printf("Received username: \033[38;5;47m%s\033[0m\n", username);

            strcpy((pls + ind) -> username, username);

            (pls + ind) -> words = 0;

            char start[30];
            read(client_socket, start, 30);
            (*num_ready)++;

            while (*num_ready != *subservers);
            char string_to_type[BUFFER_SIZE] = "Hello world! Said the program.";
            int length = len(string_to_type);

            printf("Sent to client \033[38;5;47m%s\033[0m\n", username);
            write(client_socket, string_to_type, strlen(string_to_type) + 1);

            int words;
            double user_time;

            while ((pls + ind) -> words < length) {  
                int semd = semget(intkey, 1, 0);
                struct sembuf sb;
                sb.sem_num = 0;
                sb.sem_flg = SEM_UNDO;
                sb.sem_op = -1;

                char * lb = sortlb(pls, *subservers);
                write(client_socket, lb, 400);
                read(client_socket, &words, 4);
                read(client_socket, &user_time, sizeof(double));
                (pls + ind) -> words = words;
                (pls + ind) -> time = user_time;
                (pls + ind) -> wpm = calcwpm(words, user_time);

                sb.sem_op = 1;
                semop(semd, &sb, 1);
            }

            char stats[100];
            sprintf(stats, "You finished in %dst/th place! You had a pace of %d wpm!", *num_done + 1, calcwpm(words, user_time));
            write(client_socket, stats, 100);

            (*num_done)++;

            while (*num_done < *subservers);
            
            char * lb = sortlb(pls, *subservers);
            write(client_socket, lb, 400);
        }
    }
}
