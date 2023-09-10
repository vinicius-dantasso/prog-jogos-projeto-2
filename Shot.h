#ifndef _GRAVITYGUY_SHOT_H_
#define _GRAVITYGUY_SHOT_H_

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Scripts.h"

enum ShotType{PUNCH, ONE, MULTIPLE, DISPERSION};

class Shot : public Object {
private:
    TileSet* tileset;                   //Folha do tiro
    Animation* anim;                    //Animação do tiro

    float spdshot;                     // Velocidade Geral do Tiro
    float delayshot;                   // Delay de disparo
    float shot;                        // Munição

public:
	Shot();                             // Construtor
	~Shot();                            // Destrutor

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

inline void Shot::Draw() {anim->Draw(x, y, z);}

#endif
