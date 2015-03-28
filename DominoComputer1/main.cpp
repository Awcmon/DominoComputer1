//SpaceDot2 03.15.15
#include "SDL.h"
#include "math.h"
#include "AWindow.h"
#include "AMouse.h"
#include "AwcVector2D.h"

#define FRAMES_PER_SECOND 120
#define MS_PER_FRAME 8

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
int PPB = 64;
Vector2D camPos;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

Vector2D Pos2Scr(Vector2D _pos)
{
	return Vector2D((SCREEN_WIDTH/2) + (_pos.x-camPos.x)*PPB, (SCREEN_HEIGHT/2) - (_pos.y-camPos.y)*PPB);
}

Vector2D Scr2Pos(Vector2D _pos)
{
	return Vector2D(((_pos.x - (SCREEN_WIDTH / 2)) / PPB) + camPos.x, ((-_pos.y + (SCREEN_HEIGHT / 2)) / PPB) + camPos.y);
}

/*---------------Main---------------*/
int main(int argc, char* args[])
{
	AWindow window;
	AMouse mouse;

	SDL_Event e;

	bool quit = false;

	while (!quit)
	{
		int start = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		mouse.think();

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_A])
		{
			camPos.x -= 0.1f;
		}
		if (state[SDL_SCANCODE_D])
		{
			camPos.x += 0.1f;
		}
		if (state[SDL_SCANCODE_W])
		{
			camPos.y += 0.1f;
		}
		if (state[SDL_SCANCODE_S])
		{
			camPos.y -= 0.1f;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		/*Draw dots
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
		for (int i = (int)round(camPos.x - ((SCREEN_WIDTH / 2) / PPB)); i <= (int)round(camPos.x + ((SCREEN_WIDTH / 2) / PPB)); i++)
		{
			for (int k = (int)round(camPos.y - ((SCREEN_HEIGHT / 2) / PPB)); k <= (int)round(camPos.y + ((SCREEN_HEIGHT / 2) / PPB)); k++)
			{
				Vector2D dpos((float)i, (float)k);
				SDL_RenderDrawPoint(gRenderer, (int)Pos2Scr(dpos).x, (int)Pos2Scr(dpos).y);
			}
		}*/
		//Draw grid
		SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 0xFF);
		for (int i = (int)round(camPos.x - ((SCREEN_WIDTH / 2) / PPB)); i <= (int)round(camPos.x + 0.5 + ((SCREEN_WIDTH / 2) / PPB)); i++)
		{
			Vector2D dpos(i+0.5f, 0);
			SDL_RenderDrawLine(gRenderer, (int)Pos2Scr(dpos).x, 0, (int)Pos2Scr(dpos).x, SCREEN_HEIGHT);
		}
		for (int k = (int)round(camPos.y - ((SCREEN_HEIGHT / 2) / PPB)); k <= (int)round(camPos.y + ((SCREEN_HEIGHT / 2) / PPB)); k++)
		{
			Vector2D dpos(0, k + 0.5f);
			SDL_RenderDrawLine(gRenderer, 0, (int)Pos2Scr(dpos).y, SCREEN_WIDTH, (int)Pos2Scr(dpos).y);
		}
		//Draw Mouse
		SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 0xFF);
		Vector2D dpos(round(Scr2Pos(mouse.pos).x), round(Scr2Pos(mouse.pos).y));
		SDL_Rect box{ Pos2Scr(dpos).x-PPB/2, Pos2Scr(dpos).y-PPB/2, PPB, PPB };
		SDL_RenderDrawRect(gRenderer, &box);

		SDL_RenderPresent(gRenderer);

		if (!quit)
		{
			int delay = start + MS_PER_FRAME - SDL_GetTicks();
			if (delay > 0)
			{
				SDL_Delay(delay);
			}
		}

	}

	window.free();

	return 0;
}
