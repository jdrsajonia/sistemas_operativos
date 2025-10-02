#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    key_t key=12345;
    double *ap;
    int status;

    int shmid = shmget(key,sizeof(double), 0666|IPC_CREAT); // se crea memoria compartida

    if(shmid==-1){
        perror("error");
        exit(-1);
    }


    ap=shmat(shmid,0,0);

    pid_t pid=fork();

    if (pid==0){
        *ap=3.1415;
    }
    else{
        wait(&status);
        printf("%f", *ap);
        
    }

    shmdt(ap);

    return 0;
}
    