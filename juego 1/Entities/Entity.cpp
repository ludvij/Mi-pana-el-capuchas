#include "Entities/Entity.h"


Entity::Entity(std::string_view filename, int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{
	m_texture = Game::Get().GetTexture(filename);
	// get texture size
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texSize.x, &m_texSize.y);
}

Entity::Entity(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{

}

void Entity::Draw()
{
	// tamaño de la textura
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = m_texSize.x;
	source.h = m_texSize.y;
	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = x - w / 2;
	destination.y = y - h / 2;
	destination.w = w;
	destination.h = h;

	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
}

void Entity::DrawOutline(bool fill)
{
	SDL_Rect destination;
	destination.x = x - w / 2;
	destination.y = y - h / 2;
	destination.w = w;
	destination.h = h;
	if (fill)
		SDL_RenderFillRect(Game::Get().Renderer, &destination);
	else
		SDL_RenderDrawRect(Game::Get().Renderer, &destination);
}
