#include <sys/types.h> // inclute pids
#include <unistd.h> //incluye la interfaz del sistema operativo POSIX (forks)
#include <stdlib.h> //incluye manejo de memoria como malloc
#include <stdio.h> //manejo de archivos y control de entrada y salida
#include <sys/wait.h>


/*NOTA: Este archivo solo sirve en un sistema Unix, 
dado que para el fork(), se usa la API POSIX para las llamadas al kernel 

ADICIONAL: usaremos pipes para comunicar los procesos padre e hijo

*/

double positive_leibniz(int);
double negative_leibniz(int);
void calculate_pi_onsecuence(int);
int calculate_pi_onparalel(int);

int main(){
    
    int NUM_ITERATIONS=100000000;

    calculate_pi_onparalel(NUM_ITERATIONS);
    // calculate_pi_onsecuence(NUM_ITERATIONS);
    
    return 0;
}

// ------------------------------------------------

int calculate_pi_onparalel(int iterations){
    pid_t pid;
    int pipefd[2];
    double buffer[1];
    int bytes_written=pipe(pipefd);

    if (bytes_written<0){
        perror("ERROR: pipe creation error");
    }

    pid=fork();

    if (pid<0){
        perror("ERROR: pid error");
    }

    if (pid==0){ // son
        close(pipefd[0]);
        double positive_result=positive_leibniz(iterations/2);
        bytes_written=write(pipefd[1], &positive_result, sizeof(double));
        close(pipefd[1]);
        exit(0);
    }
    else{  // father
        double negative_result=negative_leibniz(iterations/2);
        bytes_written=read(pipefd[0], buffer, sizeof(double));
        close(pipefd[0]);

        double total = negative_result+ buffer[0];
        printf("Total de Pi (paralelo): %f", total);
    }
    
    return 0;  
}

// ------------------------------------------------

void calculate_pi_onsecuence(int iterations){
    double positive = positive_leibniz(iterations);
    double negative = negative_leibniz(iterations);
    double total = positive + negative;
    printf("Total de Pi (seguido): %f", total);   
}

// ------------------------------------------------

double positive_leibniz(int iterations){
    double result=0;
    for (int i=0; i<=iterations; i++){
        result=result+1.0/(4.0*i+1.0);
    }
    return 4.0*result;
}

double negative_leibniz(int iterations){
    double result=0;
    for (int i=1; i<= iterations+1; i++){
        result=result+1.0/(4.0*i-1.0);
    }
    return -4.0*result;
}
