#include "Entities/Entity.h"


Entity::Entity(std::string_view filename, int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height)
{
	m_texture = Game::Get().GetTexture(filename);
	// get texture size
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texSize.x, &m_texSize.y);
}

Entity::Entity(int x, int y)
	: x(x), y(y), width(0), height(0)
{

}

void Entity::Draw(float scrollX)
{
	// tama�o de la textura
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = m_texSize.x;
	source.h = m_texSize.y;
	// tama�o de la entidad
	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;
#ifdef _DEBUG
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
#endif // _DEBUG
	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
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
