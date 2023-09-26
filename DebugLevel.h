
#ifndef _DEBUGLEVEL_H_
#define _DEBUGLEVEL_H_

#include "Game.h"
#include "Scene.h"

class DebugLevel : public Game
{
public:
	static Scene* scene;

	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_DEBUGLEVEL_H_
