#pragma once
#include "GameObject.h"

class Button :
    public GameObject
{

private:

    SDL_Event e;
    bool pressed;

public:

    Button(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h, SDL_Event _e);

    void press();

};

