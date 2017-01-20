#pragma once

#include <SDL.h>
#include "Globals.h"
#include "AwcVector2D.h"
#include "ATexture.h"

class ACamera
{
public:
	ACamera();
	~ACamera();

	void think();


	ATexture *renderTarget;

	Vector2D pos;

	Vector2D offset;
	float ang;
};
