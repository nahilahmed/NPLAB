#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

void *callback(int i){
    printf("Thread %d from %d\n",i,getpid());
    pthread_exit(NULL);
}

void main(){
    pthread_t t;
    int x;
    x = fork();
    if(x == 0){
        printf("Child");
        for(int i = 0; i < 3; i++){
            pthread_create(&t,NULL,callback,(void *)i);
        }
    }else{
        printf("Parent");
        for(int i = 0; i < 3; i++){
            pthread_create(&t,NULL,callback,(void *)i);
        }
    }
    pthread_exit(NULL);
}
