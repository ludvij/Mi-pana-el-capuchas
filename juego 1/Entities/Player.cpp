#include "Player.h"

Player::Player(int x, int y)
	: Entity("rcs/player.png", x, y, 70, 70),
	orientation(Orientation::NONE),
	state(State::NONE)
{
}

Player::~Player()
{
}

void Player::MoveX(float axis) {
	Vec.x = axis * 3;
}
void Player::MoveY(float axis) {
	Vec.y = axis * 3;
}

void Player::Update() {
	if (Vec.x > 0) {
		orientation = Orientation::RIGHT;
	}
	else if (Vec.x < 0) {
		orientation = Orientation::LEFT;
	}
	if (Vec.y > 0) {
		orientation = Orientation::DOWN;
	}
	else if (Vec.y < 0) {
		orientation = Orientation::UP;
	}

	switch (state)
	{
	case State::MOVING:
		if (Vec.x != 0) {
			if (orientation == Orientation::RIGHT) {
				// TODO: animation
			}
			else if (orientation == Orientation::LEFT) {
				// TODO: animation
			}
		}
		if (Vec.x == 0) {
			if (orientation == Orientation::RIGHT) {
				// TODO: animation
			}
			else if (orientation == Orientation::LEFT) {
				// TODO: animation
			}
		}
		break;
	case State::DYING:
		break;
	case State::DEAD:
		break;
	case State::SHOOTING:
		break;
	default:
		break;
	}
}

void Player::Draw(float scrollX)
{
	Entity::Draw(scrollX);
}
