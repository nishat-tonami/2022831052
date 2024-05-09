#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define Screen_Width 550
#define Screen_Height 320

bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer);
void Draw_Solid_Circle(SDL_Renderer* renderer, int center_X, int center_Y, int radius, SDL_Color color);

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    SDL_Event event;
    bool running = true;
    int autoCircleX = 0;
    int autoCircleY = Screen_Height / 2;
    int autoCircleRadius = 35;
    int controlCircleX = Screen_Width / 2;
    int controlCircleY = 20;
    int controlCircleRadius = 30;
    SDL_Color autoCircleColor = {128, 0, 128, 255};
    SDL_Color controlCircleColor = {0, 0, 255, 255};

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        controlCircleY -= 10;
                        break;
                    case SDLK_DOWN:
                        controlCircleY += 10;
                        break;
                    case SDLK_LEFT:
                        controlCircleX -= 10;
                        break;
                    case SDLK_RIGHT:
                        controlCircleX += 10;
                        break;
                }
            }
        }


        autoCircleX += 5;
        if (autoCircleX - autoCircleRadius > Screen_Width) {
            
            autoCircleX = -autoCircleRadius;
        }

    
        int dx = autoCircleX - controlCircleX;
        int dy = autoCircleY - controlCircleY;
        int distanceSquared = dx * dx + dy * dy;
        int radiusSum = autoCircleRadius + controlCircleRadius;
        if (distanceSquared <= radiusSum * radiusSum) {
            autoCircleColor = controlCircleColor = {0, 255, 0, 255};  
        } else {
            autoCircleColor = {128, 0, 128, 255};
            controlCircleColor = {0, 0, 255, 255};  
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        Draw_Solid_Circle(renderer, autoCircleX, autoCircleY, autoCircleRadius, autoCircleColor);
        Draw_Solid_Circle(renderer, controlCircleX, controlCircleY, controlCircleRadius, controlCircleColor);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Has Failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("TASK 103 : Collision of the Circles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width, Screen_Height, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window Creation Has Failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) {
        printf("Renderer Creation Has Failed: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Draw_Solid_Circle(SDL_Renderer* renderer, int center_X, int center_Y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, center_X + x, center_Y + y);
            }
        }
    }
}
