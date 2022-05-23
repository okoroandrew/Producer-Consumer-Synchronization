#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ClientEncoder.h"
#include "ClientDecoder.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#define MAX_FRAME_SIZE 536
#define PORT 12345

int main() {
    // Read the user file and store it in the string array. Then convert to Binary
    char inputFilePath[100];
    char outputFilePath[100];
    printf("Please enter input file directory: ");
    scanf("%s", inputFilePath);
    printf("Enter binary output file directory: ");
    scanf("%s", outputFilePath);

    // Reads a binary file from the producer and store in string variable binaryData
    char textOutputFilePath[100];
    printf("Enter ASCII output file directory: ");
    scanf("%s", textOutputFilePath);

    //Client Socket
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[65536];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //Create packet from client encoder and send via the socket
    char *binaryBits = clientEncoder(inputFilePath, outputFilePath);
    int sizeOfBits = (int)strlen(binaryBits);
    int start = 0, end = MAX_FRAME_SIZE - 1;
    for (int i = 0; i <= sizeOfBits/ MAX_FRAME_SIZE; i++) {
        send(sock, sliceString(binaryBits, start, end), MAX_FRAME_SIZE, 0);
        start += MAX_FRAME_SIZE; end += MAX_FRAME_SIZE;
    }

    //Read encoded packets from pipe and decode to get server massage
    valread = read(sock, buffer, 65536);
    if (valread < 0){
        printf("\n Error reading from socket \n");
        return -1;
    }
    clientDecoder(buffer, textOutputFilePath);
    close(sock);

    return 0;
}

