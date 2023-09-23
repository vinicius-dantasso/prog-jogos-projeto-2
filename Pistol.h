
#ifndef _PISTOL_H_
#define _PISTOL_H_

#include "Object.h"
#include "Animation.h"
#include "Timer.h"

enum PistolAnim {PISTOLLEFT,PISTOLRIGHT};
enum PistolState {ITEM, HANDED};

class Pistol : public Object
{
private:
	TileSet		* tile;
	Animation	* anim;
	Timer		* timer;

public:
	uint animState;
	uint state;
	int ammo;
	bool item;

	Pistol();
	~Pistol();

	void Handed();
	void Item();

	void Update();
	void Draw();
};

#endif // !_PISTOL_H_
