#include "Game.h"

#include "Layers/GameLayer.h"
#include "Layers/EndLayer.h"
#include "Layers/PowerUpLayer.h"

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
		LOG_ERROR("Error SDL_Init: " << SDL_GetError());
		return;
	}
	Window = SDL_CreateWindow("SEV: juego 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
	if (Window == nullptr)
	{
		LOG_ERROR("Error Window : " << SDL_GetError());
		return;
	}
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == nullptr)
	{
		LOG_ERROR("Error Window: " << SDL_GetError());
		return;
	}

	// initialise random number generator
	std::random_device device;
	m_mt = std::mt19937(device());

	gameLayer = new GameLayer();
	endLayer = new EndLayer();
	intersectionLayer = new PowerUpLayer();

	layer = gameLayer;
	Sheet = GetTexture("rcs/spritesheet.png");
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
	SDL_SetRenderDrawColor(Renderer, HEX_COLOR(0));
	SDL_RenderClear(Renderer);
}





SDL_Texture* Game::GetTexture(std::string_view filename)
{
	const char* data = filename.data();

	if (mapTexture.find(data) != mapTexture.end()) {
		LOG_INFO("Retrieved cached texture: " << filename);
	}
	else {
		LOG_INFO("Cached new texture: " << filename);
		SDL_Surface* surface = IMG_Load(data);
		if (surface == nullptr)
		{
			LOG_ERROR("File not found: " << filename);
			SDL_FreeSurface(surface);
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
		mapTexture[data] = texture;

		SDL_FreeSurface(surface);
	}

	return mapTexture[data];
}

