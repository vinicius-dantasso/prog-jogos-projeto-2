
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

class Bullet : public Object
{
private:
	Sprite* sprite;
	float dir;
	float spd;
	float hSpd;
	float vSpd;
	bool shot;

public:
	Bullet();
	~Bullet();

	void Shot(bool canShot);

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

inline void Bullet::Shot(bool canShot)
{ shot = canShot; }

#endif // !_BULLET_H_
