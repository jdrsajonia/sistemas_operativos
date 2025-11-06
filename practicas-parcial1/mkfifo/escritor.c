#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#define PATH_FIFO "/tmp/mi_fifo"

int main(){

    if (access(PATH_FIFO, F_OK)==0){
        unlink(PATH_FIFO);

    }

    int validate_mkfifo = mkfifo(PATH_FIFO, 0666); // creacion de la mkfifo

    if (validate_mkfifo==-1){
        perror("ERROR al crear fifo");
    }

    int mkfifo_fd=open(PATH_FIFO, O_WRONLY); // se abre en modo escritura

    if (mkfifo_fd==-1){
        perror("ERROR");
    }

    char *message="Hola amigazo. Estoy usando mkfifo";

    write(mkfifo_fd, message, strlen(message)+1);

    printf("\nMensaje enviado");
    close(mkfifo_fd);



    return 0;
}