#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Types.h"

class Graphics
{

public:

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	const char* WINDOW_TITLE = "A* Algo";
	
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	void DrawLine(float sX, float sY, float eX, float eY);
	void DrawRect(Vector2 vec, Color color);

	void Clear();

	void Render();
private:

	static Graphics* sInstance;
	static bool sInit;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;

	SDL_Renderer* gRenderer = NULL;


	Graphics();
	~Graphics();

	bool init();

};