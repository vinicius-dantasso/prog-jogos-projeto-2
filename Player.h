/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador 
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Font.h"
#include "Sprite.h"
#include "Timer.h"

// ---------------------------------------------------------------------------------

enum AnimationState {IDLELEFT,IDLERIGHT,MOVINGLEFT,MOVINGRIGHT,HITL,HITR, DEADL,DEADR};
enum PlayerState {PLAYERMOVE,PLAYERHIT, PLAYERDEAD, PLAYERDASH};

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // anima��o do personagem
    Sprite    * shadow;
    Font      * font;
    Timer     * timer;

    float       spd;                    // Velocidade Geral
    float       hSpd;                   // Velocidade Horizontal
    float       vSpd;                   // Velocidade Vertical
    float       knockBackDir;           // Dire��o do Empurr�o
    float       knockBackSpd;           // Intensidade do Empurr�o
    float       dashDir;
    float       dashSpd;

    int         hDir;                   // Dire��o Horizontal
    int         vDir;                   // Dire��o Vertical
    int         lastHdir;
    int         frames;
    int         maxFrames;
    int         life;
    int         maxLife;
    int         bombTotal;

    bool        hit;
    
public:
    uint state;
    uint animState;

    bool goingTo;
    bool isDead;

    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    void WallCollision(Object * obj);
    void Hit();
    void Dash();
    void SetBombs(int bombs);
    void OnShop();
    void SetLife(int lifes);
    int Life();
    int MaxLife();
    int BombTotal();

    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline int Player::Life()
{ return life; }

inline int Player::MaxLife()
{ return maxLife; }

inline int Player::BombTotal()
{ return bombTotal; }

inline void Player::SetBombs(int bombs)
{ bombTotal += bombs; }

inline void Player::SetLife(int lifes)
{ life += lifes; }

// ---------------------------------------------------------------------------------

#endif