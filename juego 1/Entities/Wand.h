#pragma once
#include "Weapon.h"
class Wand : public Weapon
{
public:
	Wand(int x, int y);

	virtual Projectile* Use() override;

	virtual void Update() override;

	WeaponType Type = WeaponType::WAND;
};

