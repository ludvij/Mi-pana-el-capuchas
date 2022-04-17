#include "Tile.h"


Tile::Tile(uint32_t sprite_x, uint32_t sprite_y, int x, int y)
	: Entity(sprite_x, sprite_y, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	Pierceable = false;
}

bool Tile::isPointInBounds(int x, int y)
{
	return x > (Tile::x - width / 2)  && x < (Tile::x + width / 2) 
		&& y > (Tile::y - height / 2) && y < (Tile::y + height / 2);
}
