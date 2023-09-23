
#include "Trap.h"
#include "DungeonGame.h"

Trap::Trap(float posX, float posY)
{
	tile = new TileSet("Resources/Trap2.png", 64, 64, 3, 3);
	anim = new Animation(tile, 2.5f, false);

	frames = 31;
	maxFrames = 60;

	uint SeqIdle[1] = { 0 };
	uint SeqAttack[2] = { 1,2 };

	anim->Add(DEACTIVATED, SeqIdle, 1);
	anim->Add(ACTIVATED, SeqAttack, 2);

	type = TRAP;
	state = DEACTIVATED;

	canActivate = false;

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(posX, posY);
}

Trap::~Trap()
{
	delete tile;
	delete anim;
}

void Trap::OnCollision(Object * obj)
{
	if (obj->Type() == PLAYER && !canActivate)
	{
		frames = 0;
		canActivate = true;
	}
}

void Trap::Update()
{
	if (frames == 20)
	{
		type = ENEMY;
		state = ACTIVATED;
		canActivate = false;
	}
	else if (frames >= 60 && state == ACTIVATED)
	{
		type = TRAP;
		state = DEACTIVATED;
	}

	frames++;

	anim->Select(state);
	anim->NextFrame();
}