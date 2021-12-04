#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Layers/Layer.h"


#include <string>
#include <random>
#include <map>
#include <iostream>

#ifdef _DEBUG
	#define LOG
	//#define OUTLINE
#endif // _DEBUG


#ifdef LOG
	#define LOG_ERROR(x) std::cerr << "\x1B[31m[ERROR]: " << x << "\x1B[0m" << std::endl
	#define LOG_TRACE(x) std::cout << "[TRACE]: "         << x              << std::endl
	#define LOG_INFO(x)  std::cout << "\x1B[36m[INFO]: "  << x << "\x1B[0m" << std::endl
#else
	#define LOG_ERROR(x)
	#define LOG_TRACE(x) 
	#define LOG_INFO(x)
#endif

#define HEX_COLOR(code) \
  ((code) >> (3 * 8)) & 0xFF, \
  ((code) >> (2 * 8)) & 0xFF, \
  ((code) >> (1 * 8)) & 0xFF, \
  ((code) >> (0 * 8)) & 0xFF



constexpr float MS_PER_FRAME = 1000.0f / 60.0f;


class Layer;


struct Vector2D {
	float x;
	float y;
};

enum class Input {
	NONE,
	KEYBOARD,
	CONTROLLER,
};

enum class State {
	MOVING,
	DYING,
	DEAD,
	SHOOTING,
	IDLE,
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
	Input Input = Input::NONE;

	uint32_t Width = 900;
	uint32_t Height = 900;

	int CellSizeX = Width / 18;
	int CellSizeY = Height / 18;

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

