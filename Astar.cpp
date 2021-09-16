#include "Astar.h"

Astar::Astar()
{
	mGraphics = Graphics::Instance();
}

Astar::~Astar()
{
	Graphics::Release();
	mGraphics = NULL;
}

std::vector<Node*> Astar::CreatePath(Node* start, Node* end)
{
	path.clear();
	checked.push_back(end);

	while (path.size() == 0)
	{
		Node* temp = nullptr;
		int counter = 0;
		for (int i = 0; i < checked.size(); i++)
		{
			if (!checked[i]->isWall)
			{
				if (i == 0)
				{
					temp = checked[i];
				}
				else if (temp->F > checked[i]->F)
				{
					temp = checked[i];
					counter = i;
				}
				else if (temp->F == checked[i]->F)
				{
					if (temp->G > checked[i]->G)
					{
						temp = checked[i];
						counter = i;
					}
				}
			}
		}
		visited.push_back(temp);
		checked.erase(checked.begin() + counter);
		if (CheckNodes(start, temp))
		{
			path.push_back(temp);
			while (temp->parent != nullptr)
			{
				path.push_back(temp->parent);
				if(temp->parent != nullptr)
					temp = temp->parent;
			}
			return path;
		}
		for (int i = 0; i < temp->cn.size(); i++) //Loop through neighbor
		{
			if (!temp->cn[i]->isWall)
			{
				if (checked.size() == 0)
				{
					Distance(start, end, temp->cn[i]);
					temp->cn[i]->parent = temp;
					checked.push_back(temp->cn[i]);
				}
				else
				{
					bool inClosed = false;
					for (int j = 0; j < visited.size(); j++) //Check if neighbor in closed
					{
						if (CheckNodes(temp->cn[i], visited[j]))
						{
							inClosed = true;
							j = visited.size();
						}
					}
					if (inClosed == false)
					{
						bool inOpen = false;

						for (int k = 0; k < checked.size(); k++) //Check if neighbor in open
						{
							if (CheckNodes(temp->cn[i], checked[k]))
							{
								inOpen = true;
								k = checked.size();
							}
						}

						if (inOpen == false)
						{
							Distance(start, end, temp->cn[i]);
							temp->cn[i]->parent = temp;
							checked.push_back(temp->cn[i]);
						}
					}
				}
			}
		}
	}
}

void Astar::Distance(Node* start, Node* end, Node*node)
{
	node->G = VectorDistance(start->pos, node->pos);
	node->H = VectorDistance(end->pos, node->pos);
	node->F = node->G + node->H;
}

bool Astar::CheckNodes(Node* a, Node* b)
{
	if ((b->pos.x == a->pos.x) && (b->pos.y == a->pos.y))
	{
		return true;
	}
	return false;
}