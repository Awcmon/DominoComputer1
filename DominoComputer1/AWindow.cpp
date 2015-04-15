#include "AWindow.h"

AWindow::AWindow()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	gWindow = SDL_CreateWindow("DominoComputer1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
}

AWindow::~AWindow()
{
	free();
}

void AWindow::free()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
