//recibir nombre, apellido, edad, estatura, centimetros y guardar en un archivo
#include <stdlib.h>
#include <stdio.h>

struct credencial {
    char nombre[32];
    char apellido[32];
    int edad;
    float estatura;
};

void save_credencial(struct credencial person){
    FILE *file;
    file=fopen("archivo_credenciales.dat","wb");
    fwrite(&person, sizeof(struct credencial), 1, file);
    fclose(file);
}

int main(){

    struct credencial persona;

    printf("Nombre y apellido: ");
    scanf("%s %s", persona.nombre, persona.apellido);
    printf("Edad: ");
    scanf("%d", &persona.edad);
    printf("Estatura (CM): ");
    scanf("%f", &persona.estatura);

    save_credencial(persona);

    printf("\nend of code");
    return 0;
}