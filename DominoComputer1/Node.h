#pragma once

#include "AwcVector2D.h"
#include <vector>
#include "SDL.h"
#include "ARender.h"

class Node
{
public:
	Node();
	Node(Vector2D _pos);
	~Node();

	Vector2D setPos(Vector2D _pos);
	void remove();

	void think();
	void render();

	Vector2D pos;
	Vector2D vel;
	int val;

	std::vector<Node*> adjacent;
};

