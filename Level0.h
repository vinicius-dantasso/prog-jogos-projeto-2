
#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include "Game.h"
#include "WorldBuilder.h"

class Level0 : public Game
{
private:
	WorldBuilder * builder;

public:
	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_LEVEL_MANAGER_H_
