# Proyecto 1 - Programación paralela con OpenMP
## Integrantes
- Andrei Portales
- Randy Venegas
- Sebastián Maldonado

## Introduccion
El presente informe es un detallado análisis sobre el proceso de creación de un Screensaver Paralelo en el lenguaje de programación C++. Este programa simula un conjunto de círculos en una ventana, los cuales se mueven y colisionan entre sí utilizando la librería SDL para su visualización.

Este screensaver utiliza diversas bibliotecas para crear una ventana y dibujar círculos aleatorios en ella. Los círculos se mueven en direcciones aleatorias y cambian de dirección cuando alcanzan los límites de la ventana. Para mayor complejidad, se han considerado factores como la velocidad y el color de los círculos, los cuales son también aleatorios.

Además, se ha tomado en cuenta el rebote y el ángulo al que se direcciona cada círculo después de colisionar con otro, creando un efecto realista y dinámico en la visualización de los movimientos. Cada uno de los 500 círculos que se mueven en la pantalla, se comportan de manera independiente y ejecutan las mismas acciones, generando un conjunto de patrones y movimientos creando algo satisfactorio a la vista.

## Antecedentes

La simulación de partículas es un campo de la computación gráfica que se encarga de representar el comportamiento de objetos en movimiento en un espacio tridimensional. Este tipo de simulaciones se utilizan en diversos campos como la física, la ingeniería, la biología y la animación, entre otros.

Para la simulación de partículas, se utilizan diversas técnicas, como la integración numérica, que permite obtener la posición y velocidad de las partículas en función del tiempo, y la detección de colisiones, que permite simular el comportamiento de los objetos al chocar entre sí.

En la simulación de colisiones, existen diversas técnicas como la detección de colisiones por separación de ejes, la detección de colisiones por cajas envolventes y la detección de colisiones por volúmenes de separación.


## OpenMP

*#include "omp.h"*: Esta línea incluye el archivo de cabecera de OpenMP, que es necesario para utilizar las funciones y directivas de OpenMP en el código.

*#pragma omp parallel num_threads(4)*: Esta directiva crea un grupo de hilos para ejecutar en paralelo el bloque de código siguiente. La opción num_threads(4) especifica que se deben crear 4 hilos. Todos los hilos ejecutarán el mismo bloque de código, pero cada hilo tendrá un conjunto diferente de iteraciones del bucle asignado.

*#pragma omp for*: Esta directiva indica que el bucle for inmediatamente siguiente debe ser dividido en "chunks" y distribuido entre los hilos creados por la directiva #pragma omp parallel. Por defecto, OpenMP utiliza un "schedule" estático, lo que significa que las iteraciones del bucle se dividen en partes iguales y se asignan a los hilos.

*#pragma omp for schedule(dynamic)*: Esta directiva es similar a #pragma omp for, pero utiliza un "schedule" dinámico. El "schedule" dinámico asigna iteraciones del bucle a los hilos según estén disponibles, lo que puede ser útil cuando las iteraciones del bucle tienen tiempos de ejecución diferentes. En este caso, se aplica al bucle anidado de verificación de colisiones, donde algunas iteraciones pueden tardar más que otras debido a las colisiones detectadas.

*#pragma omp critical*: Esta directiva marca una sección de código como "crítica", lo que significa que solo un hilo a la vez puede ejecutar esa sección de código. En este caso, se utiliza para proteger la función checkCollision(), que modifica el estado de los objetos Circle. Esto asegura que los hilos no interfieran entre sí al modificar los objetos Circle simultáneamente.

### Instalar el compilador de C++:
```
sudo apt-get install g++
```
### Instalar la biblioteca SDL:
```
sudo apt-get install libsdl2-dev
```
### Como compilar el programa secuencial

    
    gcc main.cpp Circle.cpp Constants.cpp -o main
    

### Como ejecutar el programa secuencial

    
    ./main <cantidad circulos>
    

### Como compilar el programa paralelo

    
    gcc -fopenmp main_par.cpp Circle.cpp Constants.cpp -o main -lSDL2 -lSDL2_image 
    

### Como ejecutar el programa paralelo

    
    ./main <cantidad circulos> <cantidad de hilos>
    


