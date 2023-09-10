#include "Gun.h"


Gun::Gun(uint type) {
	script = new Scripts();

	switch (type) {
	case HANDS: 
		break;
	case PISTOL: 
		break;
	case SMG: 
		tileset = new TileSet("Resources/Player.png", 32, 32, 1, 1);
		anim = new Animation(tileset, 0.120f, true);
		// cria bounding box
		BBox(new Rect(
			-1.0f * tileset->TileWidth() / 2.0f,
			-1.0f * tileset->TileHeight() / 2.0f,
			tileset->TileWidth() / 2.0f,
			tileset->TileHeight() / 2.0f));

		break;
	case SHOTGUN: 
		break;
	default: 
		break;
	}
	
	


	// inicializa velocidades da arma
	spd = 0.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	// Posição inicial da Arma
	MoveTo(window->CenterX() + 64.0f, window->CenterY(), Layer::FRONT);
}

Gun::~Gun() {
	delete tileset;
	delete anim;
	//delete shot;
	delete script;
}

void Gun::Update() {

	int hDir = -window->KeyDown('A') + window->KeyDown('D');
	int vDir = -window->KeyDown('W') + window->KeyDown('S');

	if (hDir != 0 || vDir != 0)
		spd = 150.0f;
	else
		spd = 0;

	hSpd = spd * hDir;
	vSpd = spd * vDir;


	Translate(hSpd * gameTime, vSpd * gameTime);
}

void Gun::Draw()
{
	float dir = script->point_direction(DungeonGame::player->X(), DungeonGame::player->Y(), window->MouseX(), window->MouseY());
	float xx = script->lengthdir_x(50, dir);
	float yy = script->lengthdir_y(50, dir);
	anim->Draw(DungeonGame::player->X() + xx, DungeonGame::player->Y() + yy, Layer::FRONT);
}

void Gun::OnCollision(Object* obj) {

}

void Gun::Shoot() {

}