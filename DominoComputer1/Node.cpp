#include "Node.h"

extern std::vector<Node*> nodes;
extern std::vector<Node*> curActiveNodes;
extern std::vector<Node*> nextActiveNodes;
extern std::vector<Node*> nodesToRemove;
extern int simState;

void RemoveNode(Node* node)
{
	bool dupe = false;
	for (int i = 0; i < (int)nodesToRemove.size(); i++)
	{
		if (nodesToRemove[i] == node)
		{
			printf("\nDuplicate found!\n");
			dupe = true;
		}
	}
	if (!dupe)
	{
		nodesToRemove.push_back(node);
	}
}

//Pushes node to vector and checks for duplicates.
void PushNode(Node* _node, std::vector<Node*> &tvec)
{
	bool dupe = false;
	for (int i = 0; i < (int)tvec.size(); i++)
	{
		if (tvec[i] == _node)
		{
			printf("Duplicate found.\n");
			dupe = true;
		}
	}
	if (!dupe)
	{
		tvec.push_back(_node);
	}
}

void PopNode(Node* _node, std::vector<Node*> &tvec)
{
	tvec.erase(std::remove(tvec.begin(), tvec.end(), _node), tvec.end());
}


Node::Node()
{
	pos = Vector2D(0, 0);
	vel = Vector2D(0, 0);
	val = 1;
}

Node::Node(Vector2D _pos)
{
	pos = _pos;
	vel = Vector2D(0, 0);
	val = 1;
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

int Node::think()
{
	if ((val == 2) || (val == 3))
	{
		//Find adjacent nodes
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			for (int k = 0; k < 8; k++)
			{
				Vector2D cpos(pos.x + round(cos(k*(Pi() / 4))), pos.y + round(sin(k*(Pi() / 4))));
				if (nodes[i]->pos == cpos)
				{
					PushNode(nodes[i], adjacent);
				}
			}
		}

		//if input node
		if (val == 3)
		{
			//Find if the nodes are all on one side. If so, simulation can proceed.
			Vector2D compr(0, 0);	//Comparison vector
			for (int i = 0; i < (int)adjacent.size(); i++)
			{
				if (i == 0)
				{
					compr = pos - adjacent[i]->pos;
				}
				else
				{
					if (compr.x != pos.x-adjacent[i]->pos.x)
					{
						compr.x = 0;
					}
					if (compr.y != pos.y-adjacent[i]->pos.y)
					{
						compr.y = 0;
					}
				}
			}
			//std::cout << "Compr: " << compr << "\n";

			//If all nodes are on one side, continue and set velocities and stuff to the adjacent nodes, otherwise stop simulation.
			if (compr != Vector2D(0, 0))
			{
				//Add up the velocities
				for (int i = 0; i < (int)adjacent.size(); i++)
				{
					vel = vel + (adjacent[i]->pos - pos);
				}
				vel = vel.Normalized();
				vel = Vector2D(round(vel.x), round(vel.y));
				std::cout << "Total Vel: " << vel << "\n";

				//find if there is a node that perfectly fits the velocity. For breaking circuits.
				bool findPerfect = false;
				for (int i = 0; i < (int)adjacent.size(); i++)
				{
					if (adjacent[i]->pos == pos + vel)
					{
						findPerfect = true;
						printf("Found Perfect.\n");
						if (adjacent[i]->val != 0)
						{
							adjacent[i]->vel = adjacent[i]->vel + vel;
							adjacent[i]->val = 2;
							PushNode(adjacent[i], nextActiveNodes);
						}
					}
				}
				if (!findPerfect)
				{
					//If not, then just give each adjacent node a velocity relative to the node.
					for (int i = 0; i < (int)adjacent.size(); i++)
					{
						if (adjacent[i]->val != 0)
						{
							Vector2D givenvel = (adjacent[i]->pos - pos).Normalized();
							adjacent[i]->vel = adjacent[i]->vel + Vector2D(round(givenvel.x), round(givenvel.y));
							adjacent[i]->val = 2;
							PushNode(adjacent[i], nextActiveNodes);
						}
					}
				}
			}
			else
			{
				//Stop simulation if all nodes are not on one side.
				printf("Direction undecisive. Simulation stopped.\n");
				simState = -1;
				return 0;
			}
		}
		else if ((val == 2) && (vel != Vector2D(0,0)))		//else if the node is active and has a velocity, but not an input node.
		{
			//Find the number of adjacent nodes that are not dead.
			int adjacentNotDead = 0;
			for (int i = 0; i < (int)adjacent.size(); i++)
			{
				if (adjacent[i]->val > 0)
				{
					adjacentNotDead++;
				}
			}

			//If there is a single non-dead node attached, it can go any way.
			if (adjacentNotDead == 1)
			{
				for (int i = 0; i < (int)adjacent.size(); i++)
				{
					if (adjacent[i]->val != 0)
					{
						Vector2D givenvel = (adjacent[i]->pos - pos).Normalized();
						adjacent[i]->vel = adjacent[i]->vel + Vector2D(round(givenvel.x), round(givenvel.y));
						adjacent[i]->val = 2;
						PushNode(adjacent[i], nextActiveNodes);
					}
				}
			}
			else
			{
				//find if there is a node that perfectly fits the velocity. For breaking circuits.
				bool findPerfect = false;
				for (int i = 0; i < (int)adjacent.size(); i++)
				{
					if (adjacent[i]->pos == pos + vel)
					{
						findPerfect = true;
						printf("Found Perfect.\n");
						if (adjacent[i]->val != 0)
						{
							adjacent[i]->vel = adjacent[i]->vel + vel;
							adjacent[i]->val = 2;
							PushNode(adjacent[i], nextActiveNodes);
						}
					}
				}
				if (!findPerfect)
				{
					//If not, then just give each adjacent node a velocity relative to the node.
					for (int i = 0; i < (int)adjacent.size(); i++)
					{
						if (adjacent[i]->val != 0)
						{
							//If it's going in about the same vel.
//							if ((adjacent[i]->pos == pos + vel) || (adjacent[i]->pos == pos + Vector2D(vel.x, 0)) || (adjacent[i]->pos == pos + Vector2D(0, vel.y)))
//							if ((adjacent[i]->pos.x == pos.x + vel.x && adjacent[i]->pos.y == pos.y) || (adjacent[i]->pos.y == pos.y + vel.y && adjacent[i]->pos.x == pos.x))
							if (((adjacent[i]->pos - pos).x == vel.x && (adjacent[i]->pos - pos).y != -vel.y) || ((adjacent[i]->pos - pos).y == vel.y && (adjacent[i]->pos - pos).x != -vel.x))
							{
								Vector2D givenvel = (adjacent[i]->pos - pos).Normalized();
								adjacent[i]->vel = adjacent[i]->vel + Vector2D(round(givenvel.x), round(givenvel.y));
								adjacent[i]->val = 2;
								PushNode(adjacent[i], nextActiveNodes);
							}
						}
					}
				}
			}
		}
		else
		{
			printf("rip\n");
		}
		
		//Set to dead. Removed from active node vector somewhere else.
		if (val != 3)
		{
			val = 0;
			vel = Vector2D(0,0);
		}
	}

	return 1;
}

void Node::render()
{
	if (val == 0)
	{
		SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 0xFF);
	}
	else if (val == 2)
	{
		SDL_SetRenderDrawColor(gRenderer, 100, 200, 100, 0xFF);
	}
	else if (val == 3)
	{
		SDL_SetRenderDrawColor(gRenderer, 100, 100, 200, 0xFF);
	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	}
	renderDrawFillRect(pos, 1, 1);
}
