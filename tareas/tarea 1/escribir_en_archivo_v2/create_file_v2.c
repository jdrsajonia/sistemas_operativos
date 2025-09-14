//recibir nombre, apellido, edad, estatura, centimetros y guardar en un archivo
#include <stdlib.h>
#include <stdio.h>

struct credencial {
    char *nombre;
    char *apellido;
    int edad;
    float estatura;
};

void save_credencial(struct credencial person){
    FILE *file;
    file=fopen("archivo_credenciales_v2.dat","wb");

    // int len_nombre=strlen(person.nombre)+1;  // +1 incluye el caracter nulo \0
    // int len_apellido=strlen(person.apellido)+1;

    fwrite(person.nombre, sizeof(char), 32, file);
    fwrite(person.apellido, sizeof(char), 32, file);

    fwrite(&person.edad, sizeof(int), 1, file);
    fwrite(&person.estatura, sizeof(float), 1, file);

    fclose(file);
}

int main(){

    struct credencial persona;

    persona.nombre=malloc(32);
    persona.apellido=malloc(32);

    printf("Nombre y apellido: ");
    scanf("%s %s", persona.nombre, persona.apellido);
    printf("Edad: ");
    scanf("%d", &persona.edad);
    printf("Estatura (CM): ");
    scanf("%f", &persona.estatura);

    save_credencial(persona);

    free(persona.nombre);
    free(persona.apellido);

    printf("\nend of code v2");
    return 0;
}