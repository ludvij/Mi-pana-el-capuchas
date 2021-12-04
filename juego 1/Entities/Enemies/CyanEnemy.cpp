#include "CyanEnemy.h"

CyanEnemy::CyanEnemy(int x, int y)
	: Enemy("rcs/enemies/enemy_cyan.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_animation = new Animation("rcs/enemies/enemy_cyan_idle.png", width, height, 18, 3, true);
	Health = 3;
}
