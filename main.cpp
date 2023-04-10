#include <SDL.h>

#include "Circle.cpp"

#define BALLS 9

int main(int argc, char *argv[]) {
    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Crear ventana
    SDL_Window *window = SDL_CreateWindow("Proyecto 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Crear renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Crear círculo

    Circle circleArray[BALLS];
    int arrayLength = sizeof(circleArray) / sizeof(Circle);

    // Esperar evento de salida
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        for (int i = 0; i < arrayLength; i++) {
            circleArray[i].move();

            for (int j = 0; j < arrayLength; j++) {
                if (i != j) {
                    circleArray[i].checkCollision(circleArray[j]);
                }
            }

        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar círculos
        for (int i = 0; i < arrayLength; i++) {
            circleArray[i].draw(renderer);
        }

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        // Esperar un poco antes de actualizar la pantalla nuevamente
        SDL_Delay(1000 / 60);
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}