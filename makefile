client: compile
	@./client
server: compile
	@./server
compile: client.o forking_server.o 
	@gcc -o client client.o
	@gcc -o server server.o
client.o: client.c dependencies.h
	@gcc -c client.c
server.o: forking_server.c dependencies.h
	@gcc -c forking_server.c
clean:
	@rm -f *.o client server