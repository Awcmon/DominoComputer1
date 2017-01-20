#pragma once

#define MAX_EVENTS 32
/*
#define MAX_EVENTS_KEYBOARD 32
#define MAX_EVENTS_MOUSE 8
#define MAX_EVENTS_MOUSEWHEEL 8
*/

#include <SDL.h>
#include <iostream>

class AInputEvent
{
public:
	AInputEvent();
	~AInputEvent();

	//Event retrieval and stuff.
	bool isEvent(int ev);
	SDL_Event getEvent(int index);
	SDL_Event* getEvents();
	int* getEventTypes();
	int numEvents();

	//SDLK
	bool keyDown(int _key);
	bool keyInput(int _key);
	bool keyPressed(int _key);
	bool keyReleased(int _key);

	//SDL_SCANCODE
	bool scanDown(int _key);
	bool scanInput(int _key);
	bool scanPressed(int _key);
	bool scanReleased(int _key);

	//Mouse
	bool mousePressed(int _button);
	bool mouseReleased(int _button);
	int mouseWheelY();

	//Think
	void think();

private:
	SDL_Event e;
	SDL_Event defaultEvent;

	int eventTypes[MAX_EVENTS];
	SDL_Event events[MAX_EVENTS];

	int eventsStored;

	const Uint8 *keystate;
};

