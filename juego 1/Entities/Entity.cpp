#include "Entity.h"


Entity::Entity(std::string_view filename, int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height)
{
	m_texture = Game::Get().GetTexture(filename);
	// get texture size
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texSize.x, &m_texSize.y);
	// for comparation
	if(UuidCreate(&m_uuid) != RPC_S_OK) {
		LOG_ERROR("Error creating UUID");
	}
	
}



void Entity::Draw(float scrollX)
{
	// tamaño de la textura
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = m_texSize.x;
	source.h = m_texSize.y;
	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = std::round(x - width / 2.0f);
	destination.y = std::round(y - height / 2.0f);
	destination.w = width;
	destination.h = height;
	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
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
	bool res = UuidEqual(&m_uuid, &(ent.m_uuid), &status);
	if (status != RPC_S_OK) LOG_ERROR("Error occured comparing uuids");
	return res;
}

