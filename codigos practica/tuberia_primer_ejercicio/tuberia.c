#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
POR CONVENCION: un proceso produce y el otro consume.

PRODUCTOR: por convención, al producir (escribir) datos, 
se cierra el descriptor de READ para que no pueda leer
Al finalizar, tambien se cierra el descriptor de WRITE por seguridad

CONSUMIDOR: por convención, al leer un dato se consume,
se cierra el descriptor de WRITE para que no pueda escribir
Al finalizar, tambien se cierra el descriptor de READ por seguridad
*/

int main(){

    int pipefd[2]; //array de descriptor Read, Write
    char buffer[5];
    int r = pipe(pipefd);

    if (r<0){
        perror("ERROR PIPE");
    }

    pid_t pid=fork();

    if (pid<0){
        perror("ERROR EN EL fork");
    }

    if (pid==0){    // el hijo

        close(pipefd[0]);   // cierra read
        r=write(pipefd[1], "hola", 4); 
        close(pipefd[1]);   // cierra write
        exit(0);
    }
    else{           // los pecaos del padre
        // int status;
        /* wait(&status); no es necesario porque la siguiente funcion, read es bloqueante.
        read atasca al padre hasta que el buffer tenga datos. */
        r=read(pipefd[0], buffer, 4);
        buffer[5]=0;
        printf("%s", buffer);
        close(pipefd[0]);  //close read
    }

    return 0;
}