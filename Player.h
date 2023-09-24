/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador 
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Font.h"
#include "Sprite.h"
#include "Timer.h"

// ---------------------------------------------------------------------------------

enum AnimationState {IDLELEFT,IDLERIGHT,MOVINGLEFT,MOVINGRIGHT,HITL,HITR};
enum PlayerState {PLAYERMOVE,PLAYERHIT, PLAYERDEAD, PLAYERDASH};

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
    Sprite    * shadow;
    Font      * font;
    Timer     * timer;

    float       spd;                    // Velocidade Geral
    float       hSpd;                   // Velocidade Horizontal
    float       vSpd;                   // Velocidade Vertical
    float       knockBackDir;           // Direção do Empurrão
    float       knockBackSpd;           // Intensidade do Empurrão
    float       dashDir;
    float       dashSpd;

    int         hDir;                   // Direção Horizontal
    int         vDir;                   // Direção Vertical
    int         level;                  // nível finalizado
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

    Player();                           // construtor
    ~Player();                          // destrutor

    //void Reset();                       // volta ao estado inicial
    int Level();                        // último nível finalizado
    void WallCollision(Object * obj);
    void Hit();
    void Dash();
    int Life();
    int MaxLife();
    int BombTotal();

    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline int Player::Level()
{ return level; }

inline int Player::Life()
{ return life; }

inline int Player::MaxLife()
{ return maxLife; }

inline int Player::BombTotal()
{ return bombTotal; }

// ---------------------------------------------------------------------------------

#endif