#pragma once
#include "Weapon.h"
class Bow : public Weapon
{
public:
	Bow(int x, int y);

	virtual std::list<Projectile*> Use() override;


	WeaponType Type = WeaponType::BOW;
};

