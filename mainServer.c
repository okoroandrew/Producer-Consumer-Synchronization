#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "ServerEncoder.h"
#include "ServerDecoder.h"
#include "ServerThreads.h"
#define MAX_FRAME_SIZE 536
#define PORT 12345

int main(){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[65536];

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 12345
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //Read from socket
    valread = read(new_socket, buffer, 65536);
    char* decoded = serverDecoder(buffer);

    int o = 0;
    while(*decoded){
        alphabets[o++] = *decoded++;
    }
    alphabets[o] = '\0';
    /**
     * Create threads
     * Each thread converts lower case vowels to upper case
     * last thread appends the sum of the digits to the output
     * */
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
    pthread_mutex_init(&mutexBuffer, NULL);
    pthread_create(&thread1, NULL, &charAA, NULL);
    pthread_create(&thread2, NULL, &charEE, NULL);
    pthread_create(&thread3, NULL, &charII, NULL);
    pthread_create(&thread4, NULL, &charOO, NULL);
    pthread_create(&thread5, NULL, &charUU, NULL);
    pthread_create(&thread6, NULL, &digits, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);

    char add[4];
    sprintf(add, "%d", sum);
    strcat(queue, add);
    printf("%s", queue);
    pthread_mutex_destroy(&mutexBuffer);

    //**Encode output from thread and send to client via socket*//*
    char *binaryBits = serverEncoder(queue);
    int sizeOfBits = (int)strlen(binaryBits);
    int start = 0, end = MAX_FRAME_SIZE - 1;
    for (int i = 0; i <= sizeOfBits/ MAX_FRAME_SIZE; i++) {
        send(new_socket, sliceString(binaryBits, start, end), MAX_FRAME_SIZE, 0); // fd = server_fd = new_socket
        start += MAX_FRAME_SIZE; end += MAX_FRAME_SIZE;
    }

    return 0;
}

