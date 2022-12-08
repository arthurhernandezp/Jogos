#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
int AUX_WaitEventTimeoutCount (SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	Uint32 depois = 0;
	int isevt = SDL_WaitEventTimeout(evt, *ms);
	if(isevt){
		depois = (SDL_GetTicks() - antes);
		if(*ms < depois) depois = *ms;
		*ms -= depois;		
	}
	return isevt;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "character.bmp");
    assert(img != NULL);

    /* EXECUÇÃO */
    bool continua = true;
    SDL_Event evt;
    int isup = 1;
    int x = -100;
    int espera = 100;
    while (continua) {
        SDL_SetRenderDrawColor(ren, 255,0,255,0);
        SDL_RenderClear(ren);
        SDL_Rect r = { x,50, 100,80 };
        SDL_Rect c;
      	Uint32 antes = SDL_GetTicks();
        int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);       
        if(isevt){       	
		switch (evt.type ) {
		    case SDL_QUIT:
		    	continua = false;
		    	break;		
		}
	
	}
	else{   
		switch(isup){
			case 1:
				c = (SDL_Rect) {   0,64, 30,32 };
			break;
			case 2:
				c = (SDL_Rect) { 125,64, 30,32 };
			break;
			case 3:
				c = (SDL_Rect) { 158,64, 30,32 };
			break;
			case 4:
				c = (SDL_Rect) { 125,64, 30,32 };
			break;
		}
		isup++;
	
		SDL_RenderCopy(ren, img, &c, &r);
		SDL_RenderPresent(ren);
		espera = 250;
		x = (x + 10) % 400;
		if(isup > 4){
			isup = 1;
		}
		
	}
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
