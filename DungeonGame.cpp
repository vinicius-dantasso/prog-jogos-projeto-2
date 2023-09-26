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
    
    audio = new Audio();
    audio->Add(MUSIC, "Resources/BossTheme.wav");
    audio->Volume(MUSIC, 0.25f);

    audio->Add(TRANSITION, "Resources/sfxSelect.wav"); //COLOCAR UM EFEITO DE GENTE

    audio->Add(SHOTPLAYER, "Resources/sfxTiroPlayer.wav");

    audio->Add(DASH, "Resources/sfxDash.wav"); //PRECISA MUDAR O EFEITO, ESSE AQUI TA SE MISTURANDO MUITO COM O AUDIO
    audio->Volume(DASH, 0.5f);

    audio->Add(BOMBTHROW, "Resources/sfxBomba.wav");

    audio->Add(HITPLAYER, "Resources/sfxHit.wav");

    audio->Add(HITENEMY, "Resources/sfxEnemyHit.wav");

    audio->Add(RELOAD, "Resources/sfxRecarregarArma.wav");
    audio->Volume(RELOAD, 0.7f);

    audio->Add(BUGCHASE, "Resources/sfxBurrowAndando.wav");
    audio->Volume(BUGCHASE, 0.8f);
    
    audio->Add(BUGJUMP, "Resources/sfxBurrowAtacando.wav");
    audio->Volume(BUGJUMP, 0.8f);

    audio->Add(GAMEOVER, "Resources/DeathTheme1.wav");
    audio->Volume(GAMEOVER, 0.3f);

    audio->Add(COIN, "Resources/sfxMoeda.wav");
    audio->Volume(COIN, 0.75f);

    audio->Add(OPENDOOR, "Resources/sfxPortaAbrida.wav");
    audio->Volume(OPENDOOR, 0.75f);

    audio->Add(SHOTENEMY, "Resources/sfxTiroInimigo.wav");
    audio->Volume(SHOTENEMY, 0.9f);

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

