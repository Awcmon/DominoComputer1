#include "Node.h"

Node::Node()
{
	pos = Vector2D(0, 0);
	vel = Vector2D(0, 0);
	printf("Node placed!\n");
}

Node::Node(Vector2D _pos)
{
	pos = _pos;
	vel = Vector2D(0, 0);
	printf("Node placed!\n");
}

Node::~Node()
{

}

Vector2D Node::setPos(Vector2D _pos)
{
	pos = _pos;
	return pos;
}

void Node::remove()
{

}

void Node::think()
{

}

void Node::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	renderDrawFillRect(pos, 1, 1);
}
