#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("SDl cant start %s", SDL_GetError());
    exit(1);
}
SDL_Window *window = SDL_CreateWindow("SDL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 440, 360, 0);
if (window == NULL) {
    SDL_Log("Window cant be generated %s", SDL_GetError());
    exit(1);
}
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
if (renderer == NULL) {
    SDL_Log("Renderer cannot be generated %s", SDL_GetError());
    exit(1);
}
SDL_RenderClear(renderer);


int x, y, r;
r = 50;


x = 100;
y = 100;
circleRGBA(renderer, x, y, r, 255, 0, 0, 255);
circleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);
circleRGBA(renderer, x + r * cos(3.1415 / 3), y - r * sin(3.1415 / 3), r, 0, 0, 255, 255);


x = 280;
y = 100;
aacircleRGBA(renderer, x, y, r, 255, 0, 0, 255);
aacircleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);
aacircleRGBA(renderer, x + r * cos(3.1415 / 3), y - r * sin(3.1415 / 3), r, 0, 0, 255, 255);


x = 100;
y = 280;
filledCircleRGBA(renderer, x, y, r, 255, 0, 0, 255);
filledCircleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);
filledCircleRGBA(renderer, x + r * cos(3.1415 / 3), y - r * sin(3.1415 / 3), r, 0, 0, 255, 255);

x = 280;
y = 280;
filledCircleRGBA(renderer, x, y, r, 255, 0, 0, 96);
filledCircleRGBA(renderer, x + r, y, r, 0, 255, 0, 96);
filledCircleRGBA(renderer, x + r * cos(3.1415 / 3), y - r * sin(3.1415 / 3), r, 0, 0, 255, 96);


stringRGBA(renderer, 110, 350, "Press the x to exit", 255, 255, 255, 255);

SDL_RenderPresent(renderer);


SDL_Event ev;
while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    /* SDL_RenderPresent(renderer); - in case of MacOS Mojave  */
}

SDL_Quit();

return 0;
