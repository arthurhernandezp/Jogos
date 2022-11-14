#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r1 = { 40,20, 20,20 };
    SDL_Rect r2 = { 300,80, 40,40 };
    SDL_Rect r3 = { 250,250, 30,30 };
    int espera = 500;
    bool continua = true;
    while (continua) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r1);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren, &r2);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(ren, &r3);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        r1.y -= 5;
                        break;
                    case SDLK_DOWN:
                        r1.y += 5;
                        break;
                    case SDLK_LEFT:
                        r1.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        r1.x += 5;
                        break;
                }
            }
            if(evt.type == SDL_MOUSEMOTION){
	 	int x, y;	    		
		SDL_GetMouseState(&x,&y);
		r3.x = x;
		r3.y =y;
	    } 
        } 
        else {
            espera = 500;
            r2.y += 2;
        }
        switch (evt.type ) {
            case SDL_QUIT:
            	continua = false;
            	break;
            case SDL_KEYDOWN:
            	if(evt.key.keysym.sym == SDLK_F4){
            		if(evt.key.keysym.mod == KMOD_LALT){
		    		continua = false;
		    		break;	
            		}		
		}
        }
    }
  }	

