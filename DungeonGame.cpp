/**********************************************************************************
// GravityGuy (Código Fonte)
// 
// Criação:     05 Out 2011
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "DungeonGame.h"
#include "DebugLevel.h"
#include "MenuScreen.h"
#include "GameOver.h"
#include "Level0.h"
#include "Level1.h"
#include "Shop.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game*   DungeonGame::level = nullptr;
Player* DungeonGame::player = nullptr;
Audio*  DungeonGame::audio = nullptr;
Pistol* DungeonGame::pistol = nullptr;
Bullet* DungeonGame::bullet = nullptr;
Scene*  DungeonGame::sceneMain = nullptr;
Gui*    DungeonGame::gui = nullptr;
Bomb*   DungeonGame::bomb = nullptr;
int     DungeonGame::floorNum = 0;
int     DungeonGame::enemiesTotal = 0;
int     DungeonGame::coinTotal = 0;
bool    DungeonGame::onShop = false;
bool    DungeonGame::viewBBox = false;

// ------------------------------------------------------------------------------

void DungeonGame::Init()
{
    // cria sistema de áudio
    /*
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");
    */

    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // cria arma
    pistol = new Pistol();

    // cria interface do usuario
    gui = new Gui();

    // inicializa nível de abertura do jogo
    level = new MenuScreen();
    level->Init();
}

// ------------------------------------------------------------------------------

void DungeonGame::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza nível
    level->Update();
} 

// ------------------------------------------------------------------------------

void DungeonGame::Draw()
{
    // desenha nível
    level->Draw();
} 

// ------------------------------------------------------------------------------

void DungeonGame::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1280, 720);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Dungeon Crawler");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new DungeonGame());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

