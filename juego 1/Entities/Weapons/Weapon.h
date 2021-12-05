#pragma once
#include "Entities/Entity.h"
#include "Entities/Projectile.h"

enum class WeaponType {
	BOW,
	WAND,
	TRIPLE_WAND,
	NONE
};

class Weapon : public Entity
{
public:
	Weapon(std::string_view filename, int x, int y, int width, int height);
	~Weapon() {};

	virtual std::list<Projectile*> Use() = 0;

	virtual void Update();

	virtual void Draw(float scrollX = 0) override;
	virtual void Draw(float x, float y);

	WeaponType Type = WeaponType::NONE;

	float Angle = 0.0f;

	bool Ready = true;

	int Uses = -1;

	int damage = 1;

	int cadence = 30;


protected:
	int shotTime = -1;
	float projectileSpeed = 10;
};

