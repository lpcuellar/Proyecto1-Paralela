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

    void randomColor() {
        color.r = rand() % 255;
        color.g = rand() % 255;
        color.b = rand() % 255;
    }

    void randomPosition() {
        centerX = rand()  % WINDOW_WIDTH;
        centerY = rand() % WINDOW_HEIGHT;

        if (centerX - radius < 0 || centerX + radius > WINDOW_WIDTH) {
            xVel = -xVel;
        }

        if (centerY - radius < 0 || centerY + radius > WINDOW_HEIGHT) {
            yVel = -yVel;
        }
    }

    void move() {
        centerX += xVel;
        centerY += yVel;

        if (centerX - radius <= 0) {
            centerX = radius;
            xVel = -xVel;
        } else if (centerX + radius >= WINDOW_WIDTH) {
            centerX = WINDOW_WIDTH - radius;
            xVel = -xVel;
        }

        if (centerY - radius <= 0) {
            centerY = radius;
            yVel = -yVel;
        } else if (centerY + radius >= WINDOW_HEIGHT) {
            centerY = WINDOW_HEIGHT - radius;
            yVel = -yVel;
        }

        if (std::abs(xVel) < MOVE_SPEED) {
            xVel = xVel < 0 ? -MOVE_SPEED : MOVE_SPEED;
        }

        if (std::abs(yVel) < MOVE_SPEED) {
            yVel = yVel < 0 ? -MOVE_SPEED : MOVE_SPEED;
        }
    }

    void checkCollision(Circle& other) {
        int dx = centerX - other.centerX;
        int dy = centerY - other.centerY;
        int radii = radius + other.radius;

        if ((dx * dx) + (dy * dy) <= radii * radii) {
            SDL_Log("Collision");

            float nx = dx / std::sqrt(dx * dx + dy * dy);
            float ny = dy / std::sqrt(dx * dx + dy * dy);

            float p = 2 * (xVel * nx + yVel * ny - other.xVel * nx - other.yVel * ny) / (1 + 1);

            float dot = xVel * nx + yVel * ny;
            float dotOther = other.xVel * nx + other.yVel * ny;

            float dx = (dotOther - dot) * nx;
            float dy = (dotOther - dot) * ny;

            xVel += dx;
            yVel += dy;

            other.xVel -= dx;
            other.yVel -= dy;

            while ((dx * dx) + (dy * dy) <= radii * radii) {
                centerX += xVel;
                centerY += yVel;
                other.centerX += other.xVel;
                other.centerY += other.yVel;
                dx = centerX - other.centerX;
                dy = centerY - other.centerY;
            }
        }
    }


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
