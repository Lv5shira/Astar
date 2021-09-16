#include "Graphics.h"

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInit = false;

Graphics* Graphics::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Graphics();
	}
	return sInstance;
}

void Graphics::Release()
{
    delete sInstance;
    sInstance = NULL;

    sInit = false;
}

bool Graphics::Initialized()
{
    return sInit;
}

Graphics::Graphics()
{
    sInit = init();
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_Quit();
}

bool Graphics::init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void Graphics::DrawLine(float sX, float sY, float eX, float eY)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, sX, sY, eX, eY);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Graphics::DrawRect(Vector2 vec, Color color)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect fillRect = { vec.x, vec.y, 64, 64 };
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
}

void Graphics::Clear()
{
    SDL_RenderClear(gRenderer);
}

void Graphics::Render()
{
    SDL_RenderPresent(gRenderer);
}