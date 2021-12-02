#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void Update();
	void moveX(float axis);
	void moveY(float axis);


	virtual void Draw(float scrollX = 0) override;


	Orientation orientation;
	State state;
};

