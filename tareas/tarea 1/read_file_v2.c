#include <stdlib.h>
#include <stdio.h>

struct credencial {
    char *nombre;
    char *apellido;
    int edad;
    float estatura;
};

void read_credencial(){
    FILE *file=fopen("archivo_credenciales_v2.dat","rb");  //puede leer perfectamente archivo_credenciales.dat (es decir, create_file_v1 es perfectamente compatible)
    // FILE *file=fopen("archivo_credenciales.dat","rb");
    struct credencial persona;

    persona.nombre=malloc(32);
    fread(persona.nombre, sizeof(char), 32, file);

    persona.apellido=malloc(32);
    fread(persona.apellido, sizeof(char), 32, file);

    fread(&persona.edad, sizeof(int), 1, file);
    fread(&persona.estatura, sizeof(float), 1, file);

    printf("nombre leido: %s\napellido leido: %s\nedad leida: %d\nestatura leida: %f", persona.nombre, persona.apellido, persona.edad, persona.estatura);

    free(persona.nombre);
    free(persona.apellido);
}

int main(){
    read_credencial();
    return 0;
}