
#include "BugHole.h"
#include "DungeonGame.h"
#include "Scripts.h"

BugHole::BugHole(float posX, float posY)
{
	tile = new TileSet("Resources/Bug_Hole.png", 32, 32, 3, 3);
	anim = new Animation(tile, 0.12f, true);

	timer = new Timer();

	uint SeqChase[2] = { 0,1 };
	uint SeqBeneath[1] = { 2 };

	anim->Add(CLOSED, SeqChase, 2);
	anim->Add(OPENNED, SeqBeneath, 1);

	spd = 50.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	state = CHASING;
	animState = CLOSED;

	type = BUGHOLE;
	timer->Start();

	MoveTo(posX, posY);
	BBox(new Rect(-4, -4, 4, 4));
}

BugHole::~BugHole()
{
	delete tile;
	delete anim;
	delete timer;
}

void BugHole::OnCollision(Object* obj)
{
	if (obj->Type() == PLAYER && state != BENEATHPLAYER)
	{
		state = BENEATHPLAYER;
		timer->Reset();
	}
}

void BugHole::Update()
{
	destX = DungeonGame::player->X();
	destY = DungeonGame::player->Y();

	switch (state)
	{
	case CHASING:
		ChasingPlayer();
		break;

	case BENEATHPLAYER:
		BeneathPlayer();
		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(animState);
	anim->NextFrame();
}

void BugHole::Draw()
{
	anim->Draw(x, y, Layer::LOWER);
}

void BugHole::ChasingPlayer()
{
	DungeonGame::audio->Play(BUGCHASE, true);

	float dir = Scripts::point_direction(x, y, destX, destY);
	hSpd = Scripts::lengthdir_x(spd, dir);
	vSpd = Scripts::lengthdir_y(spd, dir);
}

void BugHole::BeneathPlayer()
{

	DungeonGame::audio->Stop(BUGCHASE);

	hSpd = 0.0f;
	vSpd = 0.0f;

	if (timer->Elapsed(1.0f))
	{
		animState = OPENNED;
	}

	if (timer->Elapsed(5.0f))
	{
		animState = CLOSED;
		state = CHASING;
	}
}