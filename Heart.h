
#ifndef _HEART_H_
#define _HEART_H_

#include "Object.h"
#include "Sprite.h"

class Heart : public Object
{
private:
	Sprite* sprite;
	
	int quant;

public:
	Heart(float posX, float posY);
	~Heart();

	void Update();
	void Draw();
};

#endif // !_HEART_H_
