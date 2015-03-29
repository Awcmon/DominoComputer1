#pragma once

//More of a window manager.

#include <SDL.h>
#include "SDL_image.h"
#include "Globals.h"

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

class AWindow
{
public:
	AWindow();
	~AWindow();
	void free();
};

