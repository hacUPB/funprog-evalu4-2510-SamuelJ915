#include <stdio.h>
#include <stdlib.h>

void MenuPrincipal();
void caracteres();
void palabras();  
void EspaciosBlancos();  
void Lineas(); 
void vocales(); 
void CambiarPalabra();

int main(void)
{
    int opcion;
    char ArchivoLectura;
    printf("Ingrese el nombre del archivo a leer\n");
    FILE *archivo;
    archivo = fopen("ArchivoLectura","r");
    fscanf(archivo,"%d",&ArchivoLectura);
    
    if (!archivo)
    {
        perror("No se pudo abrir el archivo que quieres leer.\n");
        return 1;
    }
    archivo = (char *)malloc((ArchivoLectura * sizeof(char)));
   
    printf("Bienvenido, que desea hacer\n");
   
    do {
        MenuPrincipal();
        printf("Ingresa el número de la opción deseada:\n");
        scanf("%d", &opcion);
       
        switch(opcion)
        {
            case 1:
                caracteres ();
                break;
            case 2:
                palabras();
                break;
            case 3:
                EspaciosBlancos();
                break;
            case 4:
                Lineas();
                break;
            case 5:
                vocales();
                break;
            case 6:
                CambiarPalabra();
                break;
            case 7:
                printf("Saliendo del programa...\n");
            default:
                printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    } while(opcion != 7);
   
    free(ArchivoLectura);
    
    return 0;
}

void MenuPrincipal()
{
    printf("1. Total de caracteres (excluyendo espacios)\n");
    printf("2. Total de palabras\n");
    printf("3. Total de espacios en blanco\n");
    printf("4. Total de lineas\n");
    printf("5. Mostrar cuantas veces aparece cada vocal\n");
    printf("6. Cambiar una palabra del texto por otra\n");
    printf("7. Salir del programa\n");
}

void caracteres()
{
}
void palabras()
{
}
void EspaciosBlancos() 
{ 
}
void Lineas()
{
}
void vocales()
{
}
void CambiarPalabra()
{
}