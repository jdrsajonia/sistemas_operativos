#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#define PATH_FIFO "/tmp/mi_fifo"

int main(){
    int mkfifo_fd=open(PATH_FIFO, O_RDONLY);
    if (mkfifo_fd==-1){
        perror("ERROR al crear el mkfifo");
        exit(-1);
    }

    char buffer[39];
    read(mkfifo_fd, buffer, sizeof(buffer));
    printf("Hey! he leido esto: %s", buffer);

    close(mkfifo_fd);
    unlink(PATH_FIFO);


    return 0;
}