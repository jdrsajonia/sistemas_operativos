#include <sys/socket.h> //para los sockets
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 3535
#define BACKLOG 10 //numero de conexiones permitidas en cola
struct sockaddr_in server, client;

char buffer[20];


int main(){

    

    // struct sockaddrin{
    //     short sin_family;   // AF_INET
    //     unsigned short sin_port;    //PORT 3535
    //     struct in_addr sin_addr;    //IP
    //     char sin_zero[8];           //8 ceros para mantener compatibilidad 
    // };

    // struct in_addr{
    //     unsigned long s_addr;
    // };

    //-------------------------------

    
    int fd=socket(AF_INET, SOCK_STREAM, 0);

    if(fd==-1){
        perror("Error al crear el socket");
        exit(-1);
    } 


    server.sin_family=AF_INET;
    server.sin_port=htons(PORT); //htons arregla problemas de endianess al decodificar el puerto
    server.sin_addr.s_addr=INADDR_ANY; //inaddr_any recibe cualquier interfaz de red del server
    // bzero(&(server.sin_zero),8);
    memset(&(server.sin_zero), 0, 8);

    int r = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)); 
    //VALIDAR ERROR
    if (r==-1){
        perror("Error al hacer el bind");
        exit(-1);
    }

    r=listen(fd,BACKLOG);
    //VALIDAR ERROR
    if (r==-1){
        perror("Error al hacer el bind");
        exit(-1);
    }


    socklen_t addrlen = sizeof(struct sockaddr_in);
    int fd2 = accept(fd, (struct sockaddr*)&client, &addrlen);
    //fork(); //crear un proceso hijo para atender al cliente? pero esto duplica todo el codigo. No necesitamos un proceso, mejor usar hilos
    //validar error
    if (fd2==-1){
        perror("Error al aceptar la conexion");
        exit(-1);
    }

    r=send(fd2, "Hola mundo", 11, 0);
    //validar error
    if (r==-1){
        perror("Error al enviar datos");
        exit(-1);
    }

    r=recv(fd2, buffer, 20, 0);
    //validar error
    if (r==-1){
        perror("Error al recibir datos");
        exit(-1);
    }

    buffer[r]=0; //poner el caracter de fin de cadena
    printf("%s\n",buffer);

    // NO COMPILA, REVISAR ERRORES 

    return 0;
}