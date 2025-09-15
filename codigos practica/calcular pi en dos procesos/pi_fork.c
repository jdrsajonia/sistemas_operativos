#include <sys/types.h> // inclute pids
#include <unistd.h> //incluye la interfaz del sistema operativo POSIX (forks)
#include <stdlib.h> //incluye manejo de memoria como malloc
#include <stdio.h> //manejo de archivos y control de entrada y salida
#include <time.h>
#include <sys/wait.h>
// #include <linux/time.h>


double positive_leibniz();
double negative_leibniz();
void calculate_pi_onsecuence();
int calculate_pi_onparalel();

int main(){
    
    int NUM_ITERATIONS=100000000;

    clock_t start, end;
    start=clock();

    calculate_pi_onparalel(NUM_ITERATIONS);
    // calculate_pi_onsecuence(NUM_ITERATIONS);
    
    end=clock();
    double elapsed= (double)(end-start)/CLOCKS_PER_SEC;
    printf("\n\nTiempo de CPU: %f ", elapsed);

    return 0;
}

// ------------------------------------------------

int calculate_pi_onparalel(int iterations){
    FILE* file;
    pid_t pid;
    pid=fork();

    double negative_result;

    if (pid==0){
        printf("\nhey, i am the son\n");
        double positive_result=positive_leibniz(iterations/2);

        file=fopen("half_result_data", "wb");
        fwrite(&positive_result, sizeof(double), 1, file);
        fclose(file);
        exit(0);
    }
    else{
        printf("\nhey, i am the father\n");
        negative_result=negative_leibniz(iterations/2);
        int status;
        wait(&status);
    }
    
    double half_result;
    file=fopen("half_result_data", "rb");
    fread(&half_result, sizeof(double), 1, file);

    double total = half_result + negative_result;
    printf("Total de Pi (paralelo): %f", total);

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
