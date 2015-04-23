#pragma once

#include <SDL.h>
#include "AInputEvent.h"
#include "AwcVector2D.h"

class AMouse
{
public:
	AMouse();
	AMouse(AInputEvent* _inputEvent);
	~AMouse();

	void setInputEvent(AInputEvent* _inputEvent);

	void think();

	Vector2D pos;
	Vector2D downPos;
	Vector2D upPos;

	//
	bool m1isDown;
	bool m1pressed;
	bool m1released;
	bool m2isDown;
	bool m2pressed;
	bool m2released;
	//Mouse wheel vars
	int mWheelY;

private:
	AInputEvent* inputEvent;
};

