
#include "Pistol.h"
#include "Scripts.h"
#include "DungeonGame.h"
#include "DebugLevel.h"

Pistol::Pistol()
{
	sprite = new Sprite("Resources/Pistol.png");
	timer = new Timer();

	timer->Start();

	MoveTo(DungeonGame::player->X() + 32, DungeonGame::player->Y());
}

Pistol::~Pistol()
{
	delete sprite;
	delete timer;
}

void Pistol::Update()
{
	if (timer->Elapsed() >= 0.3f)
	{
		if (window->KeyPress(VK_LBUTTON))
		{
			timer->Reset();
			DungeonGame::bullet = new Bullet();
			DungeonGame::bullet->Shot(true);
			DebugLevel::scene->Add(DungeonGame::bullet, MOVING);
		}
	}

	float dir = Scripts::point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), window->MouseX(), window->MouseY());
	float xx = Scripts::lengthdir_x(20, dir);
	float yy = Scripts::lengthdir_y(20, dir);

	float hSpd = DungeonGame::player->X() + xx;
	float vSpd = DungeonGame::player->Y() + yy;

	MoveTo(hSpd, vSpd);
}

void Pistol::Draw()
{
	sprite->Draw(x, y, Layer::FRONT);
}