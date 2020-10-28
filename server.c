#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <err.h>
#include <netinet/in.h>

#define MAX_SIZE 128

/**
 * Authors: Sarah Pham, Jonathan Osborne, and Kegan van Ginkel
 * 
 **/

int serverSocket;

// sockaddr_in is a predefined struct in the in.h library, contains the information about the address coming in
struct sockaddr_in serverAddress;

// sockaddr_storage is from the socket.h library, defined to declare storage for automatic variables that is large and aligned enough for the socket address data structure of ANY family
struct sockaddr_storage socketStorage;

// socklen_t is an unsigned 32 bit type from socket.h, we use this because it is recommended to not use values larger than 2^(32)-1
socklen_t socketAddressSize;

int connectToClient(){
    printf("this method works");
    /** 
     * Socket method returns a nonnegative number integer if successful. Creates an unbound socket in a communications domain, and returns a file descriptor that can be used in later function calls that operate on sockets
     * 
     *   PF_INET = protocol family that refers to anything in the protocol, usually sockets/ports
     *   SOCK_DGRAM = is a datagram based protocol used by UDP; send one datagram and receive one reply then connection terminates
     *   0 = protocol of 0 causes socket() to use an unspecified default protocol appropriate for the requested socket type
    **/ 
    if((serverSocket = socket(PF_INET, SOCK_DGRAM, 0)) == -1){
        // errx produces an error message
        errx(1, "Socket call error");
        printf("Error calling socket");
        exit(EXIT_FAILURE);
    }

    printf("Success: Server Socket Call");

    
    serverAddress.sin_family = AF_INET; // Binding the socket with an address so that the remote process can refer to it
    serverAddress.sin_port = 8080; // Binding a port number to the socket
    // for test: replace htonl(INADDR_ANY) to 127.0.0.1, but we cannot use that per description
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // sin_addr is the socket ip address, we set the current host IP address: INADDR_ANY. 


    /**
     * bind method in socket.h library assigns a local socket addr to a socket identified by descriptor socket, which has no local socket addr assigned
     * - basically binds a name to a socket
     * - returns 0 if sucessful and -1 otherwise
     * 
     * Parameters:
     * socket - specifies the file descriptor of the socket to be bound
     * address - points to a sockaddr structure containing address to be bound
     * address_len - specifies length of sockaddr structure
     **/
    if((bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) == -1){
        errx(1, "Socket address binding error");
        exit(EXIT_FAILURE);
    }

    printf("Success: Socket Address Binding");

    socketAddressSize = sizeof(socketStorage); // We initialize a new socket that is the size of the socket storage

    return 0;
}

void writeToFile(int serverSocket, struct sockaddr_storage socketStorage){
    FILE *file = fopen("test.txt", "w");
    char buffer[MAX_SIZE];
    int character = 1;

    if(file == NULL) errx(1, "File creation error");

    socklen_t addressSize = sizeof(socketStorage);
    while(character != '0'){
        character = recvfrom(serverSocket, buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr *) &socketStorage, &addressSize);
        if(buffer[0] == '\0') break;
    }
}

int main(){
    printf("main method is being called");
    connectToClient();
    writeToFile(serverSocket, socketStorage);

    return 0;
}