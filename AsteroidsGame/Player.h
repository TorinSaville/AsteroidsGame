#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL_mixer.h>

#include "GameObject.h"

class Player :
    public GameObject
{

private:

    int lives;
    SDL_Rect spawn;

public:

    Player(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y);
    void update(int _windowSizeX, int _windowSizeY);
    void gameOver();

    int getLives();
    void setLives(int _lives);

};

#endif