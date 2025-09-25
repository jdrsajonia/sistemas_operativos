#include <sys/socket.h> //para los sockets
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
struct sockaddr_in cliente;
#define PORT 3535

int main(){
    // HAMACHI; tunel vpn
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd==-1){
        perror("Error al crear el socket");
        exit(-1);
    }



    cliente.sin_family=AF_INET;
    cliente.sin_port=htons(PORT);
    cliente.sin_addr.s_addr=inet_addr("127.0.0.1");
    // bzero(&(cliente.sin_zero),8);
    memset(&(cliente.sin_zero), 0, 8);

    // memset(&(cliente.sin_zero),0,8);
    int r = connect(fd, (struct sockaddr *)&cliente, sizeof(struct sockaddr));
    if (r==-1){
        perror("Error al conectar con el servidor");
        exit(-1);
    }

    char buffer[20];

    r=recv(fd, buffer, 20, 0);
    if (r==-1){
        perror("Error al recibir datos");
        exit(-1);
    }
    printf("%s\n",buffer);
    
    r=send(fd, "Hola desde el cliente", 21, 0);
    

    if (r==-1){
        perror("Error al enviar datos");
        exit(-1);
    }
    // TAREA: investigar setcockopt()
    // y/o signal(ctrl+c) (para capturar el control+C)
    
    close(fd);

    return 0;
}