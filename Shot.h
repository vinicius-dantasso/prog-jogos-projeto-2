#ifndef _GRAVITYGUY_SHOT_H_
#define _GRAVITYGUY_SHOT_H_

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Scripts.h"

enum ShotType{PUNCH, ONE, MULTIPLE, DISPERSION};

class Shot : public Object {
private:
    TileSet* tileset;                   //Folha do tiro
    Animation* anim;                    //Anima��o do tiro

    float spdshot;                     // Velocidade Geral do Tiro
    float delayshot;                   // Delay de disparo
    float shot;                        // Muni��o

public:
	Shot();                             // Construtor
	~Shot();                            // Destrutor

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

inline void Shot::Draw() {anim->Draw(x, y, z);}

#endif
