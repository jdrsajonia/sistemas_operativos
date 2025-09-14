#include <unistd.h> //incluye la interfaz del sistema operativo POSIX (forks)
#include <stdlib.h> //incluye manejo de memoria como malloc
#include <stdio.h> //manejo de archivos y control de entrada y salida

int main(){
    fork();
    printf("hey");

    return 0;
}