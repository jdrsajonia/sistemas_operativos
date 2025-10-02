#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


double load_data(){
    int MAX=1000;
    double x=1.0;
    for (int i=0; i<=MAX; i++){
        x=x+sin(i);
        // gcc threads.c -o thread -lm TOCA PONER ESTA FLAG QUE RARO
    }
    return x;
}

void *funcion(void *datos){
    printf("%i", *(int *)datos);
    double resultado=load_data();
    printf("el resultado es %f", resultado);
};


int main(){
    pthread_t hilo;
    int dato;
    int *retval;
    dato=1234;

    int r = pthread_create(&hilo, NULL, (void *)funcion, (void *)&dato);
    
    if(r!=0){
        //error
        perror("eerror en pthread_create");
        exit(-1);


    }
    r= pthread_join(hilo, (void **)&retval);

    if(r!=0){
        perror("error en phtread joinnn");
        exit(-1);
    }

    return 0;
}
