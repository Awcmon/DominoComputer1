#pragma once
//Surface is for drawing stuff on the screen in screen positions and pixels.
#include <map>
#include <string>
#include <SDL.h>
#include "AwcVector2D.h"
#include "ATexture.h"
#include "AFont.h"
#include "AwcColor.h"

extern SDL_Renderer* gRenderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

class ASurface
{
public:
	ASurface();
	~ASurface();

	//Geometric primitives
	void DrawPoint(Vector2D pos);
	void DrawPoint(int x, int y);
	void DrawLine(Vector2D p1, Vector2D p2);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawCircle(Vector2D pos, int rad = 200);
	void DrawCircleFill(Vector2D pos, int rad = 200);
	void DrawRect(Vector2D pos, int w, int h);
	void DrawFillRect(Vector2D pos, int w, int h);
	void DrawQuad(Vector2D p1, Vector2D p2);
	void DrawFillQuad(Vector2D p1, Vector2D p2);

	//Textures
	void DrawTexturedRect(Vector2D pos = Vector2D(0,0), int _w = NULL, int _h = NULL, double angle = 0.0);
	void DrawTexturedQuad(Vector2D p1, Vector2D p2);

	//Fonts and text
	void CreateFont(std::string name, std::string path, int size);
	void SetFont(std::string fontname);
	ATexture* GetTextTexture(std::string text, Color _color = Color(0,0,0));
	int GetTextWidth(std::string text);
	int GetTextHeight(std::string text);
	Vector2D GetTextDimensions(std::string text);
	void DrawText(std::string text, Vector2D pos, double angle = 0.0, Color _color = Color(0, 0, 0));

	//Setting stuff
	void SetTexture(ATexture* _texture);
	void SetBlendMode(SDL_BlendMode _blendMode);
	void SetAlpha(int _alpha);
	void SetColor(Color _color);

private:
	ATexture* texture;

	Color curColor;
	SDL_BlendMode curBlendMode;
	int curAlpha;

	//Font stuff
	std::map<std::string, AFont*> fontMap;
	AFont* currentFont;
};
