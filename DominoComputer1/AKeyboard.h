#pragma once
#include <SDL.h>
#include <string>
#include "AInputEvent.h"

class AKeyboard
{
public:
	AKeyboard();
	AKeyboard(AInputEvent *_inputEvent);
	~AKeyboard();

	void setInputEvent(AInputEvent *_inputEvent);

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

	void startTextInput();
	void stopTextInput();

	void textInputThink();
	void think();

private:
	AInputEvent *inputEvent;
	const Uint8 *keystate;

	bool textInputActive;

	std::string inputTextChar;
};

