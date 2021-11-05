#include "Game.h"

#include "Layers/DebugLayer.h"

#include <iostream>

Game Game::s_Instance;

Game::~Game()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
}

void Game::GameLoop()
{
	int initTick;
	int endTick;
	int diffTick;

	while (m_loopActive) {
		initTick = SDL_GetTicks();

		// Controls
		layer->ProcessControls();

		// Update elements
		layer->Update();

		// Draw elements
		layer->Draw();

		// synchronisation mecanism
		endTick = SDL_GetTicks();
		diffTick = endTick - initTick;
		if (diffTick < MS_PER_FRAME) {
			SDL_Delay((int)MS_PER_FRAME - diffTick);
		}
	}
}

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}
	Window = SDL_CreateWindow("SEV: juego 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
	if (Window == nullptr)
	{
		std::cerr << "Error Window: " << SDL_GetError() << std::endl;
		return;
	}
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == nullptr)
	{
		std::cerr << "Error Window: " << SDL_GetError() << std::endl;
		return;
	}

	layer = new DebugLayer();
}

void Game::Run()
{
	m_loopActive = true;
	GameLoop();
}

SDL_Texture* Game::GetTexture(std::string_view filename)
{
    return nullptr;
}

