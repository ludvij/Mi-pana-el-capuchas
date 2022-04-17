#include "Bow.h"
Bow::Bow(int x, int y)
	: Weapon(BOW_POS, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	cadence = 30;
	shotTime = 30;
	projectileSpeed = 15;
	Uses = 10;
}

std::list<Projectile*> Bow::Use()
{
	std::list<Projectile*> res;
	if (Ready == true) {
		Ready = false;
		Uses--;
		// sdl uses degree but c++ uses radians
		float angle = Angle / 180.0f * static_cast<float>(M_PI);
		Vector2D vel = { std::cosf(angle), std::sinf(angle)};
		vel = -vel * projectileSpeed;
		res.push_back(new Projectile(ARROW_PROJECTILE_POS, x, y, width / 2,height / 2, Angle, 2, vel, damage));
	}
	return res;
}


