# Proyecto 1 - Programación paralela con OpenMP

## Integrantes

-   Luis Pedro Cuellar
-   Maria Jose Morales
-   Maria Isabel Montoya
-   Jose Jorge Perez

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
