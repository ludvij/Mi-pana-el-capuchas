#include "HUD.h"

HUD::HUD()
	: frame("rcs/frame.png",
		16 * Game::Get().CellSizeX - Game::Get().CellSizeX / 2,
		Game::Get().CellSizeY - Game::Get().CellSizeY / 2,
		Game::Get().CellSizeX,
		Game::Get().CellSizeY
	)
{
	for (int i = 0; i < 5; i++) {
		hearts.push_back(new Entity("rcs/heart.png", 
			Game::Get().Width * 0.02f + i * Game::Get().CellSizeX / 2, 
			Game::Get().Height * 0.02f,
			Game::Get().CellSizeX,
			Game::Get().CellSizeY
		));
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
		delete hearts[i];
		if (i < idx) {
			hearts[i] = new Entity("rcs/heart.png",
				Game::Get().Width * 0.02f + i * Game::Get().CellSizeX / 2,
				Game::Get().Height * 0.02f,
				Game::Get().CellSizeX,
				Game::Get().CellSizeY
			);
		}
		if (i == idx && player->Health % 2 == 1) {
			hearts[i] = new Entity("rcs/half_heart.png",
				Game::Get().Width * 0.02f + i * Game::Get().CellSizeX / 2,
				Game::Get().Height * 0.02f,
				Game::Get().CellSizeX,
				Game::Get().CellSizeY
			);
		}
		else if (i >= idx) {
			hearts[i] = new Entity("rcs/empty_heart.png",
				Game::Get().Width * 0.02f + i * Game::Get().CellSizeX / 2,
				Game::Get().Height * 0.02f,
				Game::Get().CellSizeX,
				Game::Get().CellSizeY
			);
		}
		
	}
	
}

void HUD::UpdateFrame(Player* player)
{
	currWeapon = player->Weapon;
}
