#include "Animation.h"

Animation::Animation(uint32_t sprite_x, uint32_t sprite_y, int actorWidth, int actorHeight, int updateFrequence, int totalFrames, bool loop)
	: m_entityWidth(actorWidth), m_entityHeight(actorHeight),
	UpdateFrequence(updateFrequence),
	TotalFrames(totalFrames),
	Loop(loop)
{
	UpdateTime = 0;
	CurrentFrame = 0;
	// start x of the animation
	m_startX = sprite_x * SPRITE_SIZE_X;
	// render rect of the animation
	m_renderRect.x = m_startX;
	m_renderRect.y = SPRITE_SIZE_Y * sprite_y;
	m_renderRect.w = SPRITE_SIZE_X;
	m_renderRect.h = SPRITE_SIZE_Y;
}

bool Animation::Update() {
	UpdateTime++;
	if (UpdateTime > UpdateFrequence) {
		UpdateTime = 0;
		// Actualizar el frame
		CurrentFrame++;
		// Si lleva al ultimo frame vuelve al primero
		if (CurrentFrame >= TotalFrames) {
			// Reiniciar es infinita
			if (Loop == false) {
				// No es infinita
				// Indicar que finalizó
				return true;
			}
			else {
				CurrentFrame = 0;
			}
		}
	}
	//Actualizar el rectangulo del source (siguiente frame)
	m_renderRect.x = m_startX + CurrentFrame * SPRITE_SIZE_X;
	return false; // luego lo cambiamos
}

void Animation::Draw(float x, float y) {
	SDL_Rect destination;
	destination.x = x - m_entityWidth / 2;
	destination.y = y - m_entityHeight / 2;
	destination.w = m_entityWidth;
	destination.h = m_entityHeight;
	// Modificar para que la referencia sea el punto central
	SDL_RenderCopyEx(Game::Get().Renderer, Game::Get().Sheet, &m_renderRect, &destination, 0, nullptr, SDL_FLIP_NONE);

#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));
#endif // OUTLINE
}
