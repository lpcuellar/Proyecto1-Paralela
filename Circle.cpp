#include <SDL.h>
#include <cmath>
#include "Constants.cpp"

class Circle {
private:
    int centerX;
    int centerY;
    int xVel = MOVE_SPEED;
    int yVel = MOVE_SPEED;
    int radius = CIRCLE_RADIUS;
    SDL_Color color;

public:
    Circle() {
        randomPosition();
        randomColor();
    }

    /**
     * Genera un color aleatorio para el círculo
     */
    void randomColor() {
        color.r = rand() % 255;
        color.g = rand() % 255;
        color.b = rand() % 255;
    }

    /**
     * Genera una posición aleatoria para el círculo
     */
    void randomPosition() {
        centerX = radius + rand() % (WINDOW_WIDTH - 2 * radius);
        centerY = radius + rand() % (WINDOW_HEIGHT - 2 * radius);

        xVel = rand() % (2 * MOVE_SPEED) - MOVE_SPEED;
        yVel = rand() % (2 * MOVE_SPEED) - MOVE_SPEED;
    }


    /**
     * Esta funcion se encarga de mover cada circulo en el plano 2d
     * @param renderer
     */
    void move() {
        centerX += xVel;
        centerY += yVel;

        if (centerX - radius <= 0) {
            centerX = radius * 2;
            xVel = abs(xVel);
        } else if (centerX + radius >= WINDOW_WIDTH) {
            centerX = WINDOW_WIDTH - radius * 2;
            xVel = -abs(xVel);
        }

        if (centerY - radius <= 0) {
            centerY = radius;
            yVel = abs(yVel);
        } else if (centerY + radius >= WINDOW_HEIGHT) {
            centerY = WINDOW_HEIGHT - radius;
            yVel = -abs(yVel);
        }

        if (std::abs(xVel) < MOVE_SPEED) {
            if (xVel == 0) {
                xVel = rand() % 2 == 0 ? -MOVE_SPEED : MOVE_SPEED;
            } else {
                xVel = xVel <= 0 ? -MOVE_SPEED : MOVE_SPEED;
            }
        }

        if (std::abs(yVel) < MOVE_SPEED) {
            if (yVel == 0) {
                yVel = rand() % 2 == 0 ? -MOVE_SPEED : MOVE_SPEED;
            } else {
                yVel = yVel < 0 ? -MOVE_SPEED : MOVE_SPEED;
            }
        }
    }

    /**
     * Esta funcion se encarga de revisar colisiones entre circulos y asi mismo poder calcular la nueva velocidad y la trayectoria
     * @param renderer
     */
    void checkCollision(Circle& other) {
        int dx = centerX - other.centerX;
        int dy = centerY - other.centerY;
        int radii = radius + other.radius;

        if ((dx * dx) + (dy * dy) <= radii * radii) {
            float nx = dx / std::sqrt(dx * dx + dy * dy);
            float ny = dy / std::sqrt(dx * dx + dy * dy);

            float dot = xVel * nx + yVel * ny;
            float dotOther = other.xVel * nx + other.yVel * ny;

            float dx = (dotOther - dot) * nx;
            float dy = (dotOther - dot) * ny;

            xVel += dx;
            yVel += dy;

            other.xVel -= dx;
            other.yVel -= dy;

            // Calcular la distancia que se solapan los círculos
            float overlap = radii - std::sqrt((dx * dx) + (dy * dy));

            // Ajustar las posiciones de los círculos para que no se solapen
            centerX += overlap * nx * 0.5;
            centerY += overlap * ny * 0.5;
            other.centerX -= overlap * nx * 0.5;
            other.centerY -= overlap * ny * 0.5;

            // Verificar si los círculos están dentro de la ventana
            if (centerX - radius < 0) centerX = radius * 2;
            if (centerX + radius > WINDOW_WIDTH) centerX = WINDOW_WIDTH - radius * 2;
            if (centerY - radius < 0) centerY = radius * 2;
            if (centerY + radius > WINDOW_HEIGHT) centerY = WINDOW_HEIGHT - radius * 2;

            if (other.centerX - other.radius < 0) other.centerX = other.radius * 2;
            if (other.centerX + other.radius > WINDOW_WIDTH) other.centerX = WINDOW_WIDTH - other.radius * 2;
            if (other.centerY - other.radius < 0) other.centerY = other.radius * 2;
            if (other.centerY + other.radius > WINDOW_HEIGHT) other.centerY = WINDOW_HEIGHT - other.radius * 2;
        }
    }


    /**
     * Esta funcion se encarga de dibujar cada circulo en el plano 2d
     * @param renderer
     */
    void draw(SDL_Renderer* renderer) {
        int r2 = radius * radius;

        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= r2) {
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
                }
            }
        }
    }
};

