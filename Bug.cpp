
#include "Bug.h"
#include "Scripts.h"
#include "DungeonGame.h"
#include "Enemy.h"

Bug::Bug(float posX, float posY)
{
	tile = new TileSet("Resources/Bug.png", 64, 64, 2, 4);
	anim = new Animation(tile, 0.12f, true);
	timer = new Timer();

	uint SeqRise[2] = { 0,1 };
	uint SeqHit[2] = { 2,3 };

	anim->Add(RISING, SeqRise, 2);
	anim->Add(BUGHIT, SeqHit, 2);

	spd = 50.0f;
	grav = 5.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	state = INSIDE;
	animState = RISING;

	frames = 0;
	maxFrames = 10;

	type = -1;
	life = 3;

	canJump = false;
	timer->Start();

	BBox(new Rect(-4, -4, 4, 4));
	MoveTo(posX, posY);
}

Bug::~Bug()
{
	delete tile;
	delete anim;
}

void Bug::OnCollision(Object* obj)
{
	if (obj->Type() == PLAYER && state == INSIDE)
	{
		canJump = true;
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = JUMPING;
		timer->Reset();
		BBox(new Rect(-16, -16, 16, 16));
	}

	if (obj->Type() == BUGHOLE && state == JUMPING && !canJump)
	{
		if (timer->Elapsed(4.0f))
		{
			hSpd = 0.0f;
			vSpd = 0.0f;
			timer->Reset();
			state = DELAY;
			BBox(new Rect(-4, -4, 4, 4));
		}
	}

	if (obj->Type() == BUGHOLE && life <= 0)
	{
		Enemy::CoinDrop(this);
		DungeonGame::sceneMain->Delete(this, MOVING);
		DungeonGame::sceneMain->Delete(obj, MOVING);
		DungeonGame::enemiesTotal--;
	}

	if ((obj->Type() == BULLET || obj->Type() == BOMB) && state != INSIDE)
	{
		DungeonGame::audio->Play(HITENEMY);
		life -= 1;
		animState = BUGHIT;

		if(obj->Type() != BOMB)
			DungeonGame::sceneMain->Delete(obj, MOVING);
	}
}

void Bug::Update()
{
	switch (state)
	{
	case INSIDE:
		Inside();
		break;

	case JUMPING:
		Jumping();
		break;

	case DELAY:
		Delay();
		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	if (animState == BUGHIT)
	{
		frames++;
		if (frames >= maxFrames)
		{
			frames = 0;
			animState = RISING;
		}
	}

	anim->Select(animState);
	anim->NextFrame();
}

void Bug::Draw()
{
	if (state == JUMPING && timer->Elapsed(2.0f) && life > 0)
		anim->Draw(x, y, Layer::LOWER);
}

void Bug::Inside()
{
	type = -1;
	float dir = Scripts::point_direction(x, y, DungeonGame::player->X(), DungeonGame::player->Y());
	hSpd = Scripts::lengthdir_x(spd, dir);
	vSpd = Scripts::lengthdir_y(spd, dir);
}

void Bug::Jumping()
{
	if(!canJump)
		vSpd += grav;

	if (canJump && timer->Elapsed(2.0f))
	{
		if(life > 0 && state == JUMPING)
			type = ENEMY;

		vSpd = 0.0f;
		vSpd -= 300.0f;
		canJump = false;
	}
}

void Bug::Delay()
{
	if (timer->Elapsed(1.0f))
		state = INSIDE;
}