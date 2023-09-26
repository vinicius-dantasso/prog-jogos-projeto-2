
#ifndef _BOMB_H_
#define _BOMB_H_

#include "Object.h"
#include "Animation.h"
#include "Types.h"
#include "Timer.h"

enum BombState{ BOMBITEM, DROPPED, EXPLOSION, BOMBDELAY };

class Bomb : public Object
{
private:
	TileSet* tile;
	Animation* anim;
	Timer* timer;

	float spd;
	float hSpd;
	float vSpd;

public:
	uint state;
	float dir;

	Bomb(float posX, float posY, int initialState);
	~Bomb();

	void Item();
	void Dropped(float dir);
	void Explosion();
	void Delay();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_BOMB_H_
