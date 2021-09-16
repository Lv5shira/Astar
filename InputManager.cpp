#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
{
	Uint32 mask = 0;
	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	}

	return mMouseState & mask;
}

bool InputManager::MouseButtonPress(MOUSE_BUTTON button)
{

	Uint32 mask = 0;
	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	}

	return !(mPrevMouseState & mask) && (mMouseState & mask);
}


Vector2 InputManager::MousePos()
{
	return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

void InputManager::Update() {

	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePrevInput()
{
	mPrevMouseState = mMouseState;
}