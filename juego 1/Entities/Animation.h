#pragma once

#include "Game.h"
#include "SpriteSheet.h"

class Animation
{
public:
	Animation(uint32_t sprite_x, uint32_t sprite_y, int actorWidth, int actorHeight,
		int updateFrequence, int totalFrames, bool loop);
	~Animation() {};

	bool Update();
	void Draw(float x, float y);

	int TotalFrames;
	int CurrentFrame;
	bool Loop;
	int UpdateFrequence;
	int UpdateTime;

private:
	uint32_t m_startX;
	int m_entityWidth;
	int m_entityHeight;
	SDL_Rect m_renderRect{};
};

