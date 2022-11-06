#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct defRect{
	int x;
	int y;
	int cores[3];
}defRect;

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         500, 500, 0
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    srand(time(NULL));
    SDL_Event evt;
    bool continua = true; 
    SDL_Rect r = { 40,20, 50,50 };
    int i = 0;     
    defRect rects[10];
	  while(continua){
	  /* EXECUÇÃO */
	      SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_WaitEvent(&evt);
        for (int k = 0; k < 10; k++)
          {
            if(rects[k].x != 0 && rects[k].y != 0){
              boxRGBA(ren,rects[k].x,rects[k].y,rects[k].x + 50,rects[k].y +50,rects[k].cores[0],rects[k].cores[1],rects[k].cores[2],255);
            }	
          }    
          SDL_RenderPresent(ren);
        
        switch(evt.type){ 
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (r.y >0){
                              r.y -= 5;
                        }
                  break;
                    case SDLK_DOWN:
                        if(r.y < 450){            
                             r.y += 5;
                        }
                        break;
                    case SDLK_LEFT:
                        if(r.x > 0){
                             r.x -= 5;
                        }
                        break;
                    case SDLK_RIGHT:
                        if(r.x < 450){
                             r.x += 5;
                        }
                        break;
                }
	      }
       if(evt.type == SDL_MOUSEBUTTONDOWN){
        if(i < 10){
          int x, y;	    		
          SDL_GetMouseState(&x,&y);
          rects[i].x = x;
          rects[i].y = y;
          for(int j = 0; j < 3; j++){
            rects[i].cores[j] = rand() % 255;
          }
          i++;
        }
      }    	      
    /* FINALIZACAO */
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
