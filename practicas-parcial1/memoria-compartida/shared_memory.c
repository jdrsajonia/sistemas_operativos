#include <sys/types.h> // para pid
#include <sys/wait.h>
#include <sys/shm.h> // para memoria compartida
#include <unistd.h> // para forkear 
#include <stdio.h> // printf y scanf


int main(){

    
    int status;

    key_t memory_key=1080; // llave de la memoria
    int shared_memory_id=shmget(memory_key, sizeof(double), 0666|IPC_CREAT); //creacion de la memoria compartida
    if (shared_memory_id==-1){
        perror("ERROR no se creo la memoria compartida");
    }

    double *data;
    data=shmat(shared_memory_id, 0,0); //enlaza el apuntador del dato a la memoria compartida

    
    pid_t process_id=fork();

    if (process_id==0){ // es el hijo
        *data=2025.666;
        printf("Yo soy el hijo y le pasaré un dato a mi padre.\nData hijo = %f \n", *data);
    }
    else{ // es el padre
        wait(&status);
        printf("\nYo soy el padre y le sumo 1000 a %f .\n", *data);
        *data=*data+1000.0;

        printf("Data padre = %f", *data);

    }




    shmdt(data);  //desenlaza el apuntador de data de la memoria compartida
    shmctl(shared_memory_id, IPC_RMID, NULL);
    return 0;
}