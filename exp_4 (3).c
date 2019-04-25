#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

pthread_mutex_t mutex, res;
pthread_t tid;
int readcount=0;

void *reader(void * var) {
    setbuf(stdout,NULL);
    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount==1)
        pthread_mutex_lock(&res);
    printf("\n Reader %d is inside ",var);
    pthread_mutex_unlock(&mutex);
    sleep(2);
    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount==0)
        pthread_mutex_unlock(&res);
    pthread_mutex_unlock(&mutex);
    printf("\nReader is Leaving");
    pthread_exit(NULL);
}   

void *writer(void * var) {
    setbuf(stdout,NULL);
    pthread_mutex_lock(&res);
    printf("\nWriter has entered");
    sleep(2);
    printf("\nWriter is leaving");
    fflush(stdout);
    pthread_mutex_unlock(&res);    
    pthread_exit(NULL);
}

int main() {
    setbuf(stdout,NULL);
    int n1, n2, i, j;  
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&res,NULL);
    srand(time(NULL));
    for(i=0;i < 10;i++) {
        j = rand();
        if(j%2 == 1) {


            pthread_create(&tid,NULL,reader,(void *)i);  
        }
        else {
            pthread_create(&tid,NULL,writer,NULL);
        }
    }
    pthread_exit(NULL);
}
