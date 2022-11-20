#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <assert.h>
#include <stdbool.h>
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
    int variavelX = 1;
    int variavelY = 1;
    int espera = 0;
    SDL_Rect r = { 150,200, 50,50 };
    bool continua = true;
    /* EXECUÇÃO */
    while (continua) {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, & r);
        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout( & evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            switch (evt.type) {
            case SDL_QUIT:
                continua = false;
                break;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                case SDLK_F4:
                    if (evt.key.keysym.mod == KMOD_LALT) {
                        continua = false;
                        break;
                    }
                    case SDLK_UP:
                        if (r.y > 0) {
                            r.y -= 3;
                        }
                        break;
                    case SDLK_DOWN:
                        if (r.y < 350) {
                            r.y += 3;
                        }
                        break;
                    case SDLK_LEFT:
                        if (r.x > 0) {
                            r.x -= 3;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (r.x < 350) {
                            r.x += 3;
                        }
                        break;
                }
            }
        } else {
            espera = 500;
            if (r.x == 0 && r.y == 0 || r.x == 0 && r.y == 350 || r.x == 350 && r.y == 0 || r.x == 350 && r.y == 350) {
                variavelY = variavelY * (-1);
                variavelX = variavelX * (-1);
                r.x = r.x + 1;
            } else if (r.y >= 350 || r.y <= 0) {
                variavelY = variavelY * (-1);
            } else if (r.x <= 0 || r.x >= 350) {
                variavelX = variavelX * (-1);
            }
            r.y = r.y + 5 * variavelY;
            r.x = r.x + 5 * variavelX;
            SDL_RenderPresent(ren);
        }
    }
}
