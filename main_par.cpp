#include <SDL.h>
#include "Circle.cpp"
#include "omp.h"

#define THREAD_NUM 4
#define BALL_COUNT 700


int main(int argc, char *argv[]) {
    int ballCount = BALL_COUNT;
    int threads = THREAD_NUM;
    if (argc > 1) {
        ballCount = atoi(argv[1]);
    }
    if (argc > 2) {
        threads = atoi(argv[2]);
    }

    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Crear ventana
    SDL_Window *window = SDL_CreateWindow("Proyecto 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Crear renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Crear círculos
    Circle circleArray[ballCount];

    // Esperar evento de salida
    SDL_Event event;
    bool quit = false;

    // Inicializar temporizador para FPS
    Uint32 frameStart, frameTime;
    int frameCounter = 0;
    Uint32 frameDelay = 1000 / 120;

    Uint32 fpsTimer = SDL_GetTicks();

    double delta_per_second = 0.0;

    while (!quit) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        double start = omp_get_wtime();
        // Mover círculos
        #pragma omp parallel num_threads(threads) default(none) shared(circleArray, ballCount)
        {
        #pragma omp for
        for (int i = 0; i < ballCount; i++) {
            circleArray[i].move();
        }

        #pragma omp barrier

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < ballCount - 1; i++) {
            for (int j = i + 1; j < ballCount; j++) {
                    circleArray[i].checkCollision(circleArray[j]);
            }
        }
        }
        double end = omp_get_wtime();
        double delta = end - start;
        delta_per_second += delta;


        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar círculos
        for (int i = 0; i < ballCount; i++) {
            circleArray[i].draw(renderer);
        }

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        // Calcular tiempo por cuadro y ajustar el delay
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        // Incrementar contador de cuadros
        frameCounter++;

        // Calcular e imprimir FPS cada segundo
        if (SDL_GetTicks() - fpsTimer >= 1000) {
            SDL_Log("FPS: %d, sphere calculation time: %lf, thread_num: %i", frameCounter, delta_per_second / frameCounter, threads);
            frameCounter = 0;
            delta_per_second = 0.0;
            fpsTimer = SDL_GetTicks();
        }
    }

    // limpiar variables
    for (int i = 0; i < ballCount; i++) {
        circleArray[i].~Circle();
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
