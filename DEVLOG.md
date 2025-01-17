# Dev Log:

This document must be updated daily by EACH group member.

## Tony Chen

### 2024-01-06 - Add some documentation
Added makefile, added proposal, readme, created necessary files, add some appropriate organization comments in forking_server.c. Took roughly 40 minutes.

### 2024-01-07 - Add skeleton code for socket forking server
Spent 40 minutes learning sockets and adding code for socket forking server in forking_server.c.

### 2024-01-08 Add and refactor more socketing code
Spent 60 minutes adding and testing all boilerplate socket code. Encountered errors and fixed them. Refactored code into functions. 

### 2024-01-09 Testing and add username and ready up features
Spend 90 minutes testing and adding and storing usernames of clients. Asks users if they are ready. 

### 2024-01-10 Add code to increment number of players ready 
Spent 30 minutes adding and testing code to increment number of players ready. 

### 2024-01-11 Rewrote socket code and get server to know when client finishes
Spent 90 minutes. Rewrote socket code because it used something else other than Mr. K notes. Wrote a function to find length of string and wrote some code to communicate between client and server so that subserver knows when that client finishes their string.

### 2024-01-13 Create piping between processes
Spent 50 minutes. Created pipes between processes/subprocesses. Using these pipes to signal and block to subprocesses when to do certain things (when string is sent and when final results are sent). 

### 2024-01-14 Properly check when all users are ready 
Spent 40 minutes. Added code using read/write/sockets so that the game will not start for everyone unless everyone is ready. 

### 2024-01-15 Properly check when all users are finished 
Spent 60 minutes. Added code so that clients know when all other clients are finished using sockets and shared memory. 

## Jason Chao

### 2025-01-08 - TypeRacer Game Implementation
* Wrote program in client.c that runs TypeRacer in the terminal.
* Wrote comments for readability.
* Problem remains where if the user types a word that is correct, but adds additional characters (ex. "was" & "wasa"), the game will still think it's correct.
* 2 hours spent.

### 2025-01-9 - Fixed Previous Problem
* Fixed previous problem described above.
* Created a helper function check_word for cleaner code.
* 1 hour spent.

### 2024-01-10 - Server-Client Interactions
* Used the created sockets for server & client connections.
    * Server sends the string to type to the client.
    * Every time user types in the correct word, client sends the word typed + the word count.
* 30 minutes spent.

### 2024-01-12 - Formatting Tweaks
* Fixed some formatting errors in the terminal.
* 5 minutes spent.

### 2024-01-14 - Implemented Time Component
* Used clock_gettime() to find time elapsed from start of typeracer to end.
* Added formatting to game, clearing screen after a correct word input.
* 40 minutes spent.

### 2024-01-15 - Game Features
* Added a countdown for better UI.
* 20 minutes spent.

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.

## Tim Ng

### 2024-01-14 - Sorry I didn't have working code until now TvT (SHM)
* Used shm to make num_done and num_ready work
* 30 minutes spent.

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.
