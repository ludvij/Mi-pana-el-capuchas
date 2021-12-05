#pragma once

#include "Game.h"

class Animation
{
public:
	Animation(std::string_view filename, int actorWidth, int actorHeight,
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
	int m_entityWidth;
	int m_entityHeight;
	int m_fileWidth;
	int m_fileHeight;
	SDL_Texture* m_texture;
	int m_frameWidth;
	int m_frameHeight;
	SDL_Rect m_source;

};

