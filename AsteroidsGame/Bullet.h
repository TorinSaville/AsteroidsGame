#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"
#include "Player.h"
class Bullet :
    public GameObject
{

private:

    bool fired;
    int timer;

public:

    Bullet(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h);

    bool getFired();
    void setFired(bool _fired);

    void fire();
    void reload(Player* _player);

};

#endif