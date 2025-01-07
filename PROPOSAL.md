# Final Project Proposal

## Group Members:

Tony Chen, Jason Chao, Tim Ng
       
# Intentions:

We will be creating a multiplayer typing race game similar to TypeRacer and Nitro Type.
    
# Intended usage:

One machine will host a server that the clients/players will connect to. When the clients are started, they will be prompted for a username. Whenever all the clients have connected, any one of the clients can enter ‘start’ into the terminal. This will prompt the server to send each of the clients the identical string. That string will appear on the terminal of every client along with a “leaderboard” indicating the percentage of completion of each player. A client is meant to type in one word at a time and press enter. Pressing enter will update the leaderboard percentages as well as the displayed string. If the client types the word correctly that word in the string will be colored green. If the word is typed incorrectly, the string will not be colored and the user will have to type the same word. Once the client finishes all the words, it sends the amount of time the client took to finish and stops asking for user input. Once all the clients finish, each client displays the wpm and rankings of each client. Then, each client gracefully exits. The server should remain open. 

  
# Technical Details:

The forking server that creates a subserver (processes) to handle each client. Each client is connected to its respective subserver through a socket. Each subserver is connected to the main server through pipes. The server contains a variable counting the number of subservers.

Upon Connection

1) Client prompt for a username. 
Each subserver will store a struct player that contains the username, number of words entered, and the completion time of that client. Each subserver will also store a number that indicates in what order it was created; this number is for the purpose of updating the leaderboard later on through the array. 

Upon Start

1) When enough clients have connected, any client can enter ‘start’. Sends ‘start’ to the respective subserver through a socket.
2) Subserver sends ‘start’ to the server through a pipe.
3) The main server will allocate memory to create an array of struct players depending on how many subservers there are.
4) The subserver will send the server its struct player and array index through a pipe.
5) The main server will populate the array of struct players using these values. 
6) Subservers send each client the same string using sockets. 

After Start

1) Start a timer. 
2) Main server will send the subserver the entire array of struct players through a pipe. 
3) The subserver will then send that entire array to the client. 
4) The client will then parse the entire array and print it in a readable format. 
5) The client will then print out the current state of the string. 
6) The client will then be prompted for the current word. 
7) If the client spells the word right, the state of the string changes and the previous word is colored green and the variable counting how many words increments. If the client spells the word wrong, the string remains the same. 
8) The client then sends the subserver the number of words they are currently at. 
9) The subserver updates its struct player. The subserver then sends its struct player and array index to the main server so that the main server can update the full array. The main server then sends the full array back to the subserver. 
10) Repeat from step 3 until no more words are left. 
11) When there are no more words left, the timer is stopped and the time is sent back to the subserver. The subserver updates its struct player. The subserver then sends its struct player and array index to the main server so that the main server can update the full array. 

Each client stores a variable containing how many words they are currently at. 
Checking how many words are left will be done using strsep()

Finishing Conditions

The main server process will essentially keep running until each of the struct players reach the total number of words. The main server sends the subserver the finalized leaderboard which is then sent to the client. The client will format it. Then the clients will quit. 


Responsibilities: 

Tim: the actual typing game, ending the game
Tony: setting up sockets, starting the game, setting up piping
Jason: the actual typing game, leaderboard updating and communications

# Intended pacing:

Create forking_server.c and client.c and other header files (1/6)
Implement non-file communication part of client (the typing part) (1/7)
Implement working skeleton forks and pipe communication between main server and subserver (1/9)
Implement skeleton version of sockets (1/11)
Working version of string being sent to clients upon start (1/13)
Add working leaderboard updating and communication (1/16)
Add working ending the game (1/19)

