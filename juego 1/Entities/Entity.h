#pragma once
#pragma comment(lib, "rpcrt4.lib")

#include <rpc.h>
#include <string>
#include "Game.h"


class Entity 
{
public:

	Entity(std::string_view filename, int x, int y, int width, int height);

	virtual ~Entity() {};

	virtual void Draw(float ScrollX = 0);

	virtual bool IsOverlap(Entity* entity);

	bool IsInrender(float scrollX = 0);


	bool operator==(Entity ent);

	
	// position and size
	int x;
	int y;
	int width;
	int height;

	//velocity
	Vector2D Vec = { 0,0 };

	bool Pierceable = false;

	bool Deleted;

protected:

	//texture size
	SDL_Point m_texSize = { 0,0 };

	SDL_Texture* m_texture = nullptr;
private:
	UUID m_uuid;

};

