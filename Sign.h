
#ifndef _SIGN_H_
#define _SIGN_H_

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include <string>
using namespace std;

class Sign : public Object
{
private:
	Sprite* sprite;
	Font* font;

	string text;
	bool canDraw;

public:
	Sign(string write);
	~Sign();

	void Update();
	void Draw();
};

#endif // !_SIGN_H_
