/**********************************************************************************
// GravityGuy (Arquivo de Cabe�alho)
// 
// Cria��o:     05 Out 2011
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#ifndef _DUNGEONGAME_H_
#define _DUNGEONGAME_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Resources.h"
#include "Scene.h"
#include "WorldBuilder.h"
#include "Gui.h"

// ------------------------------------------------------------------------------

enum Sounds {MENU, MUSIC, TRANSITION};
enum ObjectsToCollide {PLAYER, WALL, HWALL, VWALL, BULLET, MAGIC, TRAP, ENEMY, BUGHOLE};

// ------------------------------------------------------------------------------

class DungeonGame : public Game
{
private:
    static Game * level;            // n�vel atual do jogo

public:
    static Player * player;         // jogador
    static Pistol * pistol;         // arma
    static Bullet * bullet;         // tiro
    static Audio * audio;           // sistema de �udio
    static Scene * scene;
    static Gui * gui;

    static int floorNum;
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para pr�ximo n�vel do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif