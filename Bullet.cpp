
#include "Bullet.h"
#include "DungeonGame.h"
#include "Scripts.h"

Bullet::Bullet(float posX, float posY, int spriteType, int types)
{
	switch (spriteType)
	{
	case BULLETSHOT: sprite = new Sprite("Resources/Bullet.png"); break;
	case MAGICSHOT: sprite = new Sprite("Resources/Magic.png"); break;
	}

	spd = 500.0f;
	type = types;

	BBox(new Rect(-4, -4, 4, 4));
	MoveTo(posX, posY);
}

Bullet::~Bullet()
{
	delete sprite;
}

void Bullet::OnCollision(Object* obj)
{
	if (obj->Type() == HWALL || obj->Type() == VWALL || obj->Type() == WALL)
		DungeonGame::scene->Delete(this, MOVING);

	if(type == MAGIC && obj->Type() == PLAYER)
		DungeonGame::scene->Delete(this, MOVING);
}

void Bullet::Update()
{
	if (shot && type == BULLET)
	{
		shot = false;
		
		dir = Scripts::point_direction(x, y, window->MouseX(), window->MouseY());
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
	}
	else if (shot && type == MAGIC)
	{
		shot = false;
		float destX = DungeonGame::player->X();
		float destY = DungeonGame::player->Y();

		dir = Scripts::point_direction(x, y, destX, destY);
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
	}
	
	Translate(hSpd * gameTime, vSpd * gameTime);
}

void Bullet::Draw()
{
	sprite->Draw(x, y, Layer::FRONT, 1.0f, dir);
}