#pragma once

#include "Layers/Layer.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>

constexpr float MS_PER_FRAME = 1000 / 75;


class Layer;

class Game
{
public:
	Game(const Game&) = delete;
	~Game();

	void Run();
	inline void Stop() { m_loopActive = false; };

	inline static Game& Get() { return s_Instance; }


	SDL_Texture* GetTexture(std::string_view filename);

	void GameLoop();

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	uint32_t Width = 800;
	uint32_t Height = 800;

private:
	Game();

	bool m_loopActive = false;

	Layer* layer = nullptr;

	static Game s_Instance;
};

