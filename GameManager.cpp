#include "GameManager.h"

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
	}
	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
	{
		mQuit = true;
	}

	mInput = InputManager::Instance();

	mGrid = Grid::Instance();
}

GameManager::~GameManager()
{
	Graphics::Release();
	mGraphics = NULL;

	Grid::Release();
	mGrid = NULL;
}

void GameManager::Run()
{
	while (!mQuit)
	{
		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
			if (mEvents.type == SDL_KEYDOWN)
			{
				if (mEvents.key.keysym.sym == SDLK_e)
				{
					mGrid->changeState();
				}
				else if (mEvents.key.keysym.sym == SDLK_RETURN)
				{
					mGrid->StartAlgo();
				}
			}
		}

		Update();
		Render();
	}
}

void GameManager::Update()
{
	mInput->Update();
}

void GameManager::Render()
{
	mGraphics->Clear();

	mGrid->Render();

	mGraphics->Render();
}