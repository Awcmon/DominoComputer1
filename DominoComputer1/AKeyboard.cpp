#include "AKeyboard.h"


AKeyboard::AKeyboard()
{
	inputTextChar = "";
	textInputActive = false;
}

AKeyboard::~AKeyboard()
{

}

AKeyboard::AKeyboard(AInputEvent *_inputEvent)
{
	inputEvent = _inputEvent;
	inputTextChar = "";
	textInputActive = false;
}

void AKeyboard::setInputEvent(AInputEvent *_inputEvent)
{
	inputEvent = _inputEvent;
}

/*SDLK*/
//Keyboard keyDown returns whether or not the key is physically down, while input keyDown does something similar to how a key is registered in text input.
bool AKeyboard::keyDown(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->keyDown(_key);
}

bool AKeyboard::keyInput(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->keyInput(_key);
}

bool AKeyboard::keyPressed(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->keyPressed(_key);
}

bool AKeyboard::keyReleased(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->keyReleased(_key);
}

/*SDL_SCANCODE*/
bool AKeyboard::scanDown(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->scanDown(_key);
}

bool AKeyboard::scanInput(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->scanInput(_key);
}

bool AKeyboard::scanPressed(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->scanPressed(_key);
}

bool AKeyboard::scanReleased(int _key)
{
	if (SDL_IsTextInputActive()) { return false; }
	return inputEvent->scanReleased(_key);
}

/*TEXT INPUT*/
void AKeyboard::startTextInput()
{
	textInputActive = true;
}

void AKeyboard::stopTextInput()
{
	textInputActive = false;
}

void AKeyboard::textInputThink()
{
	if (SDL_IsTextInputActive())
	{
		SDL_Event *events = inputEvent->getEvents();
		int numEvents = inputEvent->numEvents();

		for (int i = 0; i < numEvents; i++)
		{
			if (events[i].type == SDL_TEXTINPUT)
			{
				SDL_Event e = events[i];
				inputTextChar = e.text.text;
				std::cout << inputTextChar << "\n";
			}
		}
	}

	if ((!textInputActive) && SDL_IsTextInputActive())
	{
		printf("TEXT INPUT STOPPED\n");
		SDL_StopTextInput();
	}
	if (textInputActive && (!SDL_IsTextInputActive()))
	{
		printf("TEXT INPUT STARTED\n");
		SDL_StartTextInput();
	}
}

void AKeyboard::think()
{
	keystate = SDL_GetKeyboardState(NULL);

	textInputThink();
	
}
