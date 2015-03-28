#include "ASurface.h"


ASurface::ASurface()
{
}

ASurface::~ASurface()
{
}

void surfaceDrawPoint(Vector2D pos)
{
	SDL_RenderDrawPoint(gRenderer, (int)pos.x, (int)pos.y);
}

void surfaceDrawLine(Vector2D p1, Vector2D p2)
{
	SDL_RenderDrawLine(gRenderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
}

void surfaceDrawRect(Vector2D pos, int w, int h)
{
	SDL_Rect rect{ (int)pos.x, (int)pos.y, w, h };
	SDL_RenderDrawRect(gRenderer, &rect);
}

void surfaceDrawFillRect(Vector2D pos, int w, int h)
{
	SDL_Rect rect{ (int)pos.x, (int)pos.y, w, h };
	SDL_RenderFillRect(gRenderer, &rect);
}

void surfaceDrawQuad(Vector2D p1, Vector2D p2)
{
	Vector2D pos;
	
	float w = abs(p1.x - p2.x);
	float h = abs(p1.y - p2.y);

	if (p1.x <= p2.x)
	{
		pos.x = p1.x;
	}
	else
	{
		pos.x = p2.x;
	}

	if (p1.y <= p2.y)
	{
		pos.y = p1.y;
	}
	else
	{
		pos.y = p2.y;
	}

	SDL_Rect rect{ (int)pos.x, (int)pos.y, (int)w, (int)h };
	SDL_RenderDrawRect(gRenderer, &rect);
}

void surfaceDrawFillQuad(Vector2D p1, Vector2D p2)
{
	Vector2D pos;

	float w = abs(p1.x - p2.x);
	float h = abs(p1.y - p2.y);

	if (p1.x <= p2.x)
	{
		pos.x = p1.x;
	}
	else
	{
		pos.x = p2.x;
	}

	if (p1.y <= p2.y)
	{
		pos.y = p1.y;
	}
	else
	{
		pos.y = p2.y;
	}

	SDL_Rect rect{ (int)pos.x, (int)pos.y, (int)w, (int)h };
	SDL_RenderFillRect(gRenderer, &rect);
}
