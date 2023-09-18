/**********************************************************************************
// Player (C�digo Fonte)
// 
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "DungeonGame.h"
#include "Scripts.h"
#include <string>

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/Player.png", 64, 64, 1, 1);
    anim = new Animation(tileset, 0.120f, true);
    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    // cria bounding box
    BBox(new Rect(-16,-16,16,16));
    
    // inicializa estado do player 
    level = 0;

    // inicializa velocidades do player
    spd = 0.0f;
    hSpd = 0.0f;
    vSpd = 0.0f;

    // posi��o inicial
    MoveTo(864.0f, 640.0f);
    //MoveTo(window->CenterX() + 50, window->CenterY());
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
    delete font;
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

    float deltaX = (obj->X() - (16 * hDir)) - (x - (32 * hDir));
    float deltaY = (obj->Y() - (16 * vDir)) - (y - (32 * vDir));

    // Verifica se a colis�o � mais horizontal ou vertical
    if (abs(deltaX) > abs(deltaY))
    {
        // Colis�o mais horizontal, ajusta horizontalmente
        if (hDir > 0)
            MoveTo(obj->X() - 32, y);
        else if (hDir < 0)
            MoveTo(obj->X() + 32, y);
    }
    else
    {
        // Colis�o mais vertical, ajusta verticalmente
        if (vDir > 0)
            MoveTo(x, obj->Y() - 32);
        else if (vDir < 0)
            MoveTo(x, obj->Y() + 32);
    }

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    hDir = -window->KeyDown('A') + window->KeyDown('D');
    vDir = -window->KeyDown('W') + window->KeyDown('S');

    float spdDir = Scripts::point_direction(x, y, x + hDir, y + vDir);

    if (hDir != 0 || vDir != 0)
        spd = 180.0f;
    else
        spd = 0;

    hSpd = Scripts::lengthdir_x(spd, spdDir);
    vSpd = Scripts::lengthdir_y(spd, spdDir);

    Translate(hSpd * gameTime, vSpd * gameTime);

    // atualiza anima��o
    //anim->Select();
    //anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    anim->Draw(x, y, Layer::UPPER);
}