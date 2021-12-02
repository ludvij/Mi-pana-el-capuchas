#pragma once
#include "Entity.h"

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

private:
	float m_maxSpeed = 4;
};

