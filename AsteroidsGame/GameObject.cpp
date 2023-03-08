#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h) {

	//On Object Creation, Add Texture, Initialise Object Position and Renderer
	SDL_Surface* bmpFile = SDL_LoadBMP(_fileName);
	SDL_SetColorKey(bmpFile, SDL_TRUE, SDL_MapRGB(bmpFile->format, 100, 208, 255));
	texture = SDL_CreateTextureFromSurface(_renderer, bmpFile);
	SDL_FreeSurface(bmpFile);
	

	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;

	renderer = _renderer;

}

GameObject::~GameObject() {

	//On Object Deletion, Destroy Texture
	if (texture)
		SDL_DestroyTexture(texture);

}

void GameObject::draw() {

	//Draw GameObject on Screen
	if (texture)
		SDL_RenderCopy(renderer, texture, NULL, &position);

}

SDL_Rect GameObject::getPosition() { return position; }