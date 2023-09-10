#ifndef _GRAVITYGUY_GUN_H_
#define _GRAVITYGUY_GUN_H_

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Scripts.h"
#include "Shot.h"
#include "DungeonGame.h"


enum GunTypes{HANDS, PISTOL, SMG, SHOTGUN};
enum State{EQUIPPED, NOT_EQUIPPED}; //Para armas que poderão ser coletadas do chao

class Gun : public Object {
private:
    TileSet* tileset = nullptr;                   // Folha de sprites da arma
    Animation* anim = nullptr;                    // Animação da arma
    Shot* shot = nullptr;                         // Tiro da arma
    Scripts* script = nullptr;                    // Normalizaçao 
   

    float       spd;                    // Velocidade Geral
    float       hSpd;                   // Velocidade Horizontal
    float       vSpd;                   // Velocidade Vertical
public:
	Gun(uint type);
	~Gun();

    // uint type;

    void Shoot();
    void OnCollision(Object* obj);     // Resolução da colisão
    void Update();                      // Atualização do objeto
    void Draw();                        // Desenho do objeto
};



#endif