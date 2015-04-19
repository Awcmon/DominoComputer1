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

void ASurface::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(gRenderer, x, y);
}

void ASurface::DrawLine(Vector2D p1, Vector2D p2)
{
	SDL_RenderDrawLine(gRenderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
}

void ASurface::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

void ASurface::DrawCircle(Vector2D pos, int rad) //Took this code from user Fourier on Facepunch, 04.19.15 Facepunch WAYWO thread.
{
	if (rad < 0)
		rad *= -1;

	int d = (5 - rad * 4) / 4;
	int x = 0;
	int y = rad;

	while (x <= y)
	{
		if (pos.x + x >= 0 && pos.x + x <= SCREEN_WIDTH - 1 && pos.y + y >= 0 && pos.y + y <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x + x, (int)pos.y + y);
		if ((int)pos.x + x >= 0 && (int)pos.x + x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x + x, (int)pos.y - y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y + y >= 0 && (int)pos.y + y <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x - x, (int)pos.y + y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x - x, (int)pos.y - y);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x + y, (int)pos.y + x);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x + y, (int)pos.y - x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x - y, (int)pos.y + x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawPoint((int)pos.x - y, (int)pos.y - x);

		if (d < 0) {
			d += 2 * x + 1;
		}
		else {
			d += 2 * (x - y) + 1;
			y--;
		}
		x++;
	}
}

void ASurface::DrawCircleFill(Vector2D pos, int rad)
{
	/*Draw Icecream Cone
	if (rad < 0)
		rad *= -1;

	int d = (5 - rad * 4) / 4;
	int x = 0;
	int y = rad;

	while (x <= y)
	{
		if (pos.x + x >= 0 && pos.x + x <= SCREEN_WIDTH - 1 && pos.y + y >= 0 && pos.y + y <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x + x, (int)pos.y + y);
		if ((int)pos.x + x >= 0 && (int)pos.x + x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x + x, (int)pos.y - y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y + y >= 0 && (int)pos.y + y <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x - x, (int)pos.y + y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x - x, (int)pos.y - y);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x + y, (int)pos.y + x);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x + y, (int)pos.y - x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x - y, (int)pos.y + x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawLine(0, 0, (int)pos.x - y, (int)pos.y - x);

		if (d < 0) {
			d += 2 * x + 1;
		}
		else {
			d += 2 * (x - y) + 1;
			y--;
		}
		x++;
	}
	*/

	if (rad < 0)
		rad *= -1;

	int d = (5 - rad * 4) / 4;
	int x = 0;
	int y = rad;

	while (x <= y)
	{
		if (pos.x + x >= 0 && pos.x + x <= SCREEN_WIDTH - 1 && pos.y + y >= 0 && pos.y + y <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x + x, (int)pos.y + y);
		if ((int)pos.x + x >= 0 && (int)pos.x + x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x + x, (int)pos.y - y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y + y >= 0 && (int)pos.y + y <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x - x, (int)pos.y + y);
		if ((int)pos.x - x >= 0 && (int)pos.x - x <= SCREEN_WIDTH - 1 && (int)pos.y - y >= 0 && (int)pos.y - y <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x - x, (int)pos.y - y);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x + y, (int)pos.y + x);
		if ((int)pos.x + y >= 0 && (int)pos.x + y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x + y, (int)pos.y - x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y + x >= 0 && (int)pos.y + x <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x - y, (int)pos.y + x);
		if ((int)pos.x - y >= 0 && (int)pos.x - y <= SCREEN_WIDTH - 1 && (int)pos.y - x >= 0 && (int)pos.y - x <= SCREEN_HEIGHT - 1)
			DrawLine((int)pos.x, (int)pos.y, (int)pos.x - y, (int)pos.y - x);

		if (d < 0) {
			d += 2 * x + 1;
		}
		else {
			d += 2 * (x - y) + 1;
			y--;
		}
		x++;
	}

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
	return Vector2D((float)w, (float)h);
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

	ATexture textTexture(TTF_RenderText_Solid(currentFont->font, text.c_str(), SDL_Color{ _color.r, _color.g, _color.b, _color.a }));
	if (_color.a < 255)
	{
		textTexture.setBlendMode(SDL_BLENDMODE_BLEND);
		textTexture.setAlpha(_color.a);
	}

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

void ASurface::SetBlendMode(SDL_BlendMode _blendMode)
{
	curBlendMode = _blendMode;
	SDL_SetRenderDrawBlendMode(gRenderer, curBlendMode);
}

void ASurface::SetAlpha(int _alpha)
{
	curAlpha = _alpha;
}

void ASurface::SetColor(Color _color)
{
	curColor = _color;
	SDL_SetRenderDrawColor(gRenderer, curColor.r, curColor.g, curColor.b, curColor.a);
}
