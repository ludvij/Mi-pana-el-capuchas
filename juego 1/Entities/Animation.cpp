#include "Animation.h"

Animation::Animation(std::string_view filename, int actorWidth, int actorHeight, int updateFrequence, int totalFrames, bool loop)
	: m_entityWidth(actorWidth), m_entityHeight(actorHeight),
	UpdateFrequence(updateFrequence),
	TotalFrames(totalFrames),
	Loop(loop)
{
	m_texture = Game::Get().GetTexture(filename);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_fileWidth, &m_fileHeight);
	UpdateTime = 0;
	CurrentFrame = 0;
	m_frameWidth = static_cast<float>(m_fileWidth) / static_cast<float>(TotalFrames);
	m_frameHeight = m_fileHeight;
	m_source = {
		.x = 0,
		.y = 0,
		.w = m_frameWidth,
		.h = m_frameHeight
	};
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
			   // Indicar que finaliz� 
				return true;
			}
			else {
				CurrentFrame = 0;
			}
		}
	}
	//Actualizar el rectangulo del source (siguiente frame)
	m_source.x = CurrentFrame * m_frameWidth;
	return false; // luego lo cambiamos
}

void Animation::Draw(float x, float y) {
	SDL_Rect destination;
	destination.x = x - m_entityWidth / 2;
	destination.y = y - m_entityHeight / 2;
	destination.w = m_entityWidth;
	destination.h = m_entityHeight;
	// Modificar para que la referencia sea el punto central
	SDL_RenderCopyEx(Game::Get().Renderer,
		m_texture, &m_source, &destination, 0, NULL, SDL_FLIP_NONE);

#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));

#endif // OUTLINE
}
