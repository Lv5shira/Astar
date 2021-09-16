#pragma once
#include <vector>
#include "Types.h"
#include "Graphics.h"

class Astar
{
public:
	std::vector<Node*> CreatePath(Node* start, Node* end);

	Astar();
	~Astar();

	void Render();
	
private:

	Graphics* mGraphics;

	std::vector<Node*> visited; //Closed List
	std::vector<Node*> checked; //Open List
	std::vector<Node*> path;


	void Distance(Node* start, Node* end, Node *node);

	bool CheckNodes(Node* a, Node* b);
};