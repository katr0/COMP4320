#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <netdb.h>

#define MAX_SIZE 128

/**
 * Authors: Sarah Pham, Jonathan Osborne, and Kegan van Ginkel
 * 
 **/


//Returns an int indicating if the packet was damaged, lost, or undamaged.
int gremlin(char *data) {

}

//returns an in representing the checksum of the packet.
//check is to be placed in the header of the packet being seng along with the packets sequence number
int checksum(char *data) {

}

//sends file to server after running it through gremlin function
void send(char *filename, int clientfd, struct sockaddr)in server) {

}





int main(int argc, char *arv[]) {

    char *ip = "127.0.0.1";
    int port = 8080;
    int clientfd;

    FILE *f;
    char *filename = "client.txt";

    //gets probablities of loss and damage from runtime arguments
    damageProb = atof(argv[1]);
    lossProb = atof(argv[2]);

    //gets socket descriptor (-1 if failed)
    clientfd = socket(AF_INET, SOCK_DGRAM,0);
    if (clientfd == -1) {
        perror("ERROR Socket failed to open succesfully");
        exit(0);
    }


    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = port;

    //converts IP address in number-and-dots to unsigned long
    server.sin_addr.s_addr = inet_addr(ip);

    //will send file to server after runnign it through gremlin function
    send(filename, clientfd, server);

}