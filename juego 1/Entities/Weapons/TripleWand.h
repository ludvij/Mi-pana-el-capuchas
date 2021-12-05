#pragma once
#include "Weapon.h"

class TripleWand : public Weapon
{
public:
	TripleWand(int x, int y);

	virtual std::list<Projectile*> Use() override;


	WeaponType Type = WeaponType::TRIPLE_WAND;
};

