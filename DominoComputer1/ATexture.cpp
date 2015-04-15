#include "ATexture.h"

extern SDL_Renderer* gRenderer;

ATexture::ATexture()
{
	mTexture = NULL;
	width = 0;
	height = 0;
}

ATexture::ATexture(std::string path, Color colorkey)
{
	mTexture = NULL;
	width = 0;
	height = 0;

	load(path, colorkey);
}

ATexture::ATexture(SDL_Surface *sourceSurface)
{
	mTexture = NULL;
	width = 0;
	height = 0;

	createFromSurface(sourceSurface);
}

ATexture::~ATexture()
{
	free();
}

bool ATexture::load(std::string path, Color colorkey)
{
	free();

	//Final texture
	SDL_Texture* newTexture = NULL;
	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		width = loadedSurface->w;
		height = loadedSurface->h;

		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, (Uint8)colorkey.r, (Uint8)colorkey.g, (Uint8)colorkey.b));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

//Creates texture from existing surface and frees the surface
bool ATexture::createFromSurface(SDL_Surface *sourceSurface)
{
	free();

	//Final texture
	SDL_Texture* newTexture = NULL;

	width = sourceSurface->w;
	height = sourceSurface->h;

	newTexture = SDL_CreateTextureFromSurface(gRenderer, sourceSurface);

	SDL_FreeSurface(sourceSurface);

	mTexture = newTexture;
	return mTexture != NULL;
}

void ATexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
}

SDL_Texture* ATexture::getTexture()
{
	return mTexture;
}

int ATexture::getWidth()
{
	return width;
}

int ATexture::getHeight()
{
	return height;
}

void ATexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void ATexture::setBlendMode(SDL_BlendMode blendmode)
{
	SDL_SetTextureBlendMode(mTexture, blendmode);
}

void ATexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void ATexture::render(int x, int y, double angle, SDL_Point* center, SDL_Rect* clip, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
