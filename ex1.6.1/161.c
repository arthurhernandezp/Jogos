#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL2_gfxPrimitives.h>

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
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Rect r3 = { 40,400, 40,40 };
    int espera = 500;
    bool continua = true;
    bool selecionado = false;
    bool arrastado = false;
    bool cancelado = false;
    int mensagem = false;
    int x, y, dx, dy,xAntes,yAntes,xDepois,yDepois = 0;
    
     /* EXECUÇÃO */
    while (continua) {
	SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
	SDL_RenderFillRect(ren, &r3);
	if(!selecionado && r3.x == xAntes && r3.x !=xDepois && !cancelado && r3.y == yAntes && r3.y != yDepois) stringRGBA(ren, 50, 50, "Clicado...", 0, 255, 0, 255);
	else if(!selecionado && arrastado && !cancelado &&  xAntes != xDepois) stringRGBA(ren, 50, 50, "Arrastado..", 0, 255, 0, 255);
	
	SDL_RenderPresent(ren);
	SDL_Event evt;       
	if (AUX_WaitEventTimeoutCount(&evt,&espera)) {		 
		switch (evt.type){
			case SDL_KEYDOWN:	   	
				switch (evt.key.keysym.sym){  
				    case SDLK_ESCAPE:
				    	if(selecionado && r3.x != xAntes && r3.y != yAntes ){ 
						r3.x = xAntes;
						r3.y = yAntes;	
						selecionado = false;
						arrastado = false;
						cancelado = true;
					}
				     break;	
				}break;
			 	
			case SDL_MOUSEBUTTONDOWN:
				if(evt.button.button==SDL_BUTTON_LEFT){
					SDL_GetMouseState(&x,&y);
					if(x > r3.x && x < r3.x + r3.w && y > r3.y && y < r3.y + r3.h){
						selecionado = true;
						cancelado = false;
					    	dx=r3.x-x;
						dy=r3.y-y;
						xAntes = r3.x;
						yAntes = r3.y;
					 }
					 else{
					 	selecionado = false;
						cancelado = true;
					 } 
					 break;
				}
			case SDL_MOUSEBUTTONUP:
				if(evt.button.button==SDL_BUTTON_LEFT){
					SDL_GetMouseState(&x,&y);
					if(evt.button.state==SDL_RELEASED){
						selecionado=false;
						if(x > r3.x && x < r3.x + r3.w && y > r3.y && y < r3.y + r3.h){
							 arrastado = true;
							 xDepois = x;
							 yDepois = y;
						 }
					}
					break;
				}
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x,&y);
				if(r3.x <= 460 && r3.y <= 460 && selecionado){
					r3.x=x+dx;
					r3.y = y+dy;
					arrastado = false;
				}
			break;

		}
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
	        
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);  
}
