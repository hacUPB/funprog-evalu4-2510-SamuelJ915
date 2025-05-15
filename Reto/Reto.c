#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Nombre 1000

// Función para leer el archivo y cargarlo en memoria dinámica
char* leer_archivo(const char* nombre_archivo, long* longitud) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    // Determinar el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    *longitud = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Reservar memoria para el contenido
    char* contenido = (char*)malloc(*longitud + 1);
    if (contenido == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return NULL;
    }

    // Leer el contenido del archivo
    fread(contenido, 1, *longitud, archivo);
    contenido[*longitud] = '\0';

    fclose(archivo);
    return contenido;
}

int main() {
    char* texto = NULL;
    long longitud = 0;
    char nombre_archivo[Nombre];
    char nombre_salida[Nombre];
    int opcion;
    int caracteres, palabras, espacios, lineas;
    int frecuencias[5];
    char buscar[Nombre], reemplazo[Nombre];
    char* texto_modificado = NULL;
    long nueva_longitud = 0;

    do {
        printf("\nMenu de opciones:\n");
        printf("1. Ingresar nombre del archivo a leer\n");
        printf("2. Calcular estadisticas del texto\n");
        printf("3. Calcular frecuencia de vocales\n");
        printf("4. Cambiar una palabra por otra\n");
        printf("5. Guardar resultados en archivo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                if (texto != NULL) {
                    free(texto);
                    texto = NULL;
                }
                if (texto_modificado != NULL) {
                    free(texto_modificado);
                    texto_modificado = NULL;
                }

                printf("Ingrese el nombre del archivo (.txt): ");
                fgets(nombre_archivo, Nombre, stdin);
                nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0'; // Eliminar salto de línea

                texto = leer_archivo(nombre_archivo, &longitud);
                if (texto != NULL) {
                    printf("Archivo cargado correctamente (%ld caracteres).\n", longitud);
                }
                break;

            case 2:
                if (texto == NULL) {
                    printf("Primero debe cargar un archivo.\n");
                    break;
                }

                calcular_estadisticas(texto, &caracteres, &palabras, &espacios, &lineas);
                printf("\nEstadisticas del texto:\n");
                printf("Caracteres: %d\n", caracteres);
                printf("Palabras: %d\n", palabras);
                printf("Espacios: %d\n", espacios);
                printf("Lineas: %d\n", lineas);
                break;

            case 3:
                if (texto == NULL) {
                    printf("Primero debe cargar un archivo.\n");
                    break;
                }

                frecuencia_vocales(texto, frecuencias);
                printf("\nFrecuencia de vocales:\n");
                printf("a/A: %d\n", frecuencias[0]);
                printf("e/E: %d\n", frecuencias[1]);
                printf("i/I: %d\n", frecuencias[2]);
                printf("o/O: %d\n", frecuencias[3]);
                printf("u/U: %d\n", frecuencias[4]);
                break;

            case 4:
                if (texto == NULL) {
                    printf("Primero debe cargar un archivo.\n");
                    break;
                }

                printf("Ingrese la palabra a buscar: ");
                fgets(buscar, Nombre, stdin);
                buscar[strcspn(buscar, "\n")] = '\0';

                printf("Ingrese la palabra de reemplazo: ");
                fgets(reemplazo, Nombre, stdin);
                reemplazo[strcspn(reemplazo, "\n")] = '\0';

                if (texto_modificado != NULL) {
                    free(texto_modificado);
                }

                texto_modificado = reemplazar_palabra(texto, buscar, reemplazo, &nueva_longitud);
                if (texto_modificado != NULL) {
                    printf("Reemplazo realizado (%ld caracteres).\n", nueva_longitud);
                    printf("Texto modificado (primeros 200 caracteres):\n%.200s...\n", texto_modificado);
                } else {
                    printf("No se encontró la palabra '%s' en el texto.\n", buscar);
                }
                break;

            case 5:
                if (texto == NULL) {
                    printf("Primero debe cargar un archivo.\n");
                    break;
                }

                printf("Ingrese el nombre del archivo de salida (.txt): ");
                fgets(nombre_salida, Nombre, stdin);
                nombre_salida[strcspn(nombre_salida, "\n")] = '\0';

                // Usar texto modificado si existe, sino el original
                const char* texto_a_guardar = (texto_modificado != NULL) ? texto_modificado : texto;
                guardar_resultados(nombre_salida, texto_a_guardar, caracteres, palabras, espacios, lineas, frecuencias);
                break;

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    // Liberar memoria
    if (texto != NULL) {
        free(texto);
    }
    if (texto_modificado != NULL) {
        free(texto_modificado);
    }

    return 0;
}