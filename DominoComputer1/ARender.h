#pragma once
//Render is for drawing stuff in the 'game world' in 'game units'.
#include "AwcVector2D.h"
#include "ASurface.h"
#include "Globals.h"

class ARender
{
public:
	ARender();
	~ARender();
};

Vector2D Pos2Scr(Vector2D _pos);
Vector2D Scr2Pos(Vector2D _pos);

void renderDrawPoint(Vector2D pos);
void renderDrawLine(Vector2D p1, Vector2D p2);
void renderDrawRect(Vector2D pos, float w, float h);
void renderDrawFillRect(Vector2D pos, float w, float h);
void renderDrawQuad(Vector2D p1, Vector2D p2);
void renderDrawFillQuad(Vector2D p1, Vector2D p2);
void renderDrawTexturedRect(Vector2D pos, float w, float h);
