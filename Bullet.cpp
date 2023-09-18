
#include "Bullet.h"
#include "DungeonGame.h"
#include "DebugLevel.h"
#include "Scripts.h"

Bullet::Bullet()
{
	sprite = new Sprite("Resources/Bullet.png");

	spd = 300.0f;

	BBox(new Rect(-4, -4, 4, 4));
	MoveTo(DungeonGame::pistol->X(), DungeonGame::pistol->Y());
}

Bullet::~Bullet()
{
	delete sprite;
}

void Bullet::OnCollision(Object* obj)
{
	if (obj->Type() == WALL)
		DebugLevel::scene->Delete(this, MOVING);
}

void Bullet::Update()
{
	if (shot)
	{
		shot = false;
		
		dir = Scripts::point_direction(x, y, window->MouseX(), window->MouseY());
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
	}
	
	Translate(hSpd * gameTime, vSpd * gameTime);
}

void Bullet::Draw()
{
	sprite->Draw(x, y, Layer::FRONT);
}