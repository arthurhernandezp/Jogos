#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
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
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(ren);
    /*CABEÇA*/
    boxRGBA(ren, 100, 20, 220, 40,255, 0, 0, 255);
    boxRGBA(ren, 80, 40, 280, 60,255, 0, 0, 255);
    boxRGBA(ren, 80, 60, 140, 80,133, 59, 36, 255);
    boxRGBA(ren, 140, 60, 200, 160,255, 163, 92, 255);
    boxRGBA(ren, 200, 60, 220, 100,0, 0, 0, 255);
    boxRGBA(ren, 200, 100, 220, 120,255, 163, 92, 255);   
    boxRGBA(ren, 220, 100, 240, 120,0, 0, 0, 255);    
    boxRGBA(ren, 200, 120, 280, 140,0, 0, 0, 255);    
    boxRGBA(ren, 240, 80, 280, 120,255, 163, 92, 255); 
    boxRGBA(ren, 280, 100, 300, 120,255, 163, 92, 255);     
    boxRGBA(ren, 200, 140, 260, 160,255, 163, 92, 255);      
    boxRGBA(ren, 220, 60, 240, 100,255, 163, 92, 255);
    boxRGBA(ren, 60, 80, 80, 140,133, 59, 36, 255);
    boxRGBA(ren, 80, 80, 100, 120,255, 163, 92, 255);
    boxRGBA(ren, 100, 80, 120, 120,133, 59, 36, 255);
    boxRGBA(ren, 120, 80, 140, 100,255, 163, 92, 255);
    boxRGBA(ren, 120, 100, 140, 120,133, 59, 36, 255);
    boxRGBA(ren, 100, 120, 140, 160,255, 163, 92, 255);    
    boxRGBA(ren, 80, 120, 100, 140,133, 59, 36, 255);    
    
    /*CORPO*/
    boxRGBA(ren, 80, 160, 120, 220,255, 0, 0, 255);  
    boxRGBA(ren, 60, 180, 80, 220,255, 0, 0, 255);   
    boxRGBA(ren, 40, 200, 60, 220,255, 0, 0, 255);  
    boxRGBA(ren, 40, 220, 80, 280,255, 163, 92, 255);  
    boxRGBA(ren, 80, 240, 100, 260,255, 163, 92, 255);     
    boxRGBA(ren, 80, 220, 100, 240,255, 0, 0, 255); 
    boxRGBA(ren, 80, 260, 100, 300,0, 0, 255, 255); 
    boxRGBA(ren, 100, 220, 120, 300,0, 0, 255, 255);    
    boxRGBA(ren, 220, 180, 240, 240,255, 0, 0, 255); 
    boxRGBA(ren, 240, 180, 260, 220,255, 0, 0, 255); 
    boxRGBA(ren, 260, 200, 280, 220,255, 0, 0, 255); 
    boxRGBA(ren, 220, 240, 240, 260,255, 163, 92, 255); 
    boxRGBA(ren, 220, 260, 240, 300,0, 0, 255, 255); 
    boxRGBA(ren, 240, 220, 280, 280,255, 163, 92, 255);   
    boxRGBA(ren, 120, 160, 140, 220,0, 0, 255, 255);   
    boxRGBA(ren, 140, 160, 180, 200,255, 0, 0, 255);    
    boxRGBA(ren, 180, 160, 220, 180,255, 0, 0, 255);    
    boxRGBA(ren, 200, 160, 220, 220,255, 0, 0, 255); 
    boxRGBA(ren, 120, 220, 140, 240,255, 247, 0, 255);
    boxRGBA(ren, 120, 240, 140, 300,0, 0, 255, 255);   
    boxRGBA(ren, 180, 220, 200, 240,255, 247, 0, 255);  
    boxRGBA(ren, 200, 220, 220, 300,0, 0, 255, 255);   
    boxRGBA(ren, 180, 240, 200, 300,0, 0, 255, 255);
    boxRGBA(ren, 180, 180, 200, 220,0, 0, 255, 255);   
    boxRGBA(ren, 140, 200, 180, 280,0, 0, 255, 255); 
    /*BOTAS*/
    boxRGBA(ren, 60, 300, 120, 320,133, 59, 36, 255);     
    boxRGBA(ren, 40, 320, 120, 340,133, 59, 36, 255);    
    boxRGBA(ren, 200, 300, 280, 320,133, 59, 36, 255);     
    boxRGBA(ren, 200, 320, 300, 340,133, 59, 36, 255);   
    
    boxRGBA(ren, 10, 350, 380, 380,0, 0, 0, 255);   
    stringRGBA(ren, 10, 360, "Sera se esse mario recebe 0,7+ nesse trabalho?", 255, 255, 255, 255);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
	
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
