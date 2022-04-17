#include "HUD.h"

HUD::HUD()
	: frame(FRAME_POS,
		16 * Game::Get().CellSizeX - Game::Get().CellSizeX / 2,
		Game::Get().CellSizeY - Game::Get().CellSizeY / 2,
		Game::Get().CellSizeX,
		Game::Get().CellSizeY
	)
{
	for (int i = 0; i < 5; i++) {
		hearts.push_back(new Entity(HEART_POS, 
			Game::Get().Width * 0.02f + i * Game::Get().CellSizeX / 2, 
			Game::Get().Height * 0.02f,
			Game::Get().CellSizeX,
			Game::Get().CellSizeY)
		);
	}
}

HUD::~HUD()
{
	while (!hearts.empty()) delete hearts.back(), hearts.pop_back();
}

void HUD::Draw()
{
	for (const auto& h : hearts) h->Draw(); 
	frame.Draw();
	if (currWeapon != nullptr)
		currWeapon->Draw(frame.x + frame.width / 2 * 0.85f, frame.y);
}

void HUD::UpdateHearts(Player* player)
{
	int idx = player->Health / 2;
	if (idx <= 0) idx = 0;
	for (int i = 0; i < 5; i++) {
		if (i < idx) {
			hearts[i]->ChangeRenderRect(HEART_POS);
		}
		if (i == idx && player->Health % 2 == 1) {
			hearts[i]->ChangeRenderRect(HALF_HEART_POS);
		}
		else if (i >= idx) {
			hearts[i]->ChangeRenderRect(EMPTY_HEART_POS);
		}
	}
}

void HUD::UpdateFrame(Player* player)
{
	currWeapon = player->Weapon;
}
