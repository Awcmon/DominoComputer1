#pragma once

#include <SDL.h>
#include "AwcVector2D.h"

class AMouse
{
public:
	AMouse();
	~AMouse();

	void think();

	Vector2D pos;
	Vector2D downPos;
	Vector2D upPos;

	//M1 Vars
	bool m1down;
	bool m1isDown;
	bool m1up;
	//M2 Vars
	bool m2down;
	bool m2isDown;
	bool m2up;

private:
	//M1 control vars
	bool m1downCont;
	bool m1upCont;
	//M2 control vars
	bool m2downCont;
	bool m2upCont;
};

