//DominoComputer1 03.27.15
#include "SDL.h"
#include "math.h"
#include "AWindow.h"
#include "AMouse.h"
#include "AwcVector2D.h"
#include "AwcUtility.h"
#include "ARender.h"
#include "ASurface.h"
#include "Node.h"

#define FRAMES_PER_SECOND 120
#define MS_PER_FRAME 8

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
int PPB = 64;
Vector2D camPos;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

AMouse mouse;
/*---------------Main---------------*/
int main(int argc, char* args[])
{
	AWindow window;

	SDL_Event e;

	bool quit = false;

	std::vector<Node*> nodes;

	while (!quit)
	{
		int start = SDL_GetTicks();

		mouse.think();
		//Grid pos the mouse is on.
		Vector2D mpos(round(Scr2Pos(mouse.pos).x), round(Scr2Pos(mouse.pos).y));

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y < 0)
				{
					PPB -= Clamp((int)round(PPB/8),1,1000);
				}
				else if (e.wheel.y > 0)
				{
					PPB += Clamp((int)round(PPB/8),1,1000);
				}
				PPB = Clamp(PPB, 1, 1000);
				printf("PPB: %d\n", PPB);
			}
		}

		if (mouse.m1isDown)
		{
			bool isFilled = false;
			for (int i = 0; i < nodes.size(); i++)
			{
				if (nodes[i]->pos == mpos)
				{
					isFilled = true;
				}
			}
			if (!isFilled)
			{
				Node* newNode = new Node(mpos);
				nodes.push_back(newNode);
			}
		}

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

		//Render nodes.
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i]->render();
		}

		//Draw origin dot
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
		renderDrawPoint(Vector2D(0, 0));

		//Draw grid.
		SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 0xFF);
		for (int i = (int)round(camPos.x - 2 - ((SCREEN_WIDTH / 2) / PPB)); i <= (int)round(camPos.x + 1 + ((SCREEN_WIDTH / 2) / PPB)); i++)
		{
			Vector2D dpos(i+0.5f, 0);
			SDL_RenderDrawLine(gRenderer, (int)Pos2Scr(dpos).x, 0, (int)Pos2Scr(dpos).x, SCREEN_HEIGHT);
		}
		for (int k = (int)round(camPos.y - 2 - ((SCREEN_HEIGHT / 2) / PPB)); k <= (int)round(camPos.y + 1 + ((SCREEN_HEIGHT / 2) / PPB)); k++)
		{
			Vector2D dpos(0, k + 0.5f);
			SDL_RenderDrawLine(gRenderer, 0, (int)Pos2Scr(dpos).y, SCREEN_WIDTH, (int)Pos2Scr(dpos).y);
		}

		//Draw Mouse
		SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 0xFF);
		renderDrawRect(mpos, 1, 1);

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
