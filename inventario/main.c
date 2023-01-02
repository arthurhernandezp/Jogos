#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
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

typedef struct dadosItem{
	SDL_Rect r;
	bool state;
	SDL_Texture* img;
}dadosItem;

typedef struct listaSeqItens{
	dadosItem matrizItens[6][2];
	int n;//Numeros de itens inseridos
}listaSeqItens;


void constroi(listaSeqItens* L,int x,int y){
	L->n = 0;
	int aux = x;
	for(int i = 0; i<6;i++){
		for(int j = 0;j<2;j++){
			L->matrizItens[i][j].img = NULL;
		 	L->matrizItens[i][j].state = false;
		 	SDL_Rect recAux = {x,y,64,64};
		 	L->matrizItens[i][j].r = recAux;
		 	x+=65;
		}
		x= aux;
    	y+=65;
    }
}

int buscaElemento(listaSeqItens L,int i, int j){
	return L.matrizItens[i][j].state;
}

int listaVazia(listaSeqItens L){
	return L.n == 0;
}

int listaCheia(listaSeqItens L){
	return L.n == 12;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                        1000, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "Icons_04.png");
	SDL_Texture* imgInv = IMG_LoadTexture(ren, "inv.png");
    assert(img != NULL);
	struct SDL_Texture* listaItens[7];
	listaItens[0] = IMG_LoadTexture(ren, "Icons_04.png");
	listaItens[1] = IMG_LoadTexture(ren, "Icons_05.png");
	listaItens[2] = IMG_LoadTexture(ren, "Icons_06.png");
	listaItens[3] = IMG_LoadTexture(ren, "Icons_07.png");
	listaItens[4] = IMG_LoadTexture(ren, "Icons_08.png");
	listaItens[5] = IMG_LoadTexture(ren, "Icons_09.png");
	listaItens[6] = IMG_LoadTexture(ren, "Icons_10.png");

    /* EXECUÇÃO */
    bool continua = true;
    SDL_Event evt;
    int isup = 1;
    int espera = 100;
    SDL_Rect inventario = {250,100,130,390};
    SDL_Rect inventario2 = {550,100,130,390};
    SDL_Rect cI;
    SDL_Rect r = { 251,101, 64,64 };
    SDL_Rect c;
 	int i = 0;
    int j = 0;
    int x, y,dx,dy;
    int xAntes, yAntes;
    //Criação do primeiro inventario
    listaSeqItens lista;
    constroi(&lista,250,100);
    //Criação do segundo inventario
    listaSeqItens lista2;
    int x1,y1,x2,y2;
    constroi(&lista2,550,100);
    SDL_Point mouse = {0,0};
    int randAux = 0;
    bool selecionado = false;
    bool encontrou = false;
    while (continua) {
        SDL_SetRenderDrawColor(ren, 255,0,255,0);
        SDL_RenderClear(ren);
        while(SDL_PollEvent(&evt)){       	
		switch (evt.type) {
		    case SDL_QUIT:
		    	continua = false;
		    	break;	
		    case SDL_KEYDOWN:
		    	switch (evt.key.keysym.sym){  
					case SDLK_RIGHT:			
						randAux = rand() % 7;	
						if(!listaCheia(lista)){
							if(	!buscaElemento(lista,i,j) ){
								printf("[%d,%d]INSERINGO\n",i,j);
								lista.matrizItens[i][j].img = listaItens[randAux];
								lista.matrizItens[i][j].state = true;
								(lista.n)++;
								j++;

								if(j >= 2 && i<5){
								j = 0;
								i++;
								}
							}
							else{
								printf("Existe um elemento na proxima posição!!!");
							}
						}
						else{
							printf("Lista Cheia!!!!\n");
						}
						break;
					case SDLK_LEFT:
						if(!listaVazia(lista)){
							j--;
							if(j < 0 && i>0){
								j = 1;
								i--;
							}
							lista.matrizItens[i][j].img = NULL;
							lista.matrizItens[i][j].state = false;
							(lista.n)--;
							printf("[%d,%d] DELETING\n",i,j);
						}
						else{
							printf("Lista Vazia!!!!\n");
						}
						break;
				}
			break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouse.x,&mouse.y);
				if(mouse.x < 500){
				   for(x1 = 0; x1<6;x1++){
						for(y1 = 0;y1<2;y1++){
							if(SDL_PointInRect(&mouse,&lista.matrizItens[x1][y1].r) && lista.matrizItens[x1][y1].state){
								encontrou = true;
								selecionado = true;
								dx=lista.matrizItens[x1][y1].r.x-mouse.x;
								dy=lista.matrizItens[x1][y1].r.y-mouse.y;
								xAntes = lista.matrizItens[x1][y1].r.x;
								yAntes = lista.matrizItens[x1][y1].r.y;
								break;
							}
							else{
							
								encontrou = false;
								selecionado = false;
							}
						}
						if(encontrou) break;
					}
				}
				else{
					 for(x1 = 0; x1<6;x1++){
						for(y1 = 0;y1<2;y1++){
							if(SDL_PointInRect(&mouse,&lista2.matrizItens[x1][y1].r) && lista2.matrizItens[x1][y1].state){
								encontrou = true;
								selecionado = true;
								dx=lista2.matrizItens[x1][y1].r.x-mouse.x;
								dy=lista2.matrizItens[x1][y1].r.y-mouse.y;
								xAntes = lista2.matrizItens[x1][y1].r.x;
								yAntes = lista2.matrizItens[x1][y1].r.y;
								break;
							}
							else{
							
								encontrou = false;
								selecionado = false;
							}
						}
						if(encontrou) break;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:	
				if(mouse.x >500){
					if(evt.button.button==SDL_BUTTON_LEFT){
						if(evt.button.state==SDL_RELEASED){
							if(SDL_PointInRect(&mouse,&lista.matrizItens[x1][y1].r) && selecionado) {						
								encontrou = false;
								selecionado = false;
								printf("Encontrou!!\n");
								lista.matrizItens[x1][y1].r.x = xAntes;
								lista.matrizItens[x1][y1].r.y = yAntes;
								 for(x2 = 0; x2<6;x2++){
									for(y2 = 0;y2<2;y2++){
										if(SDL_PointInRect(&mouse,&lista2.matrizItens[x2][y2].r) 
										&& !lista2.matrizItens[x2][y2].state){
											encontrou = true;
											lista2.matrizItens[x2][y2].state = true;
											lista2.matrizItens[x2][y2].img = lista.matrizItens[x1][y1].img;
											lista.matrizItens[x1][y1].img = NULL;
											(lista2.n)++;
											(lista.n)--; 
											i = x1;
											j = y1;
											break;
										}
									}
									if(encontrou) break;
								}
							}
							else{
								printf("NAAAAO Encontrou!!\n");
							}
						}
					}
				}
				else{
					if(evt.button.button==SDL_BUTTON_LEFT){
							if(evt.button.state==SDL_RELEASED){
								if(SDL_PointInRect(&mouse,&lista2.matrizItens[x1][y1].r) && selecionado) {						
									encontrou = false;
									selecionado = false;
									printf("Encontrou!!\n");
									lista2.matrizItens[x1][y1].r.x = xAntes;
									lista2.matrizItens[x1][y1].r.y = yAntes;
									 for(x2 = 0; x2<6;x2++){
										for(y2 = 0;y2<2;y2++){
											if(SDL_PointInRect(&mouse,&lista.matrizItens[x2][y2].r) 
											&& !lista.matrizItens[x2][y2].state){
												encontrou = true;
												lista.matrizItens[x2][y2].state = true;
												lista.matrizItens[x2][y2].img = lista2.matrizItens[x1][y1].img;
												lista2.matrizItens[x1][y1].img = NULL;
												(lista.n)++;
												(lista2.n)--; 
												i = x1;
												j = y1;
												break;
											}
										}
										if(encontrou) break;
									}
								}
								else{
									printf("NAAAAO Encontrou!!\n");
								}
							}
						}
				
				}
				break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouse.x,&mouse.y);
					if(selecionado){
						lista.matrizItens[x1][y1].r.x = mouse.x+dx;
						lista.matrizItens[x1][y1].r.y = mouse.y+dy;
					}
				break;
					
					
		}
		
	}
		cI = (SDL_Rect) {   0,0, 130,390 };
		c = (SDL_Rect) {   0,0, 64,64 };
		SDL_RenderCopy(ren, imgInv, &cI, &inventario2);
		SDL_RenderCopy(ren, imgInv, &cI, &inventario);
		for(x = 0; x<=5;x++){
			for(y = 0;y<=1;y++){
				SDL_RenderCopy(ren, lista.matrizItens[x][y].img, &c, &lista.matrizItens[x][y].r);
				SDL_RenderCopy(ren, lista2.matrizItens[x][y].img, &c, &lista2.matrizItens[x][y].r);
			}
		}
		//SDL_RenderCopy(ren, listaItens[randAux], &c, &r);
		SDL_RenderPresent(ren);

	}

    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
