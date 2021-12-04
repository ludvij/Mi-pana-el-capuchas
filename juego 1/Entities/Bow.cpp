#include "Bow.h"
Bow::Bow(int x, int y)
	: Weapon("rcs/player/weapons/weapon_bow.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
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
		res.push_back(new Projectile("rcs/player/weapons/projectile_bow.png", x, y, width / 2,height / 2, Angle, 2, vel));
	}
	return res;
}

void Bow::Update()
{
	if (!Ready) shotTime--;
	if (shotTime <= 0) {
		Ready = true;
		shotTime = 30;
	}
}

