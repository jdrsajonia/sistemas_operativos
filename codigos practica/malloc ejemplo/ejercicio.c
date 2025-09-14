
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //scanf("%d",&a);
    
    char *nombre;
    char *apellido;
    
    nombre=malloc(32);
    apellido=malloc(32);
    
    scanf("%s", nombre);
    scanf("%s", apellido);
    
    printf("Nombre: %s \nApellido: %s", nombre, apellido);
    
    free(nombre);
    free(apellido);
    return 0;
}
