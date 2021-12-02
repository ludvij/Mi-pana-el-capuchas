#include "Game.h"

#include "Layers/GameLayer.h"

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

		// events and controls
		processGameEvents();

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

	// initialise random number generator
	std::random_device device;
	m_mt = std::mt19937(device());

	layer = new GameLayer();
}

void Game::processGameEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			Game::Get().Stop();
		}
		layer->ProcessControls(event);
	}
}

void Game::Run()
{
	m_loopActive = true;
	GameLoop();
}

int Game::randomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(m_mt);
}

void Game::Present()
{
	SDL_RenderPresent(Renderer);
}

SDL_Texture* Game::GetTexture(std::string_view filename)
{
	const char* data = filename.data();

	if (mapTexture.find(data) != mapTexture.end()) {
		std::cout << '\t' << "retorno recurso cacheado: " << filename << std::endl;
	}
	else {
		std::cout << '\t' << "Nuevo hay que cachearlo " << filename << std::endl;
		SDL_Surface* surface = IMG_Load(data);
		if (surface == nullptr)
		{
			std::cout << '\t' << "Archivo no encontrado " << filename << std::endl;
			SDL_FreeSurface(surface);
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
		mapTexture[data] = texture;

		SDL_FreeSurface(surface);
	}

	return mapTexture[data];
}

