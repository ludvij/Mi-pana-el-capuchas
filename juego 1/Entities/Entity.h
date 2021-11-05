#pragma once

#include "Game.h"
#include <string>


class Entity 
{
public:

	Entity(std::string_view filename, int x, int y, int w, int h);
	Entity(int x, int y, int w=0, int h=0);

	virtual ~Entity() {};

	virtual void Draw();

	virtual void DrawOutline(bool fill = false);

	
	// position and size
	int x;
	int y;
	int w;
	int h;

	//velocity
	SDL_Point Vec = { 0,0 };


private:
	//texture size
	SDL_Point m_texSize = { 0,0 };

	SDL_Texture* m_texture = nullptr;

};

