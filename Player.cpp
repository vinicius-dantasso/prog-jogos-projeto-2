/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "DungeonGame.h"
#include "Scripts.h"
#include <string>

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/Player.png", 32, 32, 1, 1);
    anim = new Animation(tileset, 0.120f, true);
    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    // inicializa estado do player 
    level = 0;

    // inicializa velocidades do player
    spd = 0.0f;
    hSpd = 0.0f;
    vSpd = 0.0f;

    // posição inicial
    //MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == WALL)
        WallCollision(obj);
}

// ---------------------------------------------------------------------------------

void Player::WallCollision(Object* obj)
{

    

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    int hDir = -window->KeyDown('A') + window->KeyDown('D');
    int vDir = -window->KeyDown('W') + window->KeyDown('S');

    float spdDir = Scripts::point_direction(x, y, x + hDir, y + vDir);

    if (hDir != 0 || vDir != 0)
        spd = 180.0f;
    else
        spd = 0;

    hSpd = Scripts::lengthdir_x(spd, spdDir);
    vSpd = Scripts::lengthdir_y(spd, spdDir);

    Translate(hSpd * gameTime, vSpd * gameTime);

    // atualiza animação
    //anim->Select();
    //anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{

    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    std::string xx = std::to_string(x);
    std::string yy = std::to_string(y);

    font->Draw(x, y - 60, xx, white, Layer::FRONT, 0.2f);
    font->Draw(x, y - 20, yy, white, Layer::FRONT, 0.2f);

    anim->Draw(x, y, z);
}