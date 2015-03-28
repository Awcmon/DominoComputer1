#include "ARender.h"


ARender::ARender()
{
}

ARender::~ARender()
{
}

Vector2D Pos2Scr(Vector2D _pos)
{
	return Vector2D((SCREEN_WIDTH / 2) + (_pos.x - camPos.x)*PPB, (SCREEN_HEIGHT / 2) - (_pos.y - camPos.y)*PPB);
}

Vector2D Scr2Pos(Vector2D _pos)
{
	return Vector2D(((_pos.x - (SCREEN_WIDTH / 2)) / PPB) + camPos.x, ((-_pos.y + (SCREEN_HEIGHT / 2)) / PPB) + camPos.y);
}

void renderDrawPoint(Vector2D pos)
{
	surfaceDrawPoint(Pos2Scr(pos));
}

void renderDrawLine(Vector2D p1, Vector2D p2)
{
	surfaceDrawLine(Pos2Scr(p1), Pos2Scr(p2));
}

void renderDrawRect(Vector2D pos, float w, float h)
{
	surfaceDrawRect(Pos2Scr(pos + Vector2D(-w/2,h/2)), (int)w*PPB, (int)h*PPB);
//	surfaceDrawQuad(Pos2Scr(pos - Vector2D(w/2, h/2)), Pos2Scr(pos + Vector2D(w/2, h/2)));
}

void renderDrawFillRect(Vector2D pos, float w, float h)
{
	surfaceDrawFillRect(Pos2Scr(pos + Vector2D(-w / 2, h / 2)), (int)w*PPB, (int)h*PPB);
}

void renderDrawQuad(Vector2D p1, Vector2D p2)
{
	surfaceDrawQuad(Scr2Pos(p1), Scr2Pos(p2));
}

void renderDrawFillQuad(Vector2D p1, Vector2D p2)
{
	surfaceDrawFillQuad(Scr2Pos(p1), Scr2Pos(p2));
}
