
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Player.h"
#include "Pistol.h"
#include "Gui.h"
#include "WorldBuilder.h"

WorldBuilder * builder = nullptr;
Scene* DebugLevel::scene = nullptr;

void DebugLevel::Init()
{
	scene = new Scene();
	DungeonGame::sceneMain = scene;

	scene->Add(DungeonGame::player, MOVING);
	
	scene->Add(DungeonGame::pistol, STATIC);

	scene->Add(DungeonGame::gui, STATIC);

	builder = new WorldBuilder("Resources/DebugMap.png");
}

void DebugLevel::Finalize()
{
	scene->Remove(DungeonGame::player, MOVING);
	delete scene;
	delete builder;
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
