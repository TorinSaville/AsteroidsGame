#include "Player.h"

Player::Player(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y) :
	GameObject(_renderer, _fileName, _x, _y, 80, 80) {

	lives = 3;
	spawn = position;

}

void Player::update(int _windowSizeX, int _windowSizeY) {

	//Function to Update Player Position

	//Get Keyboard State
	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (key[SDL_SCANCODE_W])//If W Pressed, Decrement Y
		if(position.y > 0)
			position.y -= 1;

	if (key[SDL_SCANCODE_S])//If S Pressed, Increment Y
		if (position.y < _windowSizeY - position.h)
			position.y += 1;

	if (key[SDL_SCANCODE_D])//If D Pressed, Decrement X
		if (position.x < _windowSizeX - position.w)
		position.x += 1;

	if (key[SDL_SCANCODE_A])//If A Pressed, Increment X
		if (position.x > 0)
			position.x -= 1;

}

void Player::gameOver(){

	//On GameOver, reset Player

	lives = 3;
	position.x = spawn.x;

}

int Player::getLives() { return lives; }
void Player::setLives(int _lives) { lives = _lives; }