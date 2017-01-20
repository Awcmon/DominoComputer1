#include "ACamera.h"


ACamera::ACamera()
{
	pos = Vector2D(0, 0);

	offset = Vector2D(0, 0);
	ang = 0.0f;

	renderTarget = new ATexture();
	if (!renderTarget->createBlank(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_TEXTUREACCESS_TARGET))
	{
		printf("wtf");
	}
}

ACamera::~ACamera()
{
	renderTarget->free();
}

void ACamera::think()
{
	float vel = 2 / (float)sqrt(PPM);
	if (keyboard.scanDown(SDL_SCANCODE_A))
	{
		pos.x -= vel;
	}
	if (keyboard.scanDown(SDL_SCANCODE_D))
	{
		pos.x += vel;
	}
	if (keyboard.scanDown(SDL_SCANCODE_W))
	{
		pos.y += vel;
	}
	if (keyboard.scanDown(SDL_SCANCODE_S))
	{
		pos.y -= vel;
	}
}
