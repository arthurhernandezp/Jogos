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
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_Rect r = { 100,200, 200,200 };
    SDL_RenderDrawRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 0x96,0x4B,0x00,0x00);
    SDL_Rect s = { 160,300, 80,100 };
    SDL_RenderFillRect(ren, &s);
    /*Desenha telhado*/
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
    SDL_RenderDrawLine(ren, 100, 200, 200, 100);
    SDL_RenderDrawLine(ren, 200, 100, 300, 200);
    SDL_RenderDrawLine(ren, 200, 100, 300, 0);
    SDL_RenderDrawLine(ren, 300, 0, 400, 100);
    /*Desenha lado da casa*/
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00); 
    SDL_RenderDrawLine(ren, 300, 400, 400, 300);
    SDL_RenderDrawLine(ren, 300, 200, 400, 100);
    SDL_RenderDrawLine(ren, 400, 300, 400, 100);
    SDL_RenderDrawPoint(ren,100, 400);
    SDL_RenderDrawPoint(ren,50, 50);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
