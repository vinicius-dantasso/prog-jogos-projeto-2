#include "Shot.h"

Shot::Shot(){
	tileset = new TileSet("Resources/Shot.png", 32, 32, 1, 1);
    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    spdshot = 100.0f;
    delayshot = 0.5f;
    shot = 100;
}

Shot::~Shot() {
	delete tileset;
}

void Shot::Update() {
	Translate(window->MouseX() * spdshot * gameTime, window->MouseY() * spdshot * gameTime);
}

void Shot::OnCollision(Object* obj) {
   
}

