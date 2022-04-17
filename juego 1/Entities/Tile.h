#pragma once
#include "Entity.h"
class Tile : public Entity
{
public:
	Tile(uint32_t sprite_x, uint32_t sprite_y, int x, int y);

	bool isPointInBounds(int x, int y);
};


