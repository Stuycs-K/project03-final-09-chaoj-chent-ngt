client: compile
	@./client
server: compile
	@./server
compile: client.o forking_server.o connections.o
	@gcc -o client client.o connections.o
	@gcc -o server forking_server.o connections.o
client.o: client.c dependencies.h
	@gcc -c client.c
server.o: forking_server.c dependencies.h
	@gcc -c forking_server.c
connections.o: connections.c dependencies.h
	@gcc -c connections.c
clean:	
	@rm -f *.o client server