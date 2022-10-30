#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x50);
    SDL_Rect r = { 40,20, 10,10 };
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 0xFF,0x69,0xB4,0x00);
    SDL_RenderDrawLine(ren, 100, 100, 100, 200);
    SDL_RenderDrawLine(ren, 100, 200, 200, 200);
    SDL_RenderDrawLine(ren, 100, 100, 200, 200);
    SDL_RenderDrawPoint(ren,100, 400);
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00); 
    SDL_RenderDrawLine(ren, 400, 100, 400, 200);
    SDL_RenderDrawLine(ren, 400, 200, 200, 200);
    SDL_RenderDrawLine(ren, 400, 100, 200, 200);   
    
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF); 
    SDL_RenderDrawLine(ren, 100, 100, 200, 200);
    SDL_RenderDrawLine(ren, 200, 200, 400, 100);
    SDL_RenderDrawLine(ren, 100, 100, 400, 100);
    
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
