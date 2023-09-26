
#ifndef _COIN_H_
#define _COIN_H_

#include "Types.h"
#include "Object.h"
#include "Animation.h"

enum CoinState {COINITEM};

class Coin : public Object
{
private:
	TileSet* tile;
	Animation* anim;

	float spd;
	float hSpd;
	float vSpd;

public:
	uint state;

	Coin(float posX, float posY);
	~Coin();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_COIN_H_
