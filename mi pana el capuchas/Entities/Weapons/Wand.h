#pragma once
#include "Weapon.h"
class Wand : public Weapon
{
public:
	Wand(int x, int y);

	virtual std::list<Projectile*> Use() override;


	WeaponType Type = WeaponType::WAND;
};

