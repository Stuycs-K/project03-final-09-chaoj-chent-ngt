# Final Project Proposal

## Group Members:

Tony Chen, Jason Chao, Tim Ng
       
# Intentions:

We will be creating a multiplayer typing race game similar to TypeRacer and Nitro Type.
    
# Intended usage:

One machine will host a server that the clients/players will connect to. When the clients are started, they will be prompted for a username. Whenever all the clients have connected, any one of the clients can enter ‘ready’ into the terminal. However, the server will not send out the typeracer until all clients have stated they are ready and sent that signal to the server. This will prompt the server to send each of the clients the identical string. That string will appear on the terminal of every client along with a “leaderboard” indicating the words per minute and time elapsed for each player. A client is meant to type in one word at a time and press enter. Pressing enter will update the leaderboard words per minute, time elapsed, and the displayed string. If the client types the word correctly, that word in the string will be colored green. If the word is typed incorrectly, there are a few possible errors that may show up. If let's say one letter is wrong, the whole word will be highlighted green except for that letter, in which it will be red. If no letter is typed where there should be one, it will also show up as highlighted red. Lastly, if you type a word that is too long, the client will tell you the word is too long and prompt you to type the word again. Once the client finishes all the words, it sends the amount of time the client took to finish and stops asking for user input. Once all the clients finish, each client displays the wpm and rankings of each client. Then, each client gracefully exits. The server should remain open. 

  
# Technical Details:

The forking server that creates a subserver (processes) to handle each client. Each client is connected to its respective subserver through a socket. Each subserver shares memory through shared memory segments. Some of the information in those shared memory segments include number of clients done, number of clients ready, the leaderboard system, and number of subservers.

Upon Connection

1) Client prompt for a username. Each subserver will update the subserver that contains the username, number of words entered, and the completion time of that client through shared memory.

Upon Start

1) When enough clients have connected, any client can enter ‘ready’. Sends ‘ready’ to the respective subserver through a socket.
2) Subserver sends ‘ready’ to the server through a pipe. The server will know when every client is ready when the num_ready variable equals to the number of subservers (also a variable).
3) Subservers send each client the same string using sockets. 

After Start

1) Start a timer
2) Print out Leaderboard (Using semaphore)
3) Wait until the user types in the correct word
4) Client sends subserver information (words typed, time elapsed)
5) In subserver, use shared memory segment to update leaderboard
6) Repeat from step 2 - step 5 until user completes the typeracer (gets all words correct)
7) Print out individual user statistics (Placement e.g. 1st, 2nd, etc.)
8) When all users are done, print out the leaderboard

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
