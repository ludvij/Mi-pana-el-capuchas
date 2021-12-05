#include "Tile.h"


Tile::Tile(std::string filename, int x, int y)
	: Entity(filename, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	Pierceable = false;
}

bool Tile::isPointInBounds(int x, int y)
{
	return x > (Tile::x - width / 2)  && x < (Tile::x + width / 2) 
		&& y > (Tile::y - height / 2) && y < (Tile::y + height / 2);
}
