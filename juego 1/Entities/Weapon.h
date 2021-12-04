#pragma once
#include "Entity.h"
#include "Projectile.h"

enum class WeaponType {
	BOW,
	WAND,
	NONE
};

class Weapon : public Entity
{
public:
	Weapon(std::string_view filename, int x, int y, int width, int height);
	~Weapon() {};

	virtual Projectile* Use() = 0;

	virtual void Update() = 0;

	virtual void Draw(float scrollX = 0) override;

	WeaponType Type = WeaponType::NONE;

	float Angle = 0.0f;

	int ShotTime = -1;
	bool Ready = true;

private:
};

