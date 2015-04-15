#include "ASurface.h"


ASurface::ASurface()
{
}

ASurface::~ASurface()
{
	fontMap.clear();
	texture = NULL;
}

//Geometric Primitives
void ASurface::DrawPoint(Vector2D pos)
{
	SDL_RenderDrawPoint(gRenderer, (int)pos.x, (int)pos.y);
}

void ASurface::DrawLine(Vector2D p1, Vector2D p2)
{
	SDL_RenderDrawLine(gRenderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
}

void ASurface::DrawRect(Vector2D pos, int w, int h)
{
	SDL_Rect rect{ (int)pos.x, (int)pos.y, w, h };
	SDL_RenderDrawRect(gRenderer, &rect);
}

void ASurface::DrawFillRect(Vector2D pos, int w, int h)
{
	SDL_Rect rect{ (int)pos.x, (int)pos.y, w, h };
	SDL_RenderFillRect(gRenderer, &rect);
}

void ASurface::DrawQuad(Vector2D p1, Vector2D p2)
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

void ASurface::DrawFillQuad(Vector2D p1, Vector2D p2)
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

//Texture stuff
void ASurface::DrawTexturedRect(Vector2D pos, int _w, int _h, double angle)
{
	int w = _w;
	int h = _h;

	if ((w == NULL) || (h == NULL))
	{
		w = texture->getWidth();
		h = texture->getHeight();
	}

	SDL_Rect renderQuad = { (int)pos.x, (int)pos.y, w, h };

	//Render to screen
	SDL_RenderCopyEx(gRenderer, texture->getTexture(), NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}

void ASurface::DrawTexturedQuad(Vector2D p1, Vector2D p2)
{

}

//Fonts and text
void ASurface::CreateFont(std::string name, std::string path, int size)
{
	//fontMap[name] = AFont(path, size
//	if (fontMap[name] == NULL)
//	{
		fontMap.insert(std::pair<std::string, AFont*>(name, new AFont(path, size)));
//	}
}

void ASurface::SetFont(std::string fontname)
{
	currentFont = fontMap[fontname];
}

ATexture* ASurface::GetTextTexture(std::string text, Color _color)
{
	return new ATexture(TTF_RenderText_Solid(currentFont->font, text.c_str(), SDL_Color{ 0, 0, 0 }));
}

int ASurface::GetTextWidth(std::string text)
{
	int w;
	int h;
	TTF_SizeText(currentFont->font, text.c_str(), &w, &h);
	return w;
}

int ASurface::GetTextHeight(std::string text)
{
	int w;
	int h;
	TTF_SizeText(currentFont->font, text.c_str(), &w, &h);
	return h;
}

Vector2D ASurface::GetTextDimensions(std::string text)
{
	int w;
	int h;
	TTF_SizeText(currentFont->font, text.c_str(), &w, &h);
	return Vector2D(w, h);
}

void ASurface::DrawText(std::string text, Vector2D pos, double angle, Color _color)
{
	/*Text test 2
	surface.SetFont("FFFBusiness32");
	std::string message = "Test string.";
	ATexture* text = surface.GetTextTexture(message);
	Vector2D textDim = surface.GetTextDimensions(message);
	surface.SetTexture(text);
	renderDrawTexturedRect(Vector2D(0, 0), (int)(textDim.x/32), (int)(textDim.y/32));
	*/

	ATexture textTexture(TTF_RenderText_Solid(currentFont->font, text.c_str(), SDL_Color{ 0, 0, 0 }));

	int w = textTexture.getWidth();
	int h = textTexture.getHeight();

	SDL_Rect renderQuad = { (int)pos.x, (int)pos.y, w, h };

	//Render to screen
	SDL_RenderCopyEx(gRenderer, textTexture.getTexture(), NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}

//Setting stuff
void ASurface::SetTexture(ATexture* _texture)
{
	/*
	texture->free();
	texture = new ATexture;
	texture->load(path);
	*/
	texture = _texture;
}
