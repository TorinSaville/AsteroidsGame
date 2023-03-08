#pragma once
#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"

class Asteroid :
    public GameObject
{
private:

    bool destroyed;
    int health;
    int currHealth;
    int points;
    Mix_Chunk* explode;

    int yInc;
    int timer;

public:

    Asteroid(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h, int _health, int _points, Mix_Chunk* _explode);

    int getPoints();

    void hit(Bullet* _laser);

    void update(int _xCoord);

    int isDestroyed(Player* _player);

    bool getDestroyed();
    
    void reset(int _x, int _y);

};

#endif