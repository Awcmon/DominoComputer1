//DominoComputer1 03.27.15
#include <vector>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

int updateDelay = 250;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

std::vector<Node*> nodes;
std::vector<Node*> curActiveNodes;
std::vector<Node*> nextActiveNodes;
std::vector<Node*> nodesToRemove;

int simState;

AMouse mouse;

void SimReset()
{
	//Set all non-inputs to regular.
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (nodes[i]->val != 3)
		{
			nodes[i]->val = 1;
		}
		nodes[i]->adjacent.clear();
	}
	//Add all input nodes to active nodes.
	curActiveNodes.clear();
	nextActiveNodes.clear();
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (nodes[i]->val == 3)
		{
			PushNode(nodes[i], curActiveNodes);
		}
	}
	printf("CurSize %d\n", curActiveNodes.size());
}

/*---------------Main---------------*/
int main(int argc, char* args[])
{
	AWindow window;

	SDL_Event e;

	bool quit = false;

	//0 = pause, 1 = moving, -1 = stopped
	simState = -1;

	int lastUpdate = 0;

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

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (simState == -1)
					{
						//Start simulation
						SimReset();
						simState = 1;
						printf("Started.\n");
					}
					else if (simState == 0)
					{
						simState = 1;
						printf("Resumed.\n");
					}
					else
					{
						//Pause
						simState = 0;
						printf("Paused.\n");
					}
					break;
				case SDLK_r:
					if (simState != -1)
					{
						//Stop sim.
						SimReset();
						simState = -1;
						printf("Stopped.\n");
						break;
					}
					else
					{
						//Start simulation
						SimReset();
						simState = 1;
						printf("Started.\n");
					}
				}
			}
		}

		//Node logic if simulation is running and it is time to update.
		if (simState == 1 && ((lastUpdate + updateDelay) < (int)SDL_GetTicks()))
		{
			for (int i = 0; i < (int)curActiveNodes.size(); i++)
			{
				if (curActiveNodes[i]->val > 0)
				{
					if (curActiveNodes[i]->think() == 0)
					{
						break;
					}
				}
			}
			curActiveNodes.clear();
			curActiveNodes = nextActiveNodes;
			nextActiveNodes.clear();
			lastUpdate = SDL_GetTicks();
		}

		if (mouse.m1isDown || mouse.m2isDown)
		{
			bool isFilled = false;
			int fillID = 0;
			for (int i = 0; i < (int)nodes.size(); i++)
			{
				if (nodes[i]->pos == mpos)
				{
					isFilled = true;
					fillID = i;
				}
			}

			if (!isFilled && mouse.m1isDown)
			{
				Node* newNode = new Node(mpos);
				nodes.push_back(newNode);
				printf("Node added, Num nodes: %d\n", nodes.size());
			}
			else if (isFilled && mouse.m2isDown)
			{
				RemoveNode(nodes[fillID]);
				printf("Node removed, Num nodes: %d\n", nodes.size()-1);
			}
			
			if (isFilled && mouse.m1down)
			{
				if (nodes[fillID]->val == 1)
				{ 
					nodes[fillID]->val = 3;
				}
				else
				{
					nodes[fillID]->val = 1;
				}
			}
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		float vel = 2 / (float)sqrt(PPB);
		if (state[SDL_SCANCODE_A])
		{
			camPos.x -= vel;
		}
		if (state[SDL_SCANCODE_D])
		{
			camPos.x += vel;
		}
		if (state[SDL_SCANCODE_W])
		{
			camPos.y += vel;
		}
		if (state[SDL_SCANCODE_S])
		{
			camPos.y -= vel;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render nodes.
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			nodes[i]->render();
		}

		//Draw origin dot
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
		renderDrawPoint(Vector2D(0, 0));

		//Draw grid.
		if (PPB > 5)
		{
			SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 0xFF);
			for (int i = (int)round(camPos.x - 2 - ((SCREEN_WIDTH / 2) / PPB)); i <= (int)round(camPos.x + 1 + ((SCREEN_WIDTH / 2) / PPB)); i++)
			{
				Vector2D dpos(i + 0.5f, 0);
				SDL_RenderDrawLine(gRenderer, (int)Pos2Scr(dpos).x, 0, (int)Pos2Scr(dpos).x, SCREEN_HEIGHT);
			}
			for (int k = (int)round(camPos.y - 2 - ((SCREEN_HEIGHT / 2) / PPB)); k <= (int)round(camPos.y + 1 + ((SCREEN_HEIGHT / 2) / PPB)); k++)
			{
				Vector2D dpos(0, k + 0.5f);
				SDL_RenderDrawLine(gRenderer, 0, (int)Pos2Scr(dpos).y, SCREEN_WIDTH, (int)Pos2Scr(dpos).y);
			}
		}

		//Draw Mouse
		SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 0xFF);
		renderDrawRect(mpos, 1, 1);

		SDL_RenderPresent(gRenderer);

		for (int i = 0; i < (int)nodesToRemove.size(); i++)
		{
			nodes.erase(std::remove(nodes.begin(), nodes.end(), nodesToRemove[i]), nodes.end());
			delete nodesToRemove[i];
		}
		nodesToRemove.clear();

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
