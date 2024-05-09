#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define Screen_Width 550
#define Screen_Height 320

bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer);
void Draw_Solid_Circle(SDL_Renderer* renderer, int center_X, int center_Y, int radius);

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1; 
    }

    SDL_Event event;
    bool running = true;
    int radius = 40;
    int radiusIncrease = 10; 
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }


        radius += radiusIncrease;

        
        if (radius + Screen_Width / 2 >= Screen_Width || radius + Screen_Height / 2 >= Screen_Height) {
            radius = 40; 
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
        Draw_Solid_Circle(renderer, Screen_Width / 2, Screen_Height / 2, radius);

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

    *window = SDL_CreateWindow("TASK 102 : Expanding Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width, Screen_Height, SDL_WINDOW_SHOWN);
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

void Draw_Solid_Circle(SDL_Renderer* renderer, int center_X, int center_Y, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, center_X + x, center_Y + y);
            }
        }
    }
}
