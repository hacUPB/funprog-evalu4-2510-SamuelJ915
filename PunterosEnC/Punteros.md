## 7. Preguntas de control ##
1. **¿Qué almacena un puntero?**
    
    A) El valor de otra variable.
    
    B) La dirección de memoria de otra variable.
    
    C) Un número aleatorio.
    
    __B) La direccion de memoria en otra variable, el puntero guarda la direccion mas no el contenido en la memoria__
2. **¿Cuál es el operador para obtener la dirección de una variable?**
    
    A) `*`
    
    B) `&`
    
    C) `->`

    __B) Es el operador & (Ampersand)__
    
3. **¿Cómo se llama la operación de acceder al valor apuntado por un puntero?**
    
    A) & (Ampersand)
    
    B) * (Desreferenciación)
    
    C) % (Módulo)

    __B) Desreferenciacion, este asterisco le indica al compilador que se debe acceder al valor que esta guardado en la direccion de memoria que guarda el puntero.__
    
4. **En el contexto de punteros, describa brevemente qué significa ‘paso por referencia’.**
__Es un metodo cuya funcion es pasar la direccion de la memoria del argumento de una funcion a otra, sirve para modificar la variable original en vez de hacer una copia__
5. **Si `ptr` es un puntero a `int`, ¿qué hace `ptr = 5;`?**
    
    A) Asigna 5 al puntero mismo.
    
    B) Almacena 5 en la dirección apuntada por `ptr`.
    
    C) No hace nada.

    __B) Almacena 5 en la direccion del puntero__