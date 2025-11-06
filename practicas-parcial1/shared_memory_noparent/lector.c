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
        perror("ERROR al acceder a la memoria compartida");
        exit(-1);
    }

    double *data;
    data=shmat(shmemory_id, NULL, 0);

    if (data == (void *) -1){
        perror("ERROR al enlazar el dato con la memoria compartida");
    }

    printf("\nEsperando a que el escritor escriba...\n");
    printf("Dato leido: %f", *data);

    shmdt(data);
    shmctl(shmemory_id, IPC_RMID, NULL);

    return 0;
}