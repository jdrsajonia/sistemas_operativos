#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORY_KEY 12345


int main(){

    int shmemory_id=shmget(MEMORY_KEY, sizeof(double), 0666|IPC_CREAT);
    if (shmemory_id==-1){
        perror("ERROR al crear memoria compartida");
        exit(-1);
    }

    double *data;

    data=shmat(shmemory_id, NULL, 0);

    if (data==(void *)-1){
        perror("ERROR al enlazar memoria compartida al dato");
        exit(-1);
    }

    printf("Ingrese un dato double a escribir --> ");
    scanf("%lf",data);

    printf("\n%f se ha escrito en la memoria compartida.", *data);
    

    shmdt(data);
    return 0;
}