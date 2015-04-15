#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class AFont
{
public:
	TTF_Font* font = NULL;

	AFont(std::string path, int size);
	~AFont();

};
