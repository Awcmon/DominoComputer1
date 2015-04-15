#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "AwcColor.h"

class ATexture
{
	public:
	ATexture();
	ATexture(std::string path, Color colorkey = Color(255, 0, 255));
	ATexture(SDL_Surface *sourceSurface);
	~ATexture();

	bool load(std::string path, Color colorkey = Color(255, 0, 255));
	bool createFromSurface(SDL_Surface *sourceSurface);
	void free();
	SDL_Texture* getTexture();

	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setBlendMode(SDL_BlendMode blendmode);
	void setAlpha(Uint8 alpha);

	int getWidth();
	int getHeight();

	void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
	int width;
	int height;
	SDL_Texture *mTexture;
};
