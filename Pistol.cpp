
#include "Pistol.h"
#include "Scripts.h"
#include "DungeonGame.h"

Pistol::Pistol()
{
	tile = new TileSet("Resources/Pistol.png", 32, 32, 2, 2);
	anim = new Animation(tile, 1.0f, false);
	timer = new Timer();

	uint SeqRight[1] = { 0 };
	uint SeqLeft[1] = { 1 };

	anim->Add(PISTOLRIGHT, SeqRight, 1);
	anim->Add(PISTOLLEFT, SeqLeft, 1);
	timer->Start();

	if (DungeonGame::floorNum == 0)
		state = ITEM;
	else
		state = HANDED;
	animState = PISTOLRIGHT;

	ammo = 20;

	MoveTo(window->CenterX() + 225.0f, window->CenterY() - 50.0f);
}

Pistol::~Pistol()
{
	delete tile;
	delete anim;
	delete timer;
}

void Pistol::Update()
{
	switch (state)
	{
	case ITEM:
		Item();
		break;

	case HANDED:
		Handed();
		break;
	}

	anim->Select(animState);
	anim->NextFrame();
}

void Pistol::Draw()
{
	anim->Draw(x, y, Layer::FRONT);
}

void Pistol::Handed()
{
	item = true;

	if (timer->Elapsed() >= 0.5f)
	{
		if (window->KeyPress(VK_LBUTTON) && ammo > 0)
		{
			timer->Reset();
			ammo -= 1;
			DungeonGame::bullet = new Bullet(x, y, BULLETSHOT, BULLET);
			DungeonGame::bullet->Shot(true);
			DungeonGame::sceneMain->Add(DungeonGame::bullet, MOVING);
			DungeonGame::audio->Play(SHOTPLAYER, false);
		}
	}

	if (ammo <= 0 && timer->Elapsed(2.0f))
		ammo = 20;

	float dir = Scripts::point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), window->MouseX(), window->MouseY());
	float xx = Scripts::lengthdir_x(30, dir);
	float yy = Scripts::lengthdir_y(30, dir);

	float hSpd = DungeonGame::player->X() + xx;
	float vSpd = DungeonGame::player->Y() + yy;

	MoveTo(hSpd, vSpd);

	if (dir < 270 && dir > 90)
		animState = PISTOLLEFT;
	else
		animState = PISTOLRIGHT;
}

void Pistol::Item()
{
	item = false;

	if (Scripts::distance_to_object(this, DungeonGame::player) <= 60.0f)
	{
		if (window->KeyPress('F'))
			state = HANDED;
	}
}

void Pistol::Reset()
{
	state = ITEM;
	ammo = 20;
	MoveTo(window->CenterX() + 225.0f, window->CenterY() - 50.0f);
}