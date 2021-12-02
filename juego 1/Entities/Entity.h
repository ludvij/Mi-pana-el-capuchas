#pragma once

#include "Game.h"
#include <string>


class Entity 
{
public:

	Entity(std::string_view filename, int x, int y, int width, int height);
	Entity(int x, int y);

	virtual ~Entity() {};

	virtual void Draw(float ScrollX = 0);

	bool IsOverlap(Entity* entity);

	bool IsInrender(float scrollX = 0);


	
	// position and size
	int x;
	int y;
	int width;
	int height;

	//velocity
	Vector2D Vec = { 0,0 };


private:

private:
	//texture size
	SDL_Point m_texSize = { 0,0 };

	SDL_Texture* m_texture = nullptr;

};

