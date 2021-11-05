#include "Layers/DebugLayer.h"
#include <iostream>
#include <ranges>

DebugLayer::DebugLayer()
{
	Init();
}

DebugLayer::~DebugLayer()
{
	delete qt;

	for (const auto& e : ents)
		delete e;
	ents.clear();
}

void DebugLayer::Init()
{

	qt = new QuadTree<Entity>(0, 0, Game::Get().Width, Game::Get().Height, QuadInsertMode::REGION_CENTER);
}

void DebugLayer::Draw()
{
	SDL_SetRenderDrawColor(Game::Get().Renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(Game::Get().Renderer);

	SDL_SetRenderDrawColor(Game::Get().Renderer, 0xFF, 0x00, 0x00, 0xFF);
	for (const auto& e : ents) e->DrawOutline(true);

	SDL_SetRenderDrawColor(Game::Get().Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	DrawQT(qt);

	SDL_SetRenderDrawColor(Game::Get().Renderer, 0x00, 0xFF, 0x00, 0xFF);
	for (const auto& e : qEnts) e->DrawOutline(true);
	SDL_RenderDrawRect(Game::Get().Renderer, &r);

	SDL_RenderPresent(Game::Get().Renderer);
}

void DebugLayer::Update()
{
	delete qt;

	qt = new QuadTree<Entity>(0, 0, Game::Get().Width, Game::Get().Height, QuadInsertMode::REGION_CENTER);

	for (const auto& e : ents) qt->Insert(e);
}

void DebugLayer::ProcessControls()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			Game::Get().Stop();
		if (event.type == SDL_KEYDOWN) {
			int code = event.key.keysym.sym;
			switch (code)
			{
			case SDLK_ESCAPE:
				Game::Get().Stop();
				break;
			case SDLK_SPACE:
				qEnts = qt->Query(r.x, r.y, r.w, r.h);
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int code = event.button.button;
			switch(code) {
			case SDL_BUTTON_LEFT:
				int x = event.button.x;
				int y = event.button.y;
				ents.push_back(new Entity(x, y, 10,10));
				break;
			}
		}
	}
}


void DrawQT(QuadTree<Entity>* qt)
{

	SDL_Rect quad = { 
		qt->m_x,
		qt->m_y,
		qt->m_w,
		qt->m_h 
	};
	
	SDL_RenderDrawRect(Game::Get().Renderer, &quad);
	if (qt->m_divided) {
		DrawQT(qt->m_TopLeft );
		DrawQT(qt->m_TopRight);
		DrawQT(qt->m_BotLeft );
		DrawQT(qt->m_BotRight);
	}
}