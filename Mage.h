
#ifndef _MAGE_H_
#define _MAGE_H_

#include "Enemy.h"

enum MageAnim
{
	MAGEIDLEL,
	MAGEIDLER,
	MAGEMOVEL,
	MAGEMOVER,
	MAGEATTL,
	MAGEATTR,
	MAGEHITL,
	MAGEHITR
};

class Mage : public Enemy
{
private:
	int frames;
	int maxFrames;
	int castCharge;
	int cast;
	float time;

public:
	uint animState;

	Mage(float posX, float posY);
	~Mage();

	void Hit();
	void Attacking();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_MAGE_H_

