#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         640, 480, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    TTF_Init();
    SDL_Color padrao = { 255,255,255,255 };
    SDL_Color focus = { 237,139,0,255 };
    char fonte[7] = "ka1.ttf";
    TTF_Font *ourFont = TTF_OpenFont(fonte,100);
    
    struct SDL_Surface* listaSurfaceText[2];
    listaSurfaceText[0] = TTF_RenderText_Solid(ourFont, "Play",padrao);  
    listaSurfaceText[1] = TTF_RenderText_Solid(ourFont, "Quit",padrao); 
     
    struct SDL_Texture* listaTextureText[2];
    listaTextureText[0] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[0]);
    listaTextureText[1] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[1]);
    
    int i;
    /*for(i= 0; i < 2;i++){
    	SDL_FreeSurface(listaSurfaceText[i]);
    }*/
    
    SDL_Point mouse = {0,0};
    SDL_Rect recPlay = {270,120,100,30};
    SDL_Rect recQuit = {270,200,100,30};
    bool selecionado = false;
    bool gameIsRunning = true;
     /* EXECUÇÃO */
    while (gameIsRunning) {
    	SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					gameIsRunning = false;
				break;
				case SDL_MOUSEMOTION:
						SDL_GetMouseState(&mouse.x,&mouse.y);
						if(SDL_PointInRect(&mouse,&recPlay)){
							listaSurfaceText[0] = TTF_RenderText_Solid(ourFont, "Play",focus);  
					   		listaTextureText[0] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[0]);
					   	}
					   	else if(SDL_PointInRect(&mouse,&recQuit)){
					   		listaSurfaceText[1] = TTF_RenderText_Solid(ourFont, "Quit",focus);  
					   		listaTextureText[1] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[1]);
					   	}
					   	else{
							listaSurfaceText[0] = TTF_RenderText_Solid(ourFont, "Play",padrao);  
							listaTextureText[0] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[0]);
							listaSurfaceText[1] = TTF_RenderText_Solid(ourFont, "Quit",padrao);  
							listaTextureText[1] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[1]);
							selecionado = false;
					   	}
				break;
				case SDL_MOUSEBUTTONDOWN:	
					if(event.button.button==SDL_BUTTON_LEFT){
						if(SDL_PointInRect(&mouse,&recQuit)) selecionado = true;
					}
				case SDL_MOUSEBUTTONUP:	
					if(event.button.button==SDL_BUTTON_LEFT){
						if(event.button.state==SDL_RELEASED){
							if(SDL_PointInRect(&mouse,&recQuit) && selecionado) gameIsRunning = false;
						}
					}
				break;
			}
		}
		
		SDL_RenderCopy(ren,listaTextureText[0],NULL,&recPlay);
		SDL_RenderCopy(ren,listaTextureText[1],NULL,&recQuit);
		SDL_RenderPresent(ren);
	}	

	for(i = 0; i < 2;i++){
		SDL_FreeSurface(listaSurfaceText[i]);
		SDL_DestroyTexture(listaTextureText[i]);
	}
	mouse.x = mouse.y = 0;
	TTF_CloseFont(ourFont);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);  
}
