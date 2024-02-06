#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "pnm.h"
#include "vec3.h"

#define WIN_WIDTH	680
#define WIN_HEIGHT	480
#define DEBUG_STATEMENTS true

typedef struct state_s {
	SDL_Window* window;
	SDL_Renderer* renderer;
} state_t;

int main(void){
	//if(SDL_Init(SDL_INIT_VIDEO) < 0){
	//	perror("[ERROR] Initializing SDL video");
	//	exit(EXIT_FAILURE);
	//}
	//if(SDL_Init(SDL_INIT_AUDIO) < 0){
	//	perror("[ERROR] Initializing SDL audio");
	//	exit(EXIT_FAILURE);
	//}

	//bool keep_win_open = true;

	//SDL_Event event;
	//SDL_Window* window;
	//SDL_Renderer* renderer;

	//window = SDL_CreateWindow(
	//	"SDL2 Window",
	//	SDL_WINDOWPOS_CENTERED,
	//	SDL_WINDOWPOS_CENTERED,
	//	WIN_WIDTH,
	//	WIN_HEIGHT,
	//	0
	//);

	//if(!window){
	//	perror("[ERROR] Creating window");
	//	exit(EXIT_FAILURE);
	//}

	//renderer = SDL_CreateRenderer(window, -1, 0);
	//if(!renderer){
	//	perror("[ERROR] Creating renderer from the window");
	//	exit(EXIT_FAILURE);
	//}

	//while(SDL_PollEvent(&event) > 0 || keep_win_open){
	//	if(event.type == SDL_QUIT){
	//		keep_win_open = false;
	//	}
	//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//	SDL_RenderClear(renderer);
	//	SDL_RenderPresent(renderer);
	//}
	////cleanup	

    //SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
    //SDL_Quit();
	pnm_t image = pnm_init("image.pnm");
	
	if(DEBUG_STATEMENTS){
		printf("Type: %d\nWidth: %d\nHeight: %d\nMax Value: %d\n",image.type, image.width, image.height, image.max_val);
	}
	
	exit(EXIT_SUCCESS);
}
