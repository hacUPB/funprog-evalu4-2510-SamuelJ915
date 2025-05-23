## Ejercicio 1 ##

``` 
#include <stdio.h>

int main() {
    // Declaración e inicialización del arreglo
    int Datos[10] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    
    printf("Elementos del arreglo y sus direcciones de memoria:\n");
    printf("------------------------------------------------\n");
    printf("| Valor | Indice | Direccion de memoria  |\n");
    printf("------------------------------------------------\n");
    
    // Iterar a través del arreglo
    for(int i = 0; i < 10; i++) {
        // Imprimir el valor, índice y dirección de memoria de cada elemento
        printf("| %5d | %6d | %p |\n", Datos[i], i, &Datos[i]);
    }
    
    printf("------------------------------------------------\n");
    
    return 0;
}
```




## Preguntas de Control ##
1. ¿Qué valor contiene el siguiente dato: `dato[5]`, si el arreglo se inicializa de la siguiente manera: `int datos[6] = {5, 82, 41};`?

__Va a tener el valor de cero porque si se inicializan menos valores que los del tamaño del arreglo, los datos demás van a ser cero por defecto__

2. ¿Cómo determinar el número de elementos en un arreglo cuando su tamaño no se especifica explícitamente?

__Para determinar el numero cuando no tenemos el tamaño se usa la funcion sizeof() que nos dice el tamaño total del arreglo__

## Preguntas de compresión ##

1. ¿Qué se pasa realmente a la función cuando enviamos un arreglo como parámetro?

__Se pasa un puntero que apunta al primer lugar del arreglo__

2. ¿Qué diferencia hay entre declarar el parámetro como `int arr[]` y `int *arr`?

__cuando se usa arr[], se declara un array como parametro de funcion. arr*, declara un puntero a un valor entero.__

3. ¿Qué implicaciones tiene esto sobre la modificación del arreglo dentro de la función?

__Modificarlo implica que si una funcion cambia un arreglo que se le pasa como argumento, el arreglo original en el codigo que llama a la original tambien cambia__

## Preguntas finales para reforzar el apredizaje ##

1. ¿Cuál es exactamente la diferencia entre un arreglo y un puntero?

__Un arreglo es una estructura de datos que guarda varios elementos del mismo tipo y un puntero es una variable que guarda la direccion de memoria de otro elemento__

2. ¿Cómo están almacenados en la memoria los elementos de una matriz?

__Se guardar de manera ordenada, uno despues del otro ocupando espacios de memoria de manera consecutiva__

3. ¿Qué precauciones se deben tomar al usar punteros para recorrer arreglos?

__Asegurarse de que un puntero apunte a un valor dentro del rango de un arreglo, tener cuidado con no excederse con el tamaño de un arreglo, cuidarse de usar punteros que no apuntes a ninguna direccion de memoria valida.__

## Ejercicios Practicos ##
### Ejercicio1 ###

```
#include <stdio.h>

int main() {
    
    int numeros[10];
    
    // Rellenarlo con numeros consecutivos desde el 11 hasta el 20
    for (int i = 0; i < 10; i++) {
        numeros[i] = 11 + i;
    }
    
    printf("Array en orden descendente:\n");
    for (int i = 9; i >= 0; i--) {
        printf("%d ", numeros[i]);
    }
    printf("\n");
    
    return 0;
}
```
### Ejercicio2 ###

```
#include <stdio.h>

int main() {
    
    int pares[5];
    
    // Rellenar el array con números pares del 2 al 10
    for (int i = 0; i < 5; i++) {
        pares[i] = 2 * (i + 1); // Genera 2, 4, 6, 8, 10
    }
    
    // Imprimir los valores en orden ascendente
    printf("Números pares :\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", pares[i]);
    }
    printf("\n");
    
    return 0;
}
```

### Ejercicio3 ###

```
#include <stdio.h>

int main() {
    int numeros[10];
    int suma = 0;
    int resta;
    
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }
    
    // Calcular operaciones acumuladas
    resta = numeros[0]; // Inicializamos con el primer valor
    for (int i = 1; i < 10; i++) {
        resta -= numeros[i];
    }
    
    for (int i = 0; i < 10; i++) {
        suma += numeros[i];
        multiplicacion *= numeros[i];
    }
    
    // Mostrar resultados
    printf("\nResultados:\n");
    printf("Suma total: %d\n", suma);
    printf("Resta acumulada: %d\n", resta);
    printf("Multiplicación acumulada: %lld\n", multiplicacion);
    
    return 0;
}
```
### Ejercicio4 ###

```
#include <stdio.h>

int main() {
    int numeros[10];
    int suma = 0;
    int resta;
    
    // Leer 10 números desde teclado
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }
    
    // Calcular operaciones acumuladas
    resta = numeros[0]; // Inicializamos con el primer valor
    for (int i = 1; i < 10; i++) {
        resta -= numeros[i];
    }
    
    for (int i = 0; i < 10; i++) {
        suma += numeros[i];
        multiplicacion *= numeros[i];
    }
    
    // Mostrar resultados
    printf("\nResultados:\n");
    printf("Suma total: %d\n", suma);
    printf("Resta acumulada: %d\n", resta);
    printf("Multiplicación acumulada: %lld\n", multiplicacion);
    
    return 0;
}
```