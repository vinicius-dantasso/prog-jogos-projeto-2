
#include "Pistol.h"
#include "Scripts.h"
#include "DungeonGame.h"
#include "DebugLevel.h"

Pistol::Pistol()
{
	sprite = new Sprite("Resources/Pistol.png");
	MoveTo(DungeonGame::player->X() + 32, DungeonGame::player->Y());
}

Pistol::~Pistol()
{
	delete sprite;
}

void Pistol::Update()
{
	if (window->KeyPress(VK_LBUTTON))
	{
		DungeonGame::bullet = new Bullet();
		DungeonGame::bullet->Shot(true);
		DebugLevel::scene->Add(DungeonGame::bullet, MOVING);
	}

	float dir = Scripts::point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), window->MouseX(), window->MouseY());
	float xx = Scripts::lengthdir_x(40, dir);
	float yy = Scripts::lengthdir_y(40, dir);

	float hSpd = DungeonGame::player->X() + xx;
	float vSpd = DungeonGame::player->Y() + yy;

	MoveTo(hSpd, vSpd);
}

void Pistol::Draw()
{
	sprite->Draw(x, y, Layer::FRONT);
}