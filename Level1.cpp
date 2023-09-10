/**********************************************************************************
// Level1 (Código Fonte) 
// 
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#include "DungeonGame.h"
#include "Home.h"
#include "Level1.h"
#include "GameOver.h"
#include "Player.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene * Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(DungeonGame::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    /*
    Platform * plat;
    float posX, posY;
    uint  platType;
    Color white { 1,1,1,1 };

    ifstream fin;
    fin.open("Level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, white);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();
    */

    // ----------------------

    // inicia com música
    DungeonGame::audio->Frequency(MUSIC, 0.94f);
    DungeonGame::audio->Frequency(TRANSITION, 1.0f);
    DungeonGame::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    /*
    if (window->KeyPress(VK_ESCAPE))
    {
        DungeonGame::audio->Stop(MUSIC);
        DungeonGame::NextLevel<Home>();
        DungeonGame::player->Reset();
    }
    else if (DungeonGame::player->Bottom() < 0 || DungeonGame::player->Top() > window->Height())
    {
        DungeonGame::audio->Stop(MUSIC);
        DungeonGame::NextLevel<GameOver>();
        DungeonGame::player->Reset();
    }
    else if (DungeonGame::player->Level() == 1 || window->KeyPress('N'))
    {
        //DungeonGame::NextLevel<Level2>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
    */
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (DungeonGame::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(DungeonGame::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
