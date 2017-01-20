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
	surface.DrawRect(Pos2Scr(pos + Vector2D(-w/2,h/2)), (int)(w*PPM), (int)(h*PPM));
//	surfaceDrawQuad(Pos2Scr(pos - Vector2D(w/2, h/2)), Pos2Scr(pos + Vector2D(w/2, h/2)));
}

void renderDrawFillRect(Vector2D pos, float w, float h)
{
	surface.DrawFillRect(Pos2Scr(pos + Vector2D(-w / 2, h / 2)), (int)(w*PPM), (int)(h*PPM));
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
	surface.DrawTexturedRect(Pos2Scr(pos + Vector2D(-w / 2, h / 2)), (int)(w*PPM), (int)(h*PPM));
}

void renderDrawText(std::string text, Vector2D pos, double angle)
{
	/*Text test 2
	surface.SetFont("FFFBusiness32");
	std::string message = "Test string.";
	ATexture* text = surface.GetTextTexture(message);
	Vector2D textDim = surface.GetTextDimensions(message);
	surface.SetTexture(text);
	renderDrawTexturedRect(Vector2D(0, 0), (int)(textDim.x/32), (int)(textDim.y/32));
	*/
	
	/*
	ATexture textTexture(TTF_RenderText_Solid(surface.GetFont()->font, text.c_str(), surface.GetColor().toSDL()));
	if (surface.GetColor().a < 255)
	{
		textTexture.setBlendMode(SDL_BLENDMODE_BLEND);
		textTexture.setAlpha(surface.GetColor().a);
	}

	float w = (float)(textTexture.getWidth()/CONVERSION_PPM);
	float h = (float)(textTexture.getHeight()/CONVERSION_PPM);

	Vector2D rpos = Pos2Scr(pos + Vector2D(0, ((float)h)/2));

	SDL_Rect renderQuad = { (int)rpos.x, (int)rpos.y, (int)w*PPM, (int)h*PPM };

	//Render to screen
	SDL_RenderCopyEx(gRenderer, textTexture.getTexture(), NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
	*/

	/*Working*/
	ATexture* oldSurfaceTexture = surface.GetTexture();
	ATexture* textTexture = surface.GetTextTexture(text);
	Vector2D textDim = surface.GetTextDimensions(text);
	surface.SetTexture(textTexture);
	renderDrawTexturedRect(pos, (textDim.x / CONVERSION_PPM), (textDim.y / CONVERSION_PPM));
	surface.SetTexture(oldSurfaceTexture);
	oldSurfaceTexture = NULL;
	textTexture = NULL;
}