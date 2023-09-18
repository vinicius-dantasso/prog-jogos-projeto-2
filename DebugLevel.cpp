
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Player.h"
#include "WorldBuilder.h"

Scene* DebugLevel::scene = nullptr;
WorldBuilder* world = nullptr;

void DebugLevel::Init()
{
	scene = new Scene();

	scene->Add(DungeonGame::player, MOVING);

	world = new WorldBuilder("Resources/DebugMap.png");
}

void DebugLevel::Finalize()
{
	scene->Remove(DungeonGame::player, MOVING);
	delete scene;
	delete world;
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
