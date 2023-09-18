/**********************************************************************************
// GravityGuy (C�digo Fonte)
// 
// Cria��o:     05 Out 2011
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "DungeonGame.h"
#include "Home.h"
#include "GameOver.h"
#include "DebugLevel.h"

// ------------------------------------------------------------------------------

// inicializa membros est�ticos da classe
Game*   DungeonGame::level = nullptr;
Player* DungeonGame::player = nullptr;
Audio*  DungeonGame::audio = nullptr;
Pistol* DungeonGame::pistol = nullptr;
Bullet* DungeonGame::bullet = nullptr;
bool    DungeonGame::viewBBox = false;

// ------------------------------------------------------------------------------

void DungeonGame::Init()
{
    // cria sistema de �udio
    /*
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");
    */

    // bounding box n�o vis�vel
    viewBBox = false;

    // cria jogador
    player = new Player();

    // cria arma
    pistol = new Pistol();

    // inicializa n�vel de abertura do jogo
    level = new DebugLevel();
    level->Init();
}

// ------------------------------------------------------------------------------

void DungeonGame::Update()
{
    // habilita/desabilita visualiza��o da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza n�vel
    level->Update();
} 

// ------------------------------------------------------------------------------

void DungeonGame::Draw()
{
    // desenha n�vel
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

