#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //para sleep


#define MAX_PROCESOS 1
#define NUM_HILOS 8
pthread_mutex_t mutex_key=PTHREAD_MUTEX_INITIALIZER;

struct datos_tipo{
    int dato;
    int p;
};

void *proceso(void *datos){
    struct datos_tipo *datos_proceso;
    datos_proceso = (struct datos_tipo *) datos;
    int a,i,j,p;

    a=datos_proceso->dato;
    p=datos_proceso->p;

    //--->
    pthread_mutex_lock(&mutex_key);

    for (int i=0; i<=p; i++){
        printf("%i", a);
    }

    fflush(stdout);
    sleep(1);

    for (int i=0; i<=p; i++){
        printf("- ");
    }
    fflush(stdout);

    //--->
    pthread_mutex_unlock(&mutex_key);
}



int main(){

    int error,i;
    char *valor_devuelto;

    //Variables para hilos
    struct datos_tipo hilo_datos[NUM_HILOS]; // se inicializan N structs de datos tipo en el arreglo hilo_datos

    pthread_t idhilo[NUM_HILOS];

    for (int i=0; i<NUM_HILOS; i++){
        hilo_datos[i].dato=i;
        hilo_datos[i].p=i+1;
        printf("%i. struct: dato = %i , veces impreso = %i\n",i, hilo_datos[i].dato, hilo_datos[i].p+1);
    }

    
    pthread_mutex_init(&mutex_key, NULL);

    // se lanzan los hilos
    for (i=0; i<NUM_HILOS; i++){
        error=pthread_create(&idhilo[i], NULL, (void *) proceso, (void *) (&hilo_datos[i]));
        if (error!=0){
            perror("No se pudo crear el hilo");
            exit(-1);
        }
    }

    // se espera a que terminen
    for (i=0; i<NUM_HILOS; i++){
        pthread_join(idhilo[i], (void **)&valor_devuelto);
    }

    pthread_mutex_destroy(&mutex_key);

    return 0;
}