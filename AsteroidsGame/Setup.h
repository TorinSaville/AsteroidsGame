#pragma once
#ifndef _SETUP_H_
#define _SETUP_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

class Setup
{

private:

	Mix_Music* bkgMusic;
	Mix_Chunk* laserSFX;
	Mix_Chunk* explodeSFX;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:

	Setup(int _windowSizeX, int _windowSizeY);
	~Setup();

	Mix_Music* getBKGMusic();
	Mix_Chunk* getLaserSFX();
	Mix_Chunk* getExplodeSFX();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

};

#endif