#include "networking.h"

/*
server_setup()
==============
Create and bind a socket.
Place the socket in a listening state.
returns the socket descriptor
*/
int server_setup() {
  //setup structs for getaddrinfo, do get addrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1,sizeof(struct addrinfo)); // make sure the struct is empty
  hints->ai_family = AF_INET;                // IPv4
  hints->ai_socktype = SOCK_STREAM;          // TCP stream sockets
  hints->ai_flags = AI_PASSIVE;              // fill in my IP for me
  getaddrinfo(NULL, PORT, hints, &results);  // port defined in networking.h

  //create the socket
  int clientd;//store the socket descriptor here
  clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  //this code should get around the address in use error
  // not touching this - jidan
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt error");

  //bind the socket to address and port
  err(bind(clientd, results->ai_addr, results->ai_addrlen), "bind error");

  //set socket to listen state
  err(listen(clientd, 10), "listen error");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return clientd;
}

/*
server_tcp_handshake(int listen_socket)
=======================================
Accept a connection from a client
return the socket descriptor for the new socket connected to the client
blocks until connection is made.
*/
int server_tcp_handshake(int listen_socket){
    int client_socket;

    // used in accept()
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    
    //accept the client connection
    client_socket = accept(listen_socket, (struct sockaddr *) &client_address, &sock_size);
    err(client_socket, "accept error");

    return client_socket;
}


/*
client_tcp_handshake(char * server_address)
===========================================
Connect to the server
return the to_server socket descriptor
blocks until connection is made.
*/
int client_tcp_handshake(char * server_address) {

  //setup structs for getaddrinfo, do get addrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1,sizeof(struct addrinfo));           // make sure the struct is empty
  hints->ai_family = AF_INET;                          // IPv4
  hints->ai_socktype = SOCK_STREAM;                    // TCP stream sockets
  getaddrinfo(server_address, PORT, hints, &results);  // port defined in networking.h

  int serverd;//store the socket descriptor here
  serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  //connect to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return serverd;
}




void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
