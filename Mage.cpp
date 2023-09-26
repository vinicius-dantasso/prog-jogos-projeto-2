
#include "Mage.h"
#include "DungeonGame.h"

Mage::Mage(float posX, float posY)
{
	tile = new TileSet("Resources/Mage.png", 64, 64, 4, 14);
	anim = new Animation(tile, 0.12f, true);
	timer = new Timer();

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	uint SeqIdleL[1] = { 8 };
	uint SeqIdleR[1] = { 9 };
	uint SeqMoveL[4] = { 4,5,6,7 };
	uint SeqMoveR[4] = { 0,1,2,3 };
	uint SeqAttL[1] = { 10 };
	uint SeqAttR[1] = { 11 };
	uint SeqHitL[1] = { 12 };
	uint SeqHitR[1] = { 13 };

	anim->Add(MAGEIDLEL, SeqIdleL, 1);
	anim->Add(MAGEIDLER, SeqIdleR, 1);
	anim->Add(MAGEMOVEL, SeqMoveL, 4);
	anim->Add(MAGEMOVER, SeqMoveR, 4);
	anim->Add(MAGEATTL, SeqAttL, 1);
	anim->Add(MAGEATTR, SeqAttR, 1);
	anim->Add(MAGEHITL, SeqHitL, 1);
	anim->Add(MAGEHITR, SeqHitR, 1);

	spd = 120.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	life = 5;

	type = ENEMY;
	state = CHOOSESTATE;
	animState = MAGEIDLEL;

	timer->Start();
	time = 1.0f;

	frames = 0;
	maxFrames = 5;

	castCharge = 0;
	cast = 60;

	BBox(new Rect(-16, -16, 16, 16));
	MoveTo(posX, posY);
}

Mage::~Mage()
{
	delete tile;
	delete anim;
	delete timer;
	delete font;
}

void Mage::OnCollision(Object* obj)
{
	if (obj->Type() == HWALL)
	{
		if (x + 16 >= obj->X() - 16 && x - 16 <= obj->X() - 16)
			MoveTo(obj->X() - 32, y);
		else if (x - 16 <= obj->X() + 16 && x + 16 >= obj->X() - 16)
			MoveTo(obj->X() + 32, y);
	}

	if (obj->Type() == VWALL)
	{
		if (y - 16 <= obj->Y() + 16 && y + 16 >= obj->Y() + 16)
			MoveTo(x, obj->Y() + 32);
		else if (y + 16 >= obj->Y() - 16 && y - 16 <= obj->Y() - 16)
			MoveTo(x, obj->Y() - 32);
	}

	if (obj->Type() == WALL)
		WallCollision(obj);

	if (obj->Type() == BULLET || obj->Type() == BOMB)
	{
		hit = true;
		life -= 1;
		float dir = Scripts::point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), obj->X(), obj->Y());
		knockBackDir = dir;
		knockBackSpd = 200.0f;
		state = ENEMYHIT;

		if (animState == MAGEMOVEL || animState == MAGEIDLEL || animState == MAGEATTL)
			animState = MAGEHITL;
		else if (animState == MAGEMOVER || animState == MAGEIDLER || animState == MAGEATTR)
			animState = MAGEHITR;

		if(obj->Type() != BOMB)
			DungeonGame::sceneMain->Delete(obj, MOVING);
	}
}

void Mage::Update()
{
	if (timer->Elapsed(time))
	{
		time = TimerRange();
		timer->Reset();
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}

	if (!hit && Scripts::distance_to_object(this, DungeonGame::player) <= 500.0f)
		state = ATTACKING;

	if (state == ATTACKING && !hit)
	{
		if (destX < x)
			animState = MAGEATTL;
		else
			animState = MAGEATTR;
	}

	if (!hit && state != ATTACKING && destX < x)
	{
		if (state == WANDERING)
			animState = MAGEMOVEL;
		else if (state == STOPPED)
			animState = MAGEIDLEL;
	}
	else if (!hit && state != ATTACKING && destX > x)
	{
		if (state == WANDERING)
			animState = MAGEMOVER;
		else if (state == STOPPED)
			animState = MAGEIDLER;
	}

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
		Enemy::CoinDrop(this);
		DungeonGame::sceneMain->Delete(this, MOVING);
		DungeonGame::enemiesTotal--;
	}
}

void Mage::Draw()
{
	anim->Draw(x, y, Layer::UPPER);
}

void Mage::Hit()
{
	knockBackSpd = Scripts::lerp(knockBackSpd, 0.0f, 0.3f);

	hSpd = Scripts::lengthdir_x(knockBackSpd, knockBackDir);
	vSpd = Scripts::lengthdir_y(knockBackSpd, knockBackDir);

	frames++;
	if (frames >= maxFrames)
	{
		hSpd = 0.0f;
		vSpd = 0.0f;
		frames = 0;
		state = CHOOSESTATE;
		hit = false;
	}
}

void Mage::Attacking()
{
	castCharge++;
	if (castCharge >= cast)
	{
		castCharge = 0;
		DungeonGame::bullet = new Bullet(x, y, MAGICSHOT, MAGIC);
		DungeonGame::bullet->Shot(true);
		DungeonGame::sceneMain->Add(DungeonGame::bullet, MOVING);
	}

	if (Scripts::distance_to_object(this, DungeonGame::player) >= 500.0f)
	{
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}
}