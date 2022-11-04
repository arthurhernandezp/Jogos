#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    /* EXECUÇÃO */
    int variavelX = 1;
    int variavelY = 1;
    SDL_Rect r = { 150,200, 50,50 };
    while (r.x != 1000) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        if(r.y == 350 || r.y == 0){
        	variavelY = variavelY * (-1);
        }
        else if(r.x == 0 || r.x == 350){
        	variavelX = variavelX * (-1);
        }
        r.y = r.y + 5*variavelY;
        r.x = r.x + 5*variavelX; 
        SDL_RenderPresent(ren);
        SDL_Delay(300);
    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
