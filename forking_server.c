#include "dependencies.h" 

int main() {
    // allocate memory for dynamic array of pipes
    int subservers = 0;
    // allocate memory for dynamic array of struct player
    
    int num_ready = 0;
    while (1) {
        // server_setup

        // create subprocess and pipes between subserver and server
         
        // subprocess

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

    }
}