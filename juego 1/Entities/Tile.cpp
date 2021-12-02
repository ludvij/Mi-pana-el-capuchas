#include "Tile.h"


Tile::Tile(std::string filename, int x, int y)
	: Entity(filename, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{

}
