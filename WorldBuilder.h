
#ifndef _WORLD_BUILDER_H_
#define _WORLD_BUILDER_H_

#include "DungeonGame.h"

class WorldBuilder
{
private:
	int width;
	int height;
	int channels;

public:
	WorldBuilder(const char* path);
	~WorldBuilder();
};

#endif // !_WORLD_BUILDER_H_
