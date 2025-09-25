#include <sys/socket.h> //para los sockets
#include <netinet/in.h>
#include <stdio.h>


#define PORT 3535
#define BACKLOG 10 //numero de conexiones permitidas en cola
char buffer[20];
int main(){

    

    struct sockaddrin{
        short sin_family;   // AF_INET
        unsigned short sin_port;    //PORT 3535
        struct in_addr sin_addr;    //IP
        char sin_zero[8];           //8 ceros para mantener compatibilidad 
    };

    struct in_addr{
        unsigned long s_addr;
    };

    //-------------------------------

    struct sockaddr_in server, client;
    int fd=socket(AF_INET, SOCK_DGRAM, 0);
    //validar error
    printf("%d",fd);


    server.sin_family=AF_INET;
    server.sin_port=htons(PORT); //htons arregla problemas de endianess al decodificar el puerto
    server.sin_addr.s_addr=INADDR_ANY; //inaddr_any recibe cualquier interfaz de red del server
    bzero(&(server.sin_zero),8);

    int r = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)); 

    r=listen(fd,BACKLOG);
    //VALIDAR ERROR

    int fd2=accept(fd, (struct sockaddr*)&client, sizeof(struct sockaddr));
    //fork(); //crear un proceso hijo para atender al cliente? pero esto duplica todo el codigo. No necesitamos un proceso, mejor usar hilos
    //validar error

    int r=send(fd2, "Hola mundo", 12, 0);
    r=recv(fd2, buffer, 20, 0);
    //validar error

    buffer[r]=0; //poner el caracter de fin de cadena
    printf("%s\n",buffer);

    // NO COMPILA, REVISAR ERRORES 

    return 0;
}