#ifndef GAME_H
#define GAME_H

#include "Entity/Entity.h"

class Game
{
public:
    InputReceiver *receiver;
    Painter *painter;
    u32 anterior;
    vector<Entity*>entidades;

    Game();
    void intro();
    void gameLoop();
    void logic();
    void render();
    void waitSync();
};
#endif // GAME_H>
