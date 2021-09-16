#pragma once
#include <SDL.h>
#include "Types.h"


class InputManager
{

public:

	enum MOUSE_BUTTON{left = 0, right};

	static InputManager* Instance();
	static void Release();

	bool MouseButtonDown(MOUSE_BUTTON button);
	bool MouseButtonPress(MOUSE_BUTTON button);

	Vector2 MousePos();

	void Update();
	void UpdatePrevInput();

private:

	static InputManager* sInstance;

	const Uint8* mKeyState;

	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;

	int mMouseXPos;
	int mMouseYPos;

};