/**********************************************************************************
// GameOver (Arquivo de Cabe�alho)
// 
// Cria��o:     14 Fev 2013
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Fim do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GameOver.h"
#include "DungeonGame.h"
#include "Home.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
    title = new Sprite("Resources/GameOver.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
        DungeonGame::NextLevel<Home>();
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
}

// ----------------------------------------------------------------------

