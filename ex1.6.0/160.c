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
    SDL_Rect r1 = { 40,50, 40,40 };
    SDL_Rect r2 = { 40,225, 40,40 };
    SDL_Rect r3 = { 40,400, 40,40 };
    SDL_Rect boxQuit = {20,350,220,50};
    SDL_Rect boxRestart = {260,350,220,50};
    int espera = 500;
    bool continua = true;
    bool jogo = true;
    bool fimdejogo = false;
    bool selecionado = false;
    int yC = 0;
    int vencedor = 0;
    int x, y, dx, dy;
     /* EXECUÇÃO */
    while(jogo){
	    while (continua) {
		SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
		SDL_RenderClear(ren);
		//Linha de chegada
		for(int i = 1; i <= 10; i++){
			if(i % 2 != 0){
				boxRGBA(ren,400,yC,450,yC + 50,0,0,0,255);
				boxRGBA(ren,450,yC,500,yC + 50,255,255,255,255);
			}
			else{
				boxRGBA(ren,450,yC,500,yC + 50,0,0,0,255);
				boxRGBA(ren,400,yC,450,yC + 50,255,255,255,255);
			}
			yC+=50;
			boxRGBA(ren,400,0,400.1,500,0,0,0,255);
			if(yC == 500) yC = 0;
		}
		SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
		SDL_RenderFillRect(ren, &r1);
		SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
		SDL_RenderFillRect(ren, &r2);
		SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
		SDL_RenderFillRect(ren, &r3);
		SDL_RenderPresent(ren);
		SDL_Event evt;       
		if (AUX_WaitEventTimeoutCount(&evt,&espera)) {		 
			switch (evt.type){
				case SDL_KEYDOWN:
					if(r1.x < 460 && r1.y < 460){         	
						switch (evt.key.keysym.sym){  
						    case SDLK_RIGHT:
							r1.x += 5;
							break;
						}
			 		}
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x,&y);
					if(x > r3.x && x < r3.x + r3.w && y > r3.y && y < r3.y + r3.h){
					    	selecionado = true;
					    	dx=r3.x-x;
						//dy=r3.y-y;
					    	if(r3.x > 405 && vencedor != 0) selecionado = false;    	
					 } 
				case SDL_MOUSEBUTTONUP:
					if(evt.button.state==SDL_RELEASED) selecionado=false;
					
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x,&y);
					if(x <= 460 && y <= 460 && selecionado){
						r3.x=x+dx;
						//r3.y=y+dy;
						//r3.x =x;
					}	
			}
		} 
		else {
		    espera = 100;
		    if(r2.x <=450) r2.x += 5;
		}
		/*PRIMEIRO LUGAR*/
		if(r1.x >= 370 && vencedor == 0) vencedor = 1;
		else if(r2.x >= 370 && vencedor == 0) vencedor = 2;
		else if(r3.x >= 370 && vencedor == 0) vencedor = 3;
		
		if(r1.x >=410 && r2.x >= 410 && r3.x >= 410){
		
			fimdejogo = true;
			continua = false;
			selecionado = false;
			SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
			SDL_RenderClear(ren);
			SDL_RenderPresent(ren);
			
		}   
		switch (evt.type ) {
		    case SDL_QUIT:
		    	continua = false;
		    	jogo = false;
		    	break;
		    case SDL_KEYDOWN:
		    	if(evt.key.keysym.sym == SDLK_F4){
		    		if(evt.key.keysym.mod == KMOD_LALT){
			    		continua = false;
			    		jogo = false;
			    		break;	
		    		}		
			}
		}
	    }    
	    while(fimdejogo){
			SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
			SDL_RenderClear(ren);
			boxRGBA(ren, 8, 98, 492,182, 0, 0, 0, 255);  
			/*VENCEDOR*/
			if(vencedor == 1){	
				boxRGBA(ren, 10, 100, 490, 180,0, 0, 255, 255);  
				stringRGBA(ren, 150, 140, "O vencedor foi o quadrado 1", 255, 255, 255, 255);
			}
			else if(vencedor == 2){ 
				boxRGBA(ren, 10, 100, 490, 180,0, 255, 0, 255);  
				stringRGBA(ren, 150, 140, "O vencedor foi o quadrado 2", 255, 255, 255, 255);
			}
			else if(vencedor == 3){ 
				boxRGBA(ren, 10, 100, 490, 180,255, 0, 0, 255);  
				stringRGBA(ren, 150, 140, "O vencedor foi o quadrado 3", 255, 255, 255, 255);
			}
			boxRGBA(ren, 18, 348, 242,402, 0, 0, 0, 255); 
			SDL_SetRenderDrawColor(ren,255,0,0,255);
			SDL_RenderFillRect(ren,&boxQuit);
			stringRGBA(ren, 116, 372, "Quit", 0, 0, 0, 255);
			
			boxRGBA(ren, 258, 348, 482,402, 0, 0, 0, 255); 
			SDL_SetRenderDrawColor(ren,255,255,255,255); 
			SDL_RenderFillRect(ren,&boxRestart);
			stringRGBA(ren, 344, 372, "Restart", 0, 0, 0, 255); 	 
			  
			SDL_RenderPresent(ren);
			SDL_Event evento;
			SDL_WaitEvent(&evento);
			switch (evento.type ) {
			    case SDL_QUIT:
			    	fimdejogo = false;
			    	jogo = false;			 
			    	break;
			    case SDL_KEYDOWN:
			    	if(evento.key.keysym.sym == SDLK_F4){
			    		if(evento.key.keysym.mod == KMOD_LALT){
				    		fimdejogo = false;
				    		jogo = false;
				    		break;	
			    		}		
				}
			    case SDL_MOUSEBUTTONDOWN:	
				SDL_GetMouseState(&x,&y);
				if(x > boxQuit.x && x < boxQuit.x + boxQuit.w && y > boxQuit.y && y < boxQuit.y + boxQuit.h){
					fimdejogo = false;
					jogo = false;
			    		break;
				}
				else if(x > boxRestart.x && x < boxRestart.x + boxRestart.w && y > boxRestart.y 
					&& y < boxRestart.y + boxRestart.h){
					fimdejogo = false;
					continua = true;
					r1.x =40; r1.y = 50; 
					r2.x = 40; r2.y= 225;
				   	r3.x =40;r3.y=400;
				   	vencedor = 0;
			    		break;	
			    	}
			    
			}        	
	      }
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);  
}
