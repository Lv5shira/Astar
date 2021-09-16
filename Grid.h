#pragma once
#include "Graphics.h"
#include "Astar.h"
#include "InputManager.h"

class Grid
{
	enum NODESTATE{ start = 0, end, wall };
public:

	const float WIDTH = 64.0f;
	const float HEIGHT = WIDTH;


	static Grid* Instance();
	static void Release();

	void changeState();

	void StartAlgo();

	void Render();

private:

	static Grid* sInstance;

	Node* _start;
	Node* _end;
	std::vector<std::vector<Node*>> grid;
	std::vector<Node*> path;

	std::vector<Vector2> walls;

	Vector2 start_pos;
	Vector2 end_pos;
	Vector2 mousePos;

	bool hasStart;
	bool hasEnd;

	int rows;
	int columns;

	Graphics* mGraphics;
	InputManager* mInputManager;
	Astar* mAstar;

	NODESTATE state;

	Grid();
	~Grid();

	void Draw();
	void DrawPath();

	void AddNodes();
	void ConnectNodes();
	void StartNode();
	void EndNode();
	void WallNode();
	void LoopCase();
	

};