## Actividad 1: Investigacion Practica ##
### Para que sirve ###
__De string.h__

strlen: Esta funcion devuelve la longitud de un string (cadena de caracteres)

strcpy: Copia los caracteres de un string en la memoria de otro string

strncpy: Copia el numero de caracteres de un string en la memoria de otro string

strcat: Adjunta un string al final de otro string

strncat: Adjunta el numero de caracteres de un string al final de otro

strcmp:  Compara el valor ASCII de los caracteres en dos strings para determinar cual tiene el mayor valor

strchr: Devuelve el puntero al primer caracter que aparece en un string  

strstr: La función busca la primera aparición de un string en el otro.

strtok: Divide un string en varias piezas usando delimitadores 

__De ctype.h__

isalpha: Revisa si un caracter es una letra

isdigit: Revisa si un caracter en un digito decimal

isalnum: Revisa si un caracter es alfanumerico

islower: Revisa si un caracter es minuscula

isupper: Revisa si un caracter es mayuscula

tolower: Devuelve en minuscula un caracter

toupper: Devuelve en mayuscula un caracter

### Prototipo de la funcion  ###

size_t strlen("Puntero");

char *strcpy(char *destination, const char *source);

char *strncpy(char *string1, const char *string2, size_t count);

char *strcat(char *string1, const char *string2);

strncat(void * destination, void * source, size_t size);

int strcmp(const char *string1, const char *string2);

char *strchr(const char *string, int c);

char *strstr(const char *string1, const char *string2);

char *strtok(char *string1, const char *string2);

int isalpha (Character)
int Character;

int isdigit (Character)
int Character;

int isalnum (Character)
int Character;

int islower (Character)
int Character;

int isupper (Character)
int Character;

int tolower(int C);

int toupper(int c);

### Parametros que recibe ###

strlen: La cadena a analizar

strcpy: La cadena inicial y su nuevo valor (otra cadena)

strcat: La cadena inicial y la que se le quiere añadir

### Ejemplo funcional ###