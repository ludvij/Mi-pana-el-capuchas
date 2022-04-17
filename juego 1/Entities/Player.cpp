#include "Player.h"
#include "Weapons/Wand.h"

Player::Player(int x, int y)
	: Entity(PLAYER_POS, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY),
	orientation(Orientation::NONE),
	state(State::IDLE)
{
	m_aIdleBack  = new Animation("rcs/player/player_idle_back.png",  width, height, 18, 3, true);
	m_aIdleFront = new Animation("rcs/player/player_idle_front.png", width, height, 18, 3, true);
	m_aIdleLeft  = new Animation("rcs/player/player_idle_left.png",  width, height, 18, 3, true);
	m_aIdleRight = new Animation("rcs/player/player_idle_right.png", width, height, 18, 3, true);

	m_aMoveBack  = new Animation("rcs/player/player_move_back.png",  width, height, 18, 4, true);
	m_aMoveFront = new Animation("rcs/player/player_move_front.png", width, height, 18, 4, true);
	m_aMoveLeft  = new Animation("rcs/player/player_move_left.png",  width, height, 18, 4, true);
	m_aMoveRight = new Animation("rcs/player/player_move_right.png", width, height, 18, 4, true);

	m_animation = m_aIdleFront;
	Weapon = new Wand(x, y);
}

Player::~Player()
{
	delete m_aIdleBack;
	delete m_aIdleFront;
	delete m_aIdleLeft;
	delete m_aIdleRight;

	delete m_aMoveBack;
	delete m_aMoveFront;
	delete m_aMoveLeft;
	delete m_aMoveRight;
}

void Player::MoveX(float multiplier) {
	Vec.x = multiplier * m_maxSpeed;
}
void Player::MoveY(float multiplier) {
	Vec.y = multiplier * m_maxSpeed;
}


void Player::Update() {
	bool endAnimation = m_animation->Update();
	if (Vec.x != 0 || Vec.y != 0)
		state = State::MOVING;
	if (Vec.y > 0 && Vec.y > Vec.x) {
		orientation = Orientation::DOWN;
	}
	else if (Vec.y < 0 && Vec.y < Vec.x) {
		orientation = Orientation::UP;
	}
	if (Vec.x > 0 && Vec.x > Vec.y) {
		orientation = Orientation::RIGHT;
	}
	else if (Vec.x < 0 && Vec.x < Vec.y) {
		orientation = Orientation::LEFT;
	}

	switch (state)
	{
	case State::MOVING:
		if (Vec.x != 0) {
			if (orientation == Orientation::RIGHT) {
				m_animation = m_aMoveRight;
			}
			else if (orientation == Orientation::LEFT) {
				m_animation = m_aMoveLeft;
			}
		}
		if (Vec.x == 0) {
			if (orientation == Orientation::RIGHT) {
				m_animation = m_aIdleRight;
			}
			else if (orientation == Orientation::LEFT) {
				m_animation = m_aIdleLeft;
			}
		}
		if (Vec.y != 0) {
			if (orientation == Orientation::UP) {
				m_animation = m_aMoveBack;
			}
			else if (orientation == Orientation::DOWN) {
				m_animation = m_aMoveFront;
			}
		}
		if (Vec.y == 0) {
			if (orientation == Orientation::UP) {
				m_animation = m_aIdleBack;
			}
			else if (orientation == Orientation::DOWN) {
				m_animation = m_aIdleFront;
			}
		}
		break;
	case State::DYING:
		break;
	case State::DEAD:
		break;
	default:
		break;
	}
	if (Weapon->Uses == 0) {
		delete Weapon;
		Weapon = new Wand(x, y);
		Weapon->cadence = cadence;
		Weapon->damage = dmg;
	}
	else {
		Weapon->x = x;
		Weapon->y = y;
		Weapon->Update();

	}

}

void Player::Draw(float scrollX)
{
	if (m_animation == nullptr)
		Entity::Draw(scrollX);
	else {
		m_animation->Draw(x - scrollX, y);
	}
	Weapon->Draw(scrollX);
}
