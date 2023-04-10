#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <cmath>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int MOVE_SPEED = 5;
const int GRAVITY = 1;

class Circle
{
private:
    int centerX;
    int centerY;
    int centerZ;
    int xVel = MOVE_SPEED;
    int yVel = MOVE_SPEED;
    int zVel = MOVE_SPEED;
    int radius;
    SDL_Color color;

public:
    Circle(int r, int red, int green, int blue) : radius(r),
                                                  color({red, green, blue, 255})
    {
        randomPosition();
    }

    void randomPosition()
    {
        centerX = rand() % WINDOW_WIDTH;
        centerY = rand() % WINDOW_HEIGHT;
        centerZ = rand() % WINDOW_WIDTH;
    }

    void move()
    {
        centerX += xVel;
        centerY += yVel;
        centerZ += zVel;
        if (centerX - radius < 0 || centerX + radius > WINDOW_WIDTH)
        {
            xVel = -xVel;
        }
        if (centerY - radius < 0 || centerY + radius > WINDOW_HEIGHT)
        {
            yVel = -yVel;
        }
        if (centerZ - radius < 0 || centerZ + radius > WINDOW_WIDTH)
        {
            zVel = -zVel;
        }

        SDL_Log("centerX: %d, centerY: %d, centerZ: %d", centerX, centerY, centerZ);
    }

    void draw(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        float porcetage = ((float)centerZ / (float)WINDOW_WIDTH);
        float scaled_radius = radius * (porcetage < 0.5 ? 0.5 : porcetage); // Calcula el radio escalado
        SDL_Log("scaled_radius: %d", scaled_radius);
        for (int i = 0; i < scaled_radius * 2; i++)
        {
            for (int j = 0; j < scaled_radius * 2; j++)
            {
                int dx = scaled_radius - i;
                int dy = scaled_radius - j;
                if (std::sqrt(dx * dx + dy * dy) <= scaled_radius)
                {
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy); //
                }
            }
        }
    }
};

int main(int argc, char *argv[])
{
    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Crear ventana
    SDL_Window *window = SDL_CreateWindow("Proyecto 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Crear renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Crear círculo
    Circle circle(15, 255, 0, 0);
    Circle circle1(15, 0, 255, 0);
    Circle circle2(15, 0, 0, 255);

    // Esperar evento de salida
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Mover círculo
        circle.move();
        circle1.move();
        circle2.move();

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar círculo
        circle.draw(renderer);
        circle1.draw(renderer);
        circle2.draw(renderer);

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        // Esperar un poco antes de actualizar la pantalla nuevamente
        SDL_Delay(10);
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}