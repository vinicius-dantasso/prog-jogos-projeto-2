
#include "Bomb.h"
#include "DungeonGame.h"
#include "Scripts.h"

Bomb::Bomb(float posX, float posY, int initialState)
{
	tile = new TileSet("Resources/Explosion.png", 100, 100, 10, 72);
	anim = new Animation(tile, 0.02f, false);
	timer = new Timer();

	uint SeqDrop[1] = { 71 };
	uint SeqExplosion[71] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,
		42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
		64,65,66,67,68,69,70 };

	anim->Add(DROPPED, SeqDrop, 1);
	anim->Add(EXPLOSION, SeqExplosion, 71);
	anim->Add(BOMBITEM, SeqDrop, 1);

	spd = 200.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	type = -1;
	state = initialState;

	if (state == DROPPED)
		timer->Start();

	MoveTo(posX, posY);
	BBox(new Circle(50));
}

Bomb::~Bomb()
{
	delete tile;
	delete anim;
	delete timer;
}

void Bomb::OnCollision(Object* obj)
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
}

void Bomb::Update()
{
	switch (state)
	{
	case BOMBITEM:
		Item();
		break;

	case BOMBDELAY:
		type = BOMB;
		Delay();
		break;

	case DROPPED:
		Dropped(dir);
		break;

	case EXPLOSION:
		Explosion();
		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(state);
	anim->NextFrame();
}

void Bomb::Draw()
{
	anim->Draw(x, y, Layer::FRONT);
}

void Bomb::Dropped(float dir)
{
	hSpd = Scripts::lengthdir_x(spd, dir);
	vSpd = Scripts::lengthdir_y(spd, dir);

	if (timer->Elapsed(1.0f))
	{
		timer->Reset();
		state = BOMBDELAY;
	}
}

void Bomb::Delay()
{
	hSpd = 0.0f;
	vSpd = 0.0f;

	if (timer->Elapsed(2.0f))
		state = EXPLOSION;
}

void Bomb::Explosion()
{
	if (anim->Inactive())
		DungeonGame::sceneMain->Delete(this, MOVING);
}

void Bomb::Item()
{}