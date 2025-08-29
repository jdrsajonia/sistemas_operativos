#include <stdlib.h>
#include <stdio.h>

struct credencial {
    char nombre[32];
    char apellido[32];
    int edad;
    float estatura;
};

void read_credencial(){
    FILE *file=fopen("archivo_credenciales.dat","rb");
    struct credencial persona;
    fread(&persona, sizeof(struct credencial), 1, file);
    printf("nombre leido: %s\napellido leido: %s\nedad leida: %d\nestatura leida: %f", persona.nombre, persona.apellido, persona.edad, persona.estatura);
}

int main(){
    read_credencial();
    return 0;
}