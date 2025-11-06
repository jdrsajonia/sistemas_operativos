#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){

    char buffer[10];

    int status;
    int pipefd[2];
    int bytes_written=pipe(pipefd);

    if (bytes_written==-1){
        perror("ERROR al crear el pipe unidireccional");
    }

    pid_t process=fork();
    if (process==-1){
        perror("ERROR al crear el proceso");
    }




    if (process==0){
        close(pipefd[0]);
        char *string = "mensagei";
        write(pipefd[1], string, sizeof(string));
        printf("Soy el hijo y te mando un dato secreto...\n");
        close(pipefd[1]);

    }
    else{
        wait(&status);
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        buffer[-1]='\0';
        printf("Soy el padre y el dato secreto es: %s\n", buffer);
    }

    return 0;
}