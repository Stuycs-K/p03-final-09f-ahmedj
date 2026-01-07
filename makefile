.PHONY: client server clean
compile: server client

client: client.o networking.o
	@gcc -Wall -o client client.o networking.o

server: server.o networking.o
	@gcc -Wall -o server server.o networking.o

server.o: server.c networking.h
	@gcc -Wall -c server.c

client.o: client.c networking.h
	@gcc -Wall -c client.c

networking.o: networking.c networking.h
	@gcc -Wall -c networking.c

clean:
	@rm *.o client server
