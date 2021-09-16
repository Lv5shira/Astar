#include "Grid.h"

Grid* Grid::sInstance = NULL;

Grid* Grid::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Grid();
	}
	return sInstance;
}

void Grid::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Grid::Grid()
{
	start_pos = NULL;
	end_pos = NULL;

	mGraphics = Graphics::Instance();

	rows = mGraphics->SCREEN_HEIGHT / HEIGHT;
	columns = mGraphics->SCREEN_WIDTH / WIDTH;

	mInputManager = InputManager::Instance();

	state = start;

	mAstar = new Astar();

	hasStart = false;
	hasEnd = false;

	AddNodes();
}

Grid::~Grid()
{
	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputManager = NULL;
}

void Grid::Draw()
{
	if (hasStart)
		mGraphics->DrawRect(start_pos, {255, 223, 0});
	if (hasEnd)
		mGraphics->DrawRect(end_pos, {0, 255, 255});
	for (int i = 0; i < walls.size(); i++)
	{
		mGraphics->DrawRect(walls[i], { 0, 0 ,0 });
		//printf("x: %f, y: %f \n", walls[i].x, walls[i].y);
	}

	for (int i = 1; i < rows; i++)
	{
		mGraphics->DrawLine(0.0f, i * HEIGHT, mGraphics->SCREEN_WIDTH, i * HEIGHT);
	}

	for (int i = 1; i < columns; i++)
	{
		mGraphics->DrawLine(i * WIDTH, 0.0f, i * WIDTH, mGraphics->SCREEN_HEIGHT);
	}
}

void Grid::AddNodes()
{
	for (int i = 0; i < rows; i++)
	{
		std::vector<Node*> row;
		for (int j = 0; j < columns; j++)
		{
			Node* n = new Node(Vector2((WIDTH / 2 + WIDTH * j), (HEIGHT / 2 + HEIGHT * i)));
			row.push_back(n);
			//mGraphics->DrawLine((WIDTH/2 + WIDTH * j), (HEIGHT/2 + HEIGHT * i), (WIDTH/2 + WIDTH * j) + 1, (HEIGHT/2 + HEIGHT* i) + 1);
			//printf("x: %f, y: %f \n", n->pos.x, n->pos.y);
		}
		grid.push_back(row);
	}
	ConnectNodes();
}

void Grid::ConnectNodes()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i - 1 >= 0)
			{
				grid[i][j]->cn.push_back(grid[i - 1][j]); //Top
			}
			if (i + 1 < rows)
			{
				grid[i][j]->cn.push_back(grid[i + 1][j]); //Bottom
			}
			if (j - 1 >= 0)
			{
				grid[i][j]->cn.push_back(grid[i][j - 1]); //Left
			}
			if (j + 1 < columns)
			{
				grid[i][j]->cn.push_back(grid[i][j + 1]); //Right
			}
		}
	}
}

void Grid::StartNode()
{
	mousePos = mInputManager->MousePos();
	//printf("x: %f, y: %f \n", mousePos.x, mousePos.y);
	if (mInputManager->MouseButtonDown(InputManager::left))
	{
		if (!hasStart)
		{
			int x = floor(mousePos.x);
			int y = floor(mousePos.y);
			//printf("floor x: %i, y: %i\n", x, y);
			int i = x / 64;
			int j = y / 64;
			if (!grid[j][i]->isStart)
			{
				grid[j][i]->isStart = true;
				grid[j][i]->isEnd = false;
				grid[j][i]->isWall = false;
				_start = grid[j][i];
				start_pos = { grid[j][i]->pos.x - 32, grid[j][i]->pos.y - 32 };
				hasStart = true;
				//printf("startpos x: %f, y: %f", grid[j][i]->pos.x - 32, grid[j][i]->pos.y - 32);
			}
		}
	}
	else if (mInputManager->MouseButtonDown(InputManager::right))
	{
		int x = floor(mousePos.x);
		int y = floor(mousePos.y);
		int i = x / 64;
		int j = y / 64;
		if (grid[j][i]->isStart)
		{
			grid[j][i]->isStart = false;
			start_pos = NULL;
			hasStart = false;
		}
	}
}

void Grid::EndNode()
{
	mousePos = mInputManager->MousePos();
	if (mInputManager->MouseButtonDown(InputManager::left))
	{
		if (!hasEnd)
		{
			int x = floor(mousePos.x);
			int y = floor(mousePos.y);
			int i = x / 64;
			int j = y / 64;
			if (!grid[j][i]->isEnd)
			{
				grid[j][i]->isEnd = true;
				grid[j][i]->isStart = false;
				grid[j][i]->isWall = false;
				_end = grid[j][i];
				end_pos = { grid[j][i]->pos.x - 32, grid[j][i]->pos.y - 32 };
				hasEnd = true;
			}
		}
	}
	else if (mInputManager->MouseButtonDown(InputManager::right))
	{
		int x = floor(mousePos.x);
		int y = floor(mousePos.y);
		int i = x / 64;
		int j = y / 64;
		if (grid[j][i]->isEnd)
		{
			grid[j][i]->isEnd = false;
			end_pos = NULL;
			hasEnd = false;
		}
	}
}

void Grid::WallNode()
{
	mousePos = mInputManager->MousePos();
	if (mInputManager->MouseButtonPress(InputManager::left))
	{
		int x = floor(mousePos.x);
		int y = floor(mousePos.y);
		int i = x / 64;
		int j = y / 64;
		if (!grid[j][i]->isWall && !grid[j][i]->isEnd && !grid[j][i]->isStart)
		{
			grid[j][i]->isWall = true;
			grid[j][i]->isStart = false;
			grid[j][i]->isEnd = false;
			walls.push_back({ grid[j][i]->pos.x - 32, grid[j][i]->pos.y - 32 });
		}
	}
	else if (mInputManager->MouseButtonPress(InputManager::right))
	{
		int x = floor(mousePos.x);
		int y = floor(mousePos.y);
		int i = x / 64;
		int j = y / 64;
		if (grid[j][i]->isWall)
		{
			int counter = 0;
			for (int k = 0; k < walls.size(); k++)
			{
				if (grid[j][i]->pos.x-32 == walls[k].x && grid[j][i]->pos.y-32 == walls[k].y)
				{
					//printf("x: %f, y: %f", walls[k].x, walls[k].y);
					walls.erase(walls.begin() + counter);
					break;
				}
				counter++;
			}
			grid[j][i]->isWall = false;
		}
	}
}

void Grid::StartAlgo()
{
	if (hasEnd && hasStart)
	{
		path = mAstar->CreatePath(_start, _end);
		printf("start x: %f, y: %f\n", _start->pos.x, _start->pos.y);
		for (int i = 0; i < path.size(); i++)
		{
			printf("PATH");
			printf("x: %f, y: %f, F: %f\n", path[i]->pos.x, path[i]->pos.y, path[i]->F);
		}
		printf("end x: %f, y: %f\n", _end->pos.x, _end->pos.y);
	}
	else
	{
		printf("No start or End Node");
	}
}

void Grid::DrawPath()
{
	for (int i = 1; i < path.size()-1; i++)
	{
		mGraphics->DrawRect({ path[i]->pos.x - 32.0f, path[i]->pos.y - 32.0f }, { 255, 0, 0 });
	}
}

void Grid::changeState()
{
	if (state == wall)
		state = start;
	else
		state = static_cast<NODESTATE>(state + 1);

	//printf("%i", state);
}

void Grid::LoopCase()
{
	switch (state)
	{
	case(start):
		StartNode();
		break;
	case(end):
		EndNode();
		break;
	case(wall):
		WallNode();
		break;
	}
}


void Grid::Render()
{
	LoopCase();

	if (path.size() != 0)
	{
		DrawPath();
	}
	Draw();

}