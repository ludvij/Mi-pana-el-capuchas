#include "Wand.h"

Wand::Wand(int x, int y)
	: Weapon("rcs/player/weapons/weapon_wand.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	shotTime = 30;
	Ready = false;
	cadence = 30;
	projectileSpeed = 10;
}

std::list<Projectile*> Wand::Use()
{
	std::list<Projectile*> res;
	if (Ready == true) {
		Ready = false;
		// sdl uses degree but c++ uses radians
		float angle = Angle / 180.0f * static_cast<float>(M_PI);
		Vector2D vel = { std::cosf(angle),std::sinf(angle) };
		vel = -vel * projectileSpeed;
		res.push_back(new Projectile("rcs/player/weapons/projectile_wand.png", x, y, width / 2, height / 2, Angle, 1, vel, damage));
	}
	return res;
}
