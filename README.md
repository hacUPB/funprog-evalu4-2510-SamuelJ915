# Unidad No. 4

## Información del estudiante  

## Nombre del estudiante: Samuel Andres Jimenez Sanchez 

## Id.: 000209342
---
## Descripción del contenido del repositorio  


En este repositorio vas a encontrar todas las actividades resueltas con respecto a la unidad 4 de fundamentos de programación. En este apartado del codigo vamos a explicar las funciones utilizadas en el reto.

# Explicación del reto final
Definimos "MAX_LENGTH" como reemplazo para malloc en varias partes del codigo porque es mas facil de usar, la usamos para definir un tamaño maximo fijo para los arrays que en este caso son de caracteres utilizados para guardar los nombres de los archivos. La misma variable se usa en los arrays en vez de modificar varios valores en el codigo.

Ahora vamos a analizar como es que el codigo lee los archivos
```
char* leer_archivo(const char* nombre_archivo, long* longitud) {
    // 1. 
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    // 2. 
    fseek(archivo, 0, SEEK_END);  // Mover el cursor al final del archivo
    *longitud = ftell(archivo);    // Obtener la posición actual (que es el tamaño)
    fseek(archivo, 0, SEEK_SET);   // Volver al inicio del archivo

    // 3. 
    char* contenido = (char*)malloc(*longitud + 1); // +1 para el carácter nulo '\0'
    if (contenido == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return NULL;
    }

    // 4. 
    fread(contenido, 1, *longitud, archivo); // Leer 'longitud' bytes
    contenido[*longitud] = '\0';              // Añadir terminador nulo

    // 5. 
    fclose(archivo);
    return contenido;
}
```
## 1. Abrir el archivo en modo lectura ##

Usamos la funcion fopen() para abrir el archivo y en modo lectura con "r"

## 2. Determinar el tamaño del archivo ##

- fseek(archivo, 0, SEEK_END): mueve el puntero al final del archivo
- ftell(archivo): Obtiene la posicion actual
- fseek(archivo, 0, SEEK_SET): Hace que el puntero se devuelva al inicio para volver a leer mas adelante

## 3. Guardar memoria ##

- malloc(*longitud + 1): Asigna memoria suficiente para todo el contenido + 1 byte extra para el carácter nulo ('\0').

- Si malloc falla, cierra el archivo y devuelve NULL.

## 4. Lectura de contenido ##

- fread() lee el archivo completo de una vez.

- Se añade manualmente '\0' al final para formar una cadena de C válida.

## 5. Cierre y retorno ##

- Cierra el archivo con fclose().

- Devuelve el puntero al contenido leído.

### Uso de la memoria dinamica ###
- La memoria se usa con malloc(), por que al llamarla debemos despues liberarla con free() cuando ya no sea necesaria.

El parámetro longitud que es paso por referencia permite al llamante saber el tamaño del archivo leído.

Ahora analicemos el contador de estadisticas del .txt

```
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
```
Lo primero es inicializar los contadores, "en_palabra" lo usé para detectar si el programa lee una palabra o no. El primer if detecta saltos de linea, el else-if cuenta espacios o enters y el ultimo esle cuenta cualquier otro caracter

```
if (texto[i] == '\n') {
    (*lineas)++;          // Incrementa contador de líneas
    if (en_palabra) {     // Si terminaba una palabra
        (*palabras)++;    // Cuenta la palabra
        en_palabra = 0;   // Resetea el flag
    }
}
```

```
else if (texto[i] == ' ' || texto[i] == '\t') {
    (*espacios)++;        // Cuenta como espacio
    if (en_palabra) {     // Si terminaba una palabra
        (*palabras)++;    // Cuenta la palabra
        en_palabra = 0;   // Resetea la banderita
    }
}
```

```
else {
    (*caracteres)++;  // Cuenta carácter válido
    en_palabra = 1;   // Marca que estamos en una palabra
}
```

Seguimos con la funcion frecuencia_vocales() que cuenta las vocales ignorando si son mayusculas o minusculas, los parametros de entrada son "const char* texto" para recibir el texto a analizar y el arreglo "int frecuencias[5]" con 5 porque hay 5 vocales. Pone todos los valores del arreglo "frecuencias" en 0 con el bucle for y al final lo que hace es recorrer letra por letra, convirtiendo cada letra a minuscula con tolower() y la funcion switch para aumentar los contadores correspondientes

```
void frecuencia_vocales(const char* texto, int frecuencias[5]) {
    // Inicializa el arreglo de frecuencias a 0
    for (int i = 0; i < 5; i++) {
        frecuencias[i] = 0;
    }

    // Recorre el texto carácter por carácter
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = tolower(texto[i]); // Convierte a minúscula para uniformidad
        
        switch (c) {
            case 'a': frecuencias[0]++; break;
            case 'e': frecuencias[1]++; break;
            case 'i': frecuencias[2]++; break;
            case 'o': frecuencias[3]++; break;
            case 'u': frecuencias[4]++; break;
        }
    }
}
```

Seguimos con la funcion que sirve para reemplazar palabras
Los parametros que recibe son, el texto, buscar, nueva_longitud y reemplazo. Cuenta cuantas veces aparece la palabra a cambiar con la siguiente funcion:

```
while ((temp = strstr(temp, buscar)) != NULL) {
    ocurrencias++;
    temp += buscar_len;  // Saltar a la siguiente posible coincidencia
}
```

- Despues hay que calcular cuanta memoria se necesita con "nueva_longitud = longitud_original + (ocurrencias * (long_reemplazo - long_buscar))"

- Reemplaza la palabra con un string copiando la palabra a cambiar y usandola en cada coincidencia de la palabra escogida.

- Por ultimo tenemos la funcion que guarda los datos que se explica mas facil viendo linea por linea cada apartado:

```
void guardar_resultados(const char* nombre_archivo,  // Nombre del archivo de salida
                       const char* texto,     // Texto a guardar (original o modificado)
                       int caracteres,              // Total de caracteres
                       int palabras,                // Total de palabras
                       int espacios,                // Total de espacios
                       int lineas,                  // Total de líneas
                       const int frecuencias[5])    // Frecuencia de vocales [a,e,i,o,u]
{
    // 1. Abrir el archivo en modo escritura ("w")
    FILE* archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo de salida.\n");
        return;
    }

    // 2. Escribir las estadísticas generales
    fprintf(archivo, "Estadísticas del texto:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "Total de caracteres: %d\n", caracteres);
    fprintf(archivo, "Total de palabras: %d\n", palabras);
    fprintf(archivo, "Total de espacios: %d\n", espacios);
    fprintf(archivo, "Total de líneas: %d\n\n", lineas);

    // 3. Escribir las frecuencias de vocales
    fprintf(archivo, "Frecuencia de vocales:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "a/A: %d\n", frecuencias[0]);
    fprintf(archivo, "e/E: %d\n", frecuencias[1]);
    fprintf(archivo, "i/I: %d\n", frecuencias[2]);
    fprintf(archivo, "o/O: %d\n", frecuencias[3]);
    fprintf(archivo, "u/U: %d\n\n", frecuencias[4]);

    // 4. Escribir el texto completo
    fprintf(archivo, "Texto:\n");
    fprintf(archivo, "----------------------\n");
    fprintf(archivo, "%s\n", texto);

    // 5. Cerrar el archivo
    fclose(archivo);
    printf("Resultados guardados en %s\n", nombre_archivo);
}
```


_Agradecimientos a Juan David Londoño Hincapie y Samuel Calderon Calderon, experimentados estudiantes de ing. de sistemas de la UPB que me ayudaron a complementar, aprender y optimizar este codigo_