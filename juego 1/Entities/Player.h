#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void Update();
	void MoveX(float axis);
	void MoveY(float axis);


	virtual void Draw(float scrollX = 0) override;


	Orientation orientation;
	State state;
};

