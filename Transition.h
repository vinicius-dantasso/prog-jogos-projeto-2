
#ifndef _LEVEL_TRANSITION_H_
#define _LEVEL_TRASITION_H_

#include "Object.h"
#include "Sprite.h"

class Transition : public Object
{
private:
	Sprite * transition = nullptr;

	float upper;
	float lower;
	
	bool finalized;

public:
	Transition();
	~Transition();

	bool Finalized();

	void Update();
	void Draw();
};

inline bool Transition::Finalized()
{
	return finalized;
}

#endif // !_LEVEL_TRANSITION_H_
