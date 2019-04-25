#include<time.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t rmutex,wmutex,res,readtry;
pthread_t tid;
int readcount=0, writecount=0;

void *reader(void* var){
    pthread_mutex_lock(&readtry);
    pthread_mutex_lock(&rmutex);
    readcount++;
    if(readcount == 1){
        pthread_mutex_lock(&res);
    }
    pthread_mutex_unlock(&rmutex);
    pthread_mutex_unlock(&readtry);
    printf("Reader %d Reading")
       printf("\nReader %d is reading..!", var);
        sleep(2);
    printf("\nReader %d is leaving..!", var);

    pthread_mutex_lock(&rmutex);
    readcount--;
    if(readcount==0) {
        pthread_mutex_unlock(&res);
    }
    pthread_mutex_unlock(&rmutex);
}

void *writer(void* var){
    pthread_mutex_lock(&wmutex);
    writecount++;
    if(writecount==1) {
        pthread_mutex_lock(&readtry);
    }
    pthread_mutex_unlock(&wmutex);

    pthread_mutex_lock(&res);
    printf("\nWriter %d is reading..!", var);
    sleep(2);
    printf("\nWriter %d is leaving..!", var);

    pthread_mutex_unlock(&res);
    pthread_mutex_lock(&wmutex);
    writecount--;
    if(writecount==0) {
        pthread_mutex_unlock(&readtry);
    }
    pthread_mutex_unlock(&wmutex);
    pthread_exit(NULL);
}

int main() {
    setbuf(stdout,NULL);
    int n1, n2, i, j;
    pthread_mutex_init(&rmutex,NULL);
    pthread_mutex_init(&wmutex,NULL);
    pthread_mutex_init(&res,NULL);
    srand(time(NULL));
    for(i=0;i < 10;i++) {
        j = rand();
        if(j%2 == 1) {


            pthread_create(&tid,NULL,reader,(void *)i);
        }
        else {
            pthread_create(&tid,NULL,writer,(void *)i);
        }
    }
    pthread_exit(NULL);
}
