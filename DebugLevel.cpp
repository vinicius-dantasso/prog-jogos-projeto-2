
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Player.h"

Scene* DebugLevel::scene = nullptr;

void DebugLevel::Init()
{
	scene = new Scene();
	gun = new Gun(SMG);
	scene->Add(DungeonGame::player, MOVING);
	scene->Add(gun, MOVING);
}

void DebugLevel::Finalize()
{
	scene->Remove(DungeonGame::player, MOVING);
	delete scene;
}

void DebugLevel::Update()
{
	scene->Update();
	scene->CollisionDetection();
}

void DebugLevel::Draw()
{
	scene->Draw();

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}
