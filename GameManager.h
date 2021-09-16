#pragma once
#include <SDL.h>
#include "Graphics.h"
#include "Grid.h"

class GameManager {

public:

	static GameManager* Instance();
	static void Release();

	void Run();

private:

	static GameManager* sInstance;

	bool mQuit;

	Graphics* mGraphics;
	InputManager* mInput;
	Grid* mGrid;

	SDL_Event mEvents;

	GameManager();
	~GameManager();

	void Update();
	void Render();
};