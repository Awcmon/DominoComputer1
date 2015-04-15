#include "ARender.h"


ARender::ARender()
{
}

ARender::~ARender()
{
}

Vector2D Pos2Scr(Vector2D _pos)
{
	return Vector2D((SCREEN_WIDTH / 2) + (_pos.x - camPos.x)*PPM, (SCREEN_HEIGHT / 2) - (_pos.y - camPos.y)*PPM);
}

Vector2D Scr2Pos(Vector2D _pos)
{
	return Vector2D(((_pos.x - (SCREEN_WIDTH / 2)) / PPM) + camPos.x, ((-_pos.y + (SCREEN_HEIGHT / 2)) / PPM) + camPos.y);
}

void renderDrawPoint(Vector2D pos)
{
	surface.DrawPoint(Pos2Scr(pos));
}

void renderDrawLine(Vector2D p1, Vector2D p2)
{
	surface.DrawLine(Pos2Scr(p1), Pos2Scr(p2));
}

void renderDrawRect(Vector2D pos, float w, float h)
{
	surface.DrawRect(Pos2Scr(pos + Vector2D(-w/2,h/2)), (int)w*PPM, (int)h*PPM);
//	surfaceDrawQuad(Pos2Scr(pos - Vector2D(w/2, h/2)), Pos2Scr(pos + Vector2D(w/2, h/2)));
}

void renderDrawFillRect(Vector2D pos, float w, float h)
{
	surface.DrawFillRect(Pos2Scr(pos + Vector2D(-w / 2, h / 2)), (int)w*PPM, (int)h*PPM);
}

void renderDrawQuad(Vector2D p1, Vector2D p2)
{
	surface.DrawQuad(Scr2Pos(p1), Scr2Pos(p2));
}

void renderDrawFillQuad(Vector2D p1, Vector2D p2)
{
	surface.DrawFillQuad(Scr2Pos(p1), Scr2Pos(p2));
}

void renderDrawTexturedRect(Vector2D pos, float w, float h)
{
	surface.DrawTexturedRect(Pos2Scr(pos + Vector2D(-w / 2, h / 2)), (int)w*PPM, (int)h*PPM);
}
