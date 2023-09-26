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
#include "Bomb.h"
#include <string>

// ---------------------------------------------------------------------------------
Player::Player()
{
    tileset = new TileSet("Resources/Player.png", 64, 64, 4, 16);
    anim = new Animation(tileset, 0.120f, true);
    shadow = new Sprite("Resources/Player_Shadow.png");

    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    timer = new Timer();
    timer->Start();

    uint SeqIdleRight[2] = { 8,9 };
    uint SeqIdleLeft[2] = { 10,11 };
    uint SeqMovingRight[4] = { 0,1,2,3 };
    uint SeqMovingLeft[4] = { 4,5,6,7 };
    uint SeqHitL[1] = { 13 };
    uint SeqHitR[1] = { 12 };
    uint SeqDeadL[1] = { 14 };
    uint SeqDeadR[1] = { 15 };

    anim->Add(IDLELEFT, SeqIdleLeft, 2);
    anim->Add(IDLERIGHT, SeqIdleRight, 2);
    anim->Add(MOVINGLEFT, SeqMovingLeft, 4);
    anim->Add(MOVINGRIGHT, SeqMovingRight, 4);
    anim->Add(HITL, SeqHitL, 1);
    anim->Add(HITR, SeqHitR, 1);
    anim->Add(DEADL, SeqDeadL, 1);
    anim->Add(DEADR, SeqDeadR, 1);
    
    type = PLAYER;
    isDead = false;

    frames = 0;
    maxFrames = 10;

    life = 5;
    maxLife = 5;

    dashDir = 0.0f;
    dashSpd = 500.0f;

    bombTotal = 3;

    spd = 0.0f;
    hSpd = 0.0f;
    vSpd = 0.0f;

    state = PLAYERMOVE;
    animState = IDLELEFT;

    BBox(new Rect(-16, -16, 16, 16));
    MoveTo(864.0f, 640.0f);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
    delete font;
    delete shadow;
    delete timer;
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    state = PLAYERMOVE;
    animState = IDLELEFT;

    life = 5;
    bombTotal = 3;
    isDead = false;
    hit = false;

    DungeonGame::coinTotal = 0;
    DungeonGame::floorNum = 0;
    DungeonGame::enemiesTotal = 0;
    DungeonGame::pistol->Reset();

    MoveTo(864.0f, 640.0f);
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == HWALL)
    {
        if (x + 16 >= obj->X() - 16 && x - 16 <= obj->X() - 16)
            MoveTo(obj->X() - 32, y);
        else if (x - 16 <= obj->X() + 16 && x + 16 >= obj->X() - 16)
            MoveTo(obj->X() + 32, y);
    }

    if (obj->Type() == VWALL)
    {
        if (y - 16 <= obj->Y() + 16 && y + 16 >= obj->Y() + 16)
            MoveTo(x, obj->Y() + 32);
        else if (y + 16 >= obj->Y() - 16 && y - 16 <= obj->Y() - 16)
            MoveTo(x, obj->Y() - 32);
    }

    if (obj->Type() == WALL)
        WallCollision(obj);

    if ((obj->Type() == ENEMY || obj->Type() == MAGIC) && !hit && state != PLAYERDEAD)
    {
        hit = true;
        life -= 1;
        float dir = Scripts::point_direction(obj->X(), obj->Y(), x, y);
        knockBackDir = dir;
        knockBackSpd = 200.0f;
        state = PLAYERHIT;

        if (animState == IDLELEFT || animState == MOVINGLEFT)
            animState = HITL;
        else if (animState == IDLERIGHT || animState == MOVINGRIGHT)
            animState = HITR;
    }
}

// ---------------------------------------------------------------------------------

void Player::WallCollision(Object* obj)
{

    float deltaX = (obj->X() - (16 * hDir)) - (x - (32 * hDir));
    float deltaY = (obj->Y() - (16 * vDir)) - (y - (32 * vDir));

    // Verifica se a colisão é mais horizontal ou vertical
    if (abs(deltaX) > abs(deltaY))
    {
        // Colisão mais horizontal, ajusta horizontalmente
        if (hDir > 0)
            MoveTo(obj->X() - 32, y);
        else if (hDir < 0)
            MoveTo(obj->X() + 32, y);
    }
    else
    {
        // Colisão mais vertical, ajusta verticalmente
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

    if(!hit)
    {
        switch (hDir)
        {
        case 1:
            lastHdir = 1;
            animState = MOVINGRIGHT;
            break;

        case -1:
            lastHdir = -1;
            animState = MOVINGLEFT;
            break;

        default:
            if (lastHdir == 1)
                animState = IDLERIGHT;
            else if (lastHdir == -1)
                animState = IDLELEFT;
            break;
        }
    }

    if (window->KeyPress(VK_SPACE) && timer->Elapsed() >= 0.5f)
    {
        timer->Reset();
        state = PLAYERDASH;
    }

    if (state == PLAYERDASH && timer->Elapsed(0.2f))
    {
        timer->Reset();
        hit = false;
        state = PLAYERMOVE;
    }

    if (bombTotal > 0 && window->KeyPress('G'))
    {
        DungeonGame::bomb = new Bomb(x, y, DROPPED);
        DungeonGame::bomb->dir = Scripts::point_direction(x, y, window->MouseX(), window->MouseY());
        DungeonGame::sceneMain->Add(DungeonGame::bomb, MOVING);
        bombTotal -= 1;
    }

    if (DungeonGame::onShop)
        OnShop();

    switch (state)
    {
    case PLAYERMOVE:
        if(!goingTo)
        {
            hSpd = Scripts::lengthdir_x(spd, spdDir);
            vSpd = Scripts::lengthdir_y(spd, spdDir);
        }
        else
        {
            hSpd = 0.0f;
            vSpd = 0.0f;
        }
        break;

    case PLAYERHIT:
        Hit();
        break;

    case PLAYERDASH:
        hSpd = 0.0f;
        vSpd = 0.0f;
        Dash();
        break;

    case PLAYERDEAD:
        hSpd = 0.0f;
        vSpd = 0.0f;

        if (animState == IDLELEFT || animState == MOVINGLEFT || animState == HITL)
            animState = DEADL;
        else if (animState == IDLERIGHT || animState == MOVINGRIGHT || animState == HITR)
            animState = DEADR;
        
        if (timer->Elapsed(5.0f))
            isDead = true;
        break;
    }

    Translate(hSpd * gameTime, vSpd * gameTime);

    if (life <= 0 && state != PLAYERDEAD)
    {
        timer->Reset();
        state = PLAYERDEAD;
    }

    // atualiza animação
    anim->Select(animState);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    /*
    std::string xx = std::to_string(window->MouseX());
    std::string yy = std::to_string(window->MouseY());

    font->Draw(window->MouseX(), window->MouseY() - 40, xx, white, Layer::FRONT, 0.3f);
    font->Draw(window->MouseX(), window->MouseY() - 10, yy, white, Layer::FRONT, 0.3f);
    */

    shadow->Draw(x, y + 15, Layer::LOWER);
    anim->Draw(x, y, Layer::UPPER);
}

void Player::Hit()
{
    knockBackSpd = Scripts::lerp(knockBackSpd, 0.0f, 0.3f);

    hSpd = Scripts::lengthdir_x(knockBackSpd, knockBackDir);
    vSpd = Scripts::lengthdir_y(knockBackSpd, knockBackDir);

    frames++;
    if (frames >= maxFrames)
    {
        frames = 0;
        state = PLAYERMOVE;
        hit = false;
    }
}

void Player::Dash()
{
    if (hDir > 0 && vDir > 0)
        dashDir = Scripts::point_direction(x, y, x + 1.0f, y + 1.0f);
    else if (hDir > 0 && vDir < 0)
        dashDir = Scripts::point_direction(x, y, x + 1.0f, y - 1.0f);
    else if (hDir < 0 && vDir > 0)
        dashDir = Scripts::point_direction(x, y, x - 1.0f, y + 1.0f);
    else if (hDir < 0 && vDir < 0)
        dashDir = Scripts::point_direction(x, y, x - 1.0f, y - 1.0f);
    else if (hDir > 0)
        dashDir = Scripts::point_direction(x, y, x + 1.0f, y);
    else if (hDir < 0)
        dashDir = Scripts::point_direction(x, y, x - 1.0f, y);
    else if (vDir > 0)
        dashDir = Scripts::point_direction(x, y, x, y + 1.0f);
    else if (vDir < 0)
        dashDir = Scripts::point_direction(x, y, x, y - 1.0f);

    hit = true;
    hSpd = Scripts::lengthdir_x(dashSpd, dashDir);
    vSpd = Scripts::lengthdir_y(dashSpd, dashDir);
}

void Player::OnShop()
{
    if (Scripts::distance_to_object(this, DungeonGame::bomb) <= 60)
    {
        if (DungeonGame::bomb->state == BOMBITEM && window->KeyPress('F') && DungeonGame::coinTotal >= 30)
        {
            this->SetBombs(3);
            DungeonGame::coinTotal -= 30;
            DungeonGame::sceneMain->Delete(DungeonGame::bomb, MOVING);
            DungeonGame::onShop = false;
        }
    }
}