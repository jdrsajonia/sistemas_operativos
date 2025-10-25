#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PROCESOS 1
#define NUM_HILOS 8

pthread_mutex_t lock; // variable global de mutex

struct datos_tipo {
    int dato;
    int p;
};


void *proceso(void *datos) {
    struct datos_tipo *datos_proceso;
    datos_proceso = (struct datos_tipo *) datos;

    int a, p;
    a = datos_proceso->dato;
    p = datos_proceso->p;
   
// --->
    pthread_mutex_lock(&lock);

    for (int i = 0; i <= p; i++) {
        printf(" %i ", a);
    }
   
    fflush(stdout);
    sleep(1);

    for (int i = 0; i <= p; i++) {
        printf("-- ");
    }
    fflush(stdout);

   
   
// --->
    pthread_mutex_unlock(&lock);
   
    pthread_exit(NULL);
}

int main() {
   
   
    pthread_mutex_init(&lock, NULL);      // inicializar mutex
   
   
    int error;
    char *valor_devuelto;
    struct datos_tipo hilo_datos[NUM_HILOS];
    pthread_t idhilo[NUM_HILOS];

    for (int i = 0; i < NUM_HILOS; i++) {
        hilo_datos[i].dato = i;
        hilo_datos[i].p = i + 1;
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        error = pthread_create(&idhilo[i], NULL, proceso, (void *)(&hilo_datos[i]));
        if (error != 0) {
            perror("No puedo crear hilo");
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(idhilo[i], (void **)&valor_devuelto);
    }
   
   
    pthread_mutex_destroy(&lock);
    return 0;
}

// flag: -lpthread
