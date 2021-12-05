#include "Projectile.h"
#include "Player.h"
#include "Layers/GameLayer.h"

Projectile::Projectile(std::string_view filename, int x, int y, int width, int height, float angle, int pierce, Vector2D velocity, int dmg)
	: Entity(filename, x, y, width, height),
	Pierce(pierce),
	Angle(angle),
	Dmg(dmg)
{
	Vec = velocity;
}

void Projectile::Draw(float scrollX)
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

void Projectile::Update()
{
	if (Pierce == 0)
		Deleted = true;
	if (Vec.x == 0 && Vec.y == 0)
		Deleted = true;
}

bool Projectile::IsOverlap(Entity* entity)
{
	// they are in bounds
	if (Entity::IsOverlap(entity)) {
		// entity can be pierced
		if (entity->Pierceable) {
			// check if it has been already pierced
			bool inside = false;
			for (auto const e : m_pierced) {
				if (*e == *entity) {
					inside = true;
				}
			}
			// has been pierced
			if (!inside) {
				// can only damage the player
				if (HarmPlayer) {
					// is the player
					if (*entity == *((GameLayer*)Game::Get().layer)->player) {
						Pierce--;
						m_pierced.push_back(entity);
					}
				}
				else {
					if (*entity == *((GameLayer*)Game::Get().layer)->player) 
						return false;	
					Pierce--;
					m_pierced.push_back(entity);
				}

				return true;
			}
		}
		else {
			Pierce = 0;
		}
	}
	return false;
}
