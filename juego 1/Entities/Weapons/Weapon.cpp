#include "Weapon.h"

Weapon::Weapon(std::string_view filename, int x, int y, int width, int height)
	: Entity(filename, x, y, width, height)
{
}

void Weapon::Draw(float scrollX)
{
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = m_texSize.x;
	source.h = m_texSize.y;
	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = std::round(x - width / 2);
	destination.y = std::round(y - height / 2);
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &source, &destination, Angle, nullptr, SDL_FLIP_NONE);
#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));
#endif
}
