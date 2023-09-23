
#ifndef _BEE_H_
#define _BEE_H_

#include "Enemy.h"

enum BeeAnim {BEELEFT, BEERIGHT, BEEHITL, BEEHITR};

class Bee : public Enemy
{
private:
	float		  time;
	int			  frames;
	int			  maxFrames;

public:
	uint animState;

	Bee(float posX, float posY);
	~Bee();

	void Hit();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_BEE_H_
