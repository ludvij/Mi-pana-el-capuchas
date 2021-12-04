#include "Wand.h"

Wand::Wand(int x, int y)
	: Weapon("rcs/player/weapons/weapon_wand.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	ShotTime = 30;
}

Projectile* Wand::Use()
{
	if (Ready == true) {
		Ready = false;
		// sdl uses degree but c++ uses radians
		float angle = Angle / 180.0f * static_cast<float>(M_PI);
		Vector2D vel = { -std::cosf(angle) * 10, -std::sinf(angle) * 10 };
		return new Projectile(
			"rcs/player/weapons/projectile_wand.png",
			x,			// X center
			y,			// Y center
			width / 2,	// Width
			height / 2,	// Height
			Angle,		// Angle
			2,			// Pierce 
			vel			// Velocity
		);
	}
	return nullptr;
}

void Wand::Update()
{
	if (!Ready) ShotTime--;
	if (ShotTime <= 0) {
		Ready = true;
		ShotTime = 30;
	}
}
