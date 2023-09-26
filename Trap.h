
#ifndef _TRAP_H_
#define _TRAP_H_

#include "Types.h"
#include "Object.h"
#include "Animation.h"

enum TrapState {DEACTIVATED, ACTIVATED};

class Trap : public Object
{
private:
	TileSet   * tile;
	Animation * anim;
	int			frames;
	int			maxFrames;
	bool		canActivate;

public:
	uint state;

	Trap(float posX, float posY);
	~Trap();

	void OnCollision(Object * obj);
	void Update();
	void Draw();
};

inline void Trap::Draw()
{ anim->Draw(x,y, Layer::LOWER); }

#endif // !_TRAP_H_
