#pragma once
#pragma comment(lib, "rpcrt4.lib")

#include <rpc.h>
#include <string>
#include "Game.h"
#include "Sprite_pos.h"

class Entity 
{
public:

	//Entity(std::string_view filename, int x, int y, int width, int height);

	Entity(uint32_t sprite_x, uint32_t sprite_y, int x, int y, int width, int height);

	virtual ~Entity() {};

	void ChangeRenderRect(uint32_t sprite_x, uint32_t sprite_y);

	virtual void Draw(float ScrollX = 0);

	virtual bool IsOverlap(Entity* entity);

	bool IsInrender(float scrollX = 0);


	bool operator==(Entity& ent);

	friend std::ostream& operator<< (std::ostream& os, const Entity& vector);

	
	// position and size
	float x;
	float y;
	int width;
	int height;

	//velocity
	Vector2D Vec = { 0,0 };

	bool Pierceable = false;

	bool Deleted = false;


	SDL_Texture* m_texture = nullptr;

protected:
	SDL_Rect m_renderRect;

private:

	UUID m_uuid;

};

