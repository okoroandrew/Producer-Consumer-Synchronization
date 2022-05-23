#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutexBuffer;

char alphabets[5000];

char queue[10];
int sum = 0;

void * charAA(){
    for (int i = 0; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);

        if (alphabets[i] == 'a'){
            alphabets[i] = 'A';
        }
        queue[i] = alphabets[i];

        pthread_mutex_unlock(&mutexBuffer);
    }
}

void * charEE(){
    for (int i = 0; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);
        if (alphabets[i] == 'e'){
            alphabets[i] = 'E';
        }
        queue[i] = alphabets[i];

        pthread_mutex_unlock(&mutexBuffer);
    }
}

void * charII(){
    for (int i = 0; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);
        if (alphabets[i] == 'i'){
            alphabets[i] = 'I';
        }
        queue[i] = alphabets[i];

        pthread_mutex_unlock(&mutexBuffer);
    }
}

void * charOO(){
    for (int i = 0; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);
        if (alphabets[i] == 'o'){
            alphabets[i] = 'O';
        }
        queue[i] = alphabets[i];

        pthread_mutex_unlock(&mutexBuffer);
    }

}

void * charUU(){
    int i = 0;
    for ( ; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);
        if (alphabets[i] == 'u'){
            alphabets[i] = 'U';
        }
        queue[i] = alphabets[i];

        pthread_mutex_unlock(&mutexBuffer);
    }
}

void * digits(){
    for (int i = 0; i < strlen(alphabets); i++){
        pthread_mutex_lock(&mutexBuffer);
        if (alphabets[i] == '1' || alphabets[i] == '2' || alphabets[i] == '3' ||alphabets[i] == '4' || alphabets[i] == '5' ||
            alphabets[i] == '6' || alphabets[i] == '7' || alphabets[i] == '8' || alphabets[i] == '9'){
            sum += (int)alphabets[i];
        }
        pthread_mutex_unlock(&mutexBuffer);
    }

}