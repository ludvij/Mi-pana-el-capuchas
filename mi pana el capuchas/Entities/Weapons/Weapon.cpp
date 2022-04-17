#include "Weapon.h"

Weapon::Weapon(uint32_t sprite_x, uint32_t sprite_y, int x, int y, int width, int height)
	: Entity(sprite_x, sprite_y, x, y, width, height)
{
}

void Weapon::Update()
{
	if (!Ready) shotTime--;
	if (shotTime <= 0) {
		Ready = true;
		shotTime = cadence;
	}
}

void Weapon::Draw(float scrollX)
{
	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = std::round(x - width / 2.0f);
	destination.y = std::round(y - height / 2.0f);
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::Get().Renderer, Game::Get().Sheet, &m_renderRect, &destination, Angle, nullptr, SDL_FLIP_NONE);
#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));
#endif
}

void Weapon::Draw(float x, float y)
{

	// tamaño de la entidad
	SDL_Rect destination;
	destination.x = std::round(x - width / 2);
	destination.y = std::round(y - height / 2);
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::Get().Renderer, Game::Get().Sheet, &m_renderRect, &destination, 0, nullptr, SDL_FLIP_NONE);
}
