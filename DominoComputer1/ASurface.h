#pragma once
//Surface is for drawing stuff on the screen in screen positions and pixels.
#include <SDL.h>
#include "AwcVector2D.h"

extern SDL_Renderer* gRenderer;

class ASurface
{
public:
	ASurface();
	~ASurface();
};

void surfaceDrawPoint(Vector2D pos);
void surfaceDrawLine(Vector2D p1, Vector2D p2);
void surfaceDrawRect(Vector2D pos, int w, int h);
void surfaceDrawFillRect(Vector2D pos, int w, int h);
void surfaceDrawQuad(Vector2D p1, Vector2D p2);
void surfaceDrawFillQuad(Vector2D p1, Vector2D p2);
