#pragma once

#include "AwcVector2D.h"
#include <vector>
#include <map>
#include <SDL.h>
#include "ARender.h"
#include "AwcUtility.h"
#include <algorithm>

class Node
{
public:
	Node();
	Node(Vector2D _pos);
	~Node();

	Vector2D setPos(Vector2D _pos);
	void remove();

	void findAdjacent();

	int think();	//return 0 for error, 1 for okay.
	void render();

	Vector2D pos;
	Vector2D vel;
	//0 = off, 1 = on/ready, 2 = active, 3 = input
	int val;

	std::vector<Node*> adjacent;
	std::vector<Vector2D> adjVelVec;
};

void RemoveNode(Node* node);
void PushNode(Node* node, std::vector<Node*> &tvec);
void PopNode(Node* node, std::vector<Node*> &tvec);
