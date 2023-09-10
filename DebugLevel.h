
#ifndef _DEBUGLEVEL_H_
#define _DEBUGLEVEL_H_

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Gun.h"

class DebugLevel : public Game
{
private:

public:
	static Scene* scene;
	Gun* gun = nullptr;
	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_DEBUGLEVEL_H_
