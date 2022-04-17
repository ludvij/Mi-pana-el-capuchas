#include "Entity.h"


//Entity::Entity(std::string_view filename, int x, int y, int width, int height)
//	: x(x), y(y), width(width), height(height)
//{
//	m_texture = Game::Get().GetTexture(filename);
//	// get texture size
//	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texSize.x, &m_texSize.y);
//	// for comparation
//	if(UuidCreate(&m_uuid) != RPC_S_OK) {
//		LOG_ERROR("Error creating UUID");
//	}
//	Pierceable = true;
//	
//}

Entity::Entity(uint32_t sprite_x, uint32_t sprite_y, int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height)
{
	m_texture = Game::Get().GetTexture("rcs/spritesheet.png");
	
	m_renderRect.w = SPRITE_SIZE_X;
	m_renderRect.h = SPRITE_SIZE_Y;
	m_renderRect.x = SPRITE_SIZE_X * sprite_x;
	m_renderRect.y = SPRITE_SIZE_Y * sprite_y;
	// for comparation
	if (UuidCreate(&m_uuid) != RPC_S_OK) {
		LOG_ERROR("Error creating UUID");
	}
	Pierceable = true;

}



void Entity::ChangeRenderRect(uint32_t sprite_x, uint32_t sprite_y)
{
	m_renderRect.x = sprite_x;
	m_renderRect.y = sprite_y;
}

void Entity::Draw(float scrollX)
{
	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = std::round(x - width / 2.0f);
	destination.y = std::round(y - height / 2.0f);
	destination.w = width;
	destination.h = height;
	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &m_renderRect, &destination, 0, nullptr, SDL_FLIP_NONE);
#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));
#endif // OUTLINE
}

bool Entity::IsOverlap(Entity* entity)
{
	bool overlap = false;
	if (entity->x - entity->width / 2 <= x + width / 2
		&& entity->x + entity->width / 2 >= x - width / 2
		&& entity->y + entity->height / 2 >= y - height / 2
		&& entity->y - entity->height / 2 <= y + height / 2) {
		overlap = true;
	}
	return overlap;
}
bool Entity::IsInrender(float scrollX)
{
	
	if((x - scrollX) - width / 2 <= Game::Get().Width && (x - scrollX) + width / 2 >= 0 &&
		y - height / 2 <= Game::Get().Height && y + height / 2 >= 0) {
		return true;
	}
	return false;
}

bool Entity::operator==(Entity& ent)
{
	RPC_STATUS status;
	bool res = UuidEqual(&m_uuid, &ent.m_uuid, &status);
	if (status != RPC_S_OK) LOG_ERROR("Error occured comparing uuids");
	return res;
}

std::ostream& operator<<(std::ostream& os, const Entity& e)
{
	char* str;
	if (UuidToStringA(&e.m_uuid, reinterpret_cast<RPC_CSTR*>(&str)) != RPC_S_OK) {
		LOG_ERROR("ERROR CREATING UUID STRING");
	}
	os << str;
	RpcStringFreeA(reinterpret_cast<RPC_CSTR*>(&str));
	return os;
}
