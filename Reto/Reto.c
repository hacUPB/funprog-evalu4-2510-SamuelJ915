#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

// Declaraciones de funciones 
char* leer_archivo(const char* nombre_archivo, long* longitud);
void calcular_estadisticas(const char* texto, int* caracteres, int* palabras, int* espacios, int* lineas);
void frecuencia_vocales(const char* texto, int frecuencias[5]);
char* reemplazar_palabra(const char* texto, const char* buscar, const char* reemplazo, long* nueva_longitud);
void guardar_resultados(const char* nombre_archivo, const char* texto, int caracteres, int palabras, int espacios, int lineas, const int frecuencias[5]);

int main() {
    char* texto = NULL;
    long longitud = 0;
    char nombre_archivo[MAX_LENGTH];
    char nombre_salida[MAX_LENGTH];
    int opcion;
    int caracteres, palabras, espacios, lineas;
    int frecuencias[5];
    char buscar[MAX_LENGTH], reemplazo[MAX_LENGTH];
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
                fgets(nombre_archivo, MAX_LENGTH, stdin);
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
                fgets(buscar, MAX_LENGTH, stdin);
                buscar[strcspn(buscar, "\n")] = '\0';

                printf("Ingrese la palabra de reemplazo: ");
                fgets(reemplazo, MAX_LENGTH, stdin);
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
                fgets(nombre_salida, MAX_LENGTH, stdin);
                nombre_salida[strcspn(nombre_salida, "\n")] = '\0';

                // Usar texto modificado si existe, sino el original
                const char* texto_a_guardar = (texto_modificado != NULL) ? texto_modificado : texto;
    
                // Recalcular estadísticas para el texto que vamos a guardar
                calcular_estadisticas(texto_a_guardar, &caracteres, &palabras, &espacios, &lineas);
                frecuencia_vocales(texto_a_guardar, frecuencias);
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

// Implementaciones de las funciones

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

// Función para calcular estadísticas del texto
void calcular_estadisticas(const char* texto, int* caracteres, int* palabras, int* espacios, int* lineas) {
    // Inicializamos los contadores
    *caracteres = 0;
    *palabras = 0;
    *espacios = 0;
    *lineas = 1; // Siempre hay al menos una línea

    // Recorremos el texto letra por letra
    int en_palabra = 0; // Funcion para saber si estamos dentro de una palabra
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            (*lineas)++;
            if (en_palabra) {
                (*palabras)++;
                en_palabra = 0;
            }
        } else if (texto[i] == ' ' || texto[i] == '\t') {
            (*espacios)++;
            if (en_palabra) {
                (*palabras)++;
                en_palabra = 0;
            }
        } else {
            (*caracteres)++;
            en_palabra = 1;
        }
    }

    // Contar la última palabra si el texto no termina con espacio o salto de línea
    if (en_palabra) {
        (*palabras)++;
    }
}

// Función para calcular frecuencia de vocales
void frecuencia_vocales(const char* texto, int frecuencias[5]) {
    for (int i = 0; i < 5; i++) {
        frecuencias[i] = 0;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        char c = tolower(texto[i]);
        switch (c) {
            case 'a': frecuencias[0]++; break;
            case 'e': frecuencias[1]++; break;
            case 'i': frecuencias[2]++; break;
            case 'o': frecuencias[3]++; break;
            case 'u': frecuencias[4]++; break;
        }
    }
}

// Función para reemplazar palabras en el texto
char* reemplazar_palabra(const char* texto, const char* buscar, const char* reemplazo, long* nueva_longitud) {
    int buscar_len = strlen(buscar);
    int reemplazo_len = strlen(reemplazo);

    // Contar ocurrencias para calcular el nuevo tamaño
    int ocurrencias = 0;
    const char* temp = texto;
    while ((temp = strstr(temp, buscar)) != NULL) {
        ocurrencias++;
        temp += buscar_len;
    }

    // Calcular nueva longitud
    *nueva_longitud = strlen(texto) + ocurrencias * (reemplazo_len - buscar_len);
    char* nuevo_texto = (char*)malloc(*nueva_longitud + 1);
    if (nuevo_texto == NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    // Realizar el reemplazo
    char* ptr = nuevo_texto;
    const char* inicio = texto;
    temp = texto;
    while ((temp = strstr(temp, buscar)) != NULL) {
        // Copiar parte anterior a la palabra
        int len = temp - inicio;
        strncpy(ptr, inicio, len);
        ptr += len;

        // Copiar reemplazo
        strcpy(ptr, reemplazo);
        ptr += reemplazo_len;

        // Avanzar
        temp += buscar_len;
        inicio = temp;
    }

    // Copiar el resto del texto
    strcpy(ptr, inicio);
    return nuevo_texto;
}

// Función para guardar resultados en archivo
void guardar_resultados(const char* nombre_archivo, const char* texto, int caracteres, int palabras, 
                        int espacios, int lineas, const int frecuencias[5]) {
    FILE* archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo de salida.\n");
        return;
    }

    fprintf(archivo, "Estadísticas del texto:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "Total de caracteres: %d\n", caracteres);
    fprintf(archivo, "Total de palabras: %d\n", palabras);
    fprintf(archivo, "Total de espacios: %d\n", espacios);
    fprintf(archivo, "Total de líneas: %d\n\n", lineas);

    fprintf(archivo, "Frecuencia de vocales:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "a/A: %d\n", frecuencias[0]);
    fprintf(archivo, "e/E: %d\n", frecuencias[1]);
    fprintf(archivo, "i/I: %d\n", frecuencias[2]);
    fprintf(archivo, "o/O: %d\n", frecuencias[3]);
    fprintf(archivo, "u/U: %d\n\n", frecuencias[4]);

    fprintf(archivo, "Texto:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "%s\n", texto);

    fclose(archivo);
    printf("Resultados guardados en %s\n", nombre_archivo);
}