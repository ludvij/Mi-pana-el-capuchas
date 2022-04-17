#pragma once

#include "Game.h"


class Layer
{
public:
	Layer() {};

	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void ProcessControls(SDL_Event event) = 0;
};

