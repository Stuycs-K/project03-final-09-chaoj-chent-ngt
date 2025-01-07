[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# Typeracer

### Chunky Chewers

Jason Chao, Tony Chen, Tim Ng
       
### Project Description:

This project simulates a game where each player has to type each word in a string correctly as fast as possible. 
  
### Instructions:

How does the user install/compile/run the program.
How does the user interact with this program?

One machine will be used as a server. Each other machine will serve as a client. 
Each machine runs 'make compile'. 
Then the server machine runs 'make server'. 
Each client machine runs 'make client'. 
Once all the clients have connected, any one of the clients can 'start'. 
Once the string appears on each clients game, each client has to type the next uncolored word and press enter after they finish typing. 
Once they get through the entire string, the client blocks input. 
Once all clients finish, the server sends a final leaderboard which is displayed to each client. 
The clients gracefully exit. 
