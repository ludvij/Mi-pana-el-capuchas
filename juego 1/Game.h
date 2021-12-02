#pragma once

#include "Layers/Layer.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <random>
#include <map>

constexpr float MS_PER_FRAME = 1000 / 75;


class Layer;


struct Vector2D {
	float x;
	float y;
};

enum class Input {
	KEYBOARD,
	CONTROLLER,
};

enum class State {
	MOVING,
	DYING,
	DEAD,
	SHOOTING,
	NONE,
};

enum class Orientation : int {
	NONE  = 0,
	UP    = 0b1,
	DOWN  = 0b10,
	LEFT  = 0b100,
	RIGHT = 0b1000,
};

class Game
{
public:
	Game(const Game&) = delete;
	~Game();

	void Run();
	inline void Stop() { m_loopActive = false; };

	inline static Game& Get() { return s_Instance; }

	int randomInt(int min, int max);

	void Present();


	SDL_Texture* GetTexture(std::string_view filename);

	void GameLoop();

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	uint32_t Width = 800;
	uint32_t Height = 800;

private:

	Game();

	void processGameEvents();

private:

	std::map<std::string, SDL_Texture*> mapTexture; 
	std::mt19937 m_mt;

	bool m_loopActive = false;

	Layer* layer = nullptr;

	static Game s_Instance;
};

