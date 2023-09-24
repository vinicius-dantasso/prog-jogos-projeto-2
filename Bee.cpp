
#include "Bee.h"
#include "Scripts.h"
#include "DungeonGame.h"
#include "Bomb.h"

Bee::Bee(float posX, float posY)
{
	tile = new TileSet("Resources/Bee.png", 32, 32, 4, 8);
	anim = new Animation(tile, 0.15f, true);
	timer = new Timer();

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	uint SeqLeft[2] = { 4,5 };
	uint SeqRight[2] = { 0,1 };
	uint SeqHitR[2] = { 2,3 };
	uint SeqHitL[2] = { 6,7 };

	anim->Add(BEELEFT, SeqLeft, 2);
	anim->Add(BEERIGHT, SeqRight, 2);
	anim->Add(BEEHITR, SeqHitR, 2);
	anim->Add(BEEHITL, SeqHitL, 2);

	spd = 80.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	type = ENEMY;
	state = CHOOSESTATE;
	animState = BEERIGHT;

	timer->Start();
	time = 1.0f;

	frames = 0;
	maxFrames = 10;

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(posX, posY);
}

Bee::~Bee()
{
	delete tile;
	delete anim;
	delete timer;
	delete font;
}

void Bee::OnCollision(Object* obj)
{
	if (obj->Type() == HWALL)
	{
		if (x + 8 >= obj->X() - 16 && x - 8 <= obj->X() - 16)
			MoveTo(obj->X() - 32, y);
		else if (x - 8 <= obj->X() + 16 && x + 8 >= obj->X() - 16)
			MoveTo(obj->X() + 32, y);
	}

	if (obj->Type() == VWALL)
	{
		if (y - 8 <= obj->Y() + 16 && y + 8 >= obj->Y() + 16)
			MoveTo(x, obj->Y() + 32);
		else if (y + 8 >= obj->Y() - 16 && y - 8 <= obj->Y() - 16)
			MoveTo(x, obj->Y() - 32);
	}

	if (obj->Type() == BULLET || obj->Type() == BOMB)
	{
		hit = true;
		life -= 1;
		float dir = Scripts::point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), obj->X(), obj->Y());
		knockBackDir = dir;
		knockBackSpd = 200.0f;
		state = ENEMYHIT;
		
		if (animState == BEELEFT)
			animState = BEEHITL;
		else if (animState == BEERIGHT)
			animState = BEEHITR;

		if(obj->Type() != BOMB)
			DungeonGame::sceneMain->Delete(obj, MOVING);
	}
}

void Bee::Update()
{
	if (timer->Elapsed(time))
	{
		time = TimerRange();
		timer->Reset();
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}

	if (!hit && Scripts::distance_to_object(this, DungeonGame::player) <= 150.0f)
		state = ATTACKING;

	if (!hit && DungeonGame::player->X() > x)
		animState = BEELEFT;
	else if (!hit && DungeonGame::player->X() < x)
		animState = BEERIGHT;

	switch (state)
	{
	case CHOOSESTATE:
		ChooseState();
		break;

	case WANDERING:
		Wandering();
		break;

	case STOPPED:
		hSpd = 0.0f;
		vSpd = 0.0f;
		break;

	case ATTACKING:
		Attacking();
		break;

	case ENEMYHIT:
		Hit();
		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(animState);
	anim->NextFrame();

	if (life <= 0)
	{
		DungeonGame::sceneMain->Delete(this, MOVING);
		DungeonGame::enemiesTotal--;
	}
}

void Bee::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);
	anim->Draw(x, y, Layer::UPPER);
}

void Bee::Hit()
{
	knockBackSpd = Scripts::lerp(knockBackSpd, 0.0f, 0.3f);

	hSpd = Scripts::lengthdir_x(knockBackSpd, knockBackDir);
	vSpd = Scripts::lengthdir_y(knockBackSpd, knockBackDir);

	frames++;
	if (frames >= maxFrames)
	{
		frames = 0;
		state = CHOOSESTATE;
		hit = false;
	}
}