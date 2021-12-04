#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Weapon.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void Update();
	void MoveX(float multiplier);
	void MoveY(float multiplier);


	virtual void Draw(float scrollX = 0) override;


	Orientation orientation;
	State state;
	Weapon* Weapon;

private:
	float m_maxSpeed = 4;

	Animation* m_aIdleFront;
	Animation* m_aIdleBack;
	Animation* m_aIdleLeft;
	Animation* m_aIdleRight;

	Animation* m_aMoveFront;
	Animation* m_aMoveBack;
	Animation* m_aMoveLeft;
	Animation* m_aMoveRight;

	Animation* m_animation;

};

