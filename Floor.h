
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "Object.h"
#include "Sprite.h"

enum FloorType {LIMPO, PEDRA};

class Floor : public Object
{
private:
	Sprite* sprite;

public:
	Floor(float posX, float posY, int type);
	~Floor();

	void Update();
	void Draw();
};

inline void Floor::Update(){}
inline void Floor::Draw()
{
	sprite->Draw(x, y, Layer::BACK);
}

#endif // !_FLOOR_H_
