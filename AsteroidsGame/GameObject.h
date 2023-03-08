#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <iostream>
#include <SDL.h>

class GameObject
{

protected:

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect position;

public:

	GameObject(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h);
	~GameObject();

	virtual void draw();
	SDL_Rect getPosition();

};

#endif