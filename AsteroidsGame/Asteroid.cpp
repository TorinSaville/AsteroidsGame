#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h, int _health, int _points, Mix_Chunk* _explode) :
	GameObject(_renderer, _fileName, _x, _y, _w, _h) {

	//Init Asteroid Variables
	explode = _explode;
	health = _health;
	currHealth = _health;
	points = _points;
	yInc = 1;
	timer = 0;


}

int Asteroid::getPoints() { return points; }

void Asteroid::hit(Bullet* _laser) {

	//Function to Check if Asteroid has Been Hit

	SDL_Rect laser = _laser->getPosition();

	if (laser.x <= position.x + position.w && laser.x + laser.w >= position.x &&
		laser.y >= position.y && laser.y + laser.h <= position.y + position.h) { //If Laser Rect is Inside Asteroid Rect, Means Collision

		//Decrement Asteroid Health and Reset Laser
		currHealth--;
		_laser->setFired(false);

	}

}

void Asteroid::update(int _xCoord){

	//Function to Update Asteroid Position

	if (destroyed == true) {//If Asteroid has Been Destroyed, Set it to Passed Throough Random X Value and Y Value, Set to No Longer Destroyed

		position.x = _xCoord;
		position.y = 0 - (50 + position.h);

		destroyed = false;

	}
	else {//If Not Destroyed, Delay Update With Timer then Increment Y and Set Timer to 0

		if (timer == 3) {
			position.y += yInc;
			timer = 0;
		}
		else {
			timer++;
		}

	}

}

int Asteroid::isDestroyed(Player* _player) {

	//Function to Check if Asteroid has Benn Destroyed, Returns Score

	int score = 0;
	SDL_Rect ship = _player->getPosition();

	if (currHealth == 0) {//If Health is 0, Set Asteroid as Destroyed, Add Points, Reset Health and Play Explosion Sound

		destroyed = true;
		score += points;
		currHealth = health;
		Mix_PlayChannel(-1, explode, 0);

	}
	else if((position.y + position.h >= 720) || (ship.x <= position.x + position.w && ship.x + ship.w >= position.x &&
		ship.y >= position.y && ship.y + ship.h <= position.y + position.h)){

		//If Asteroid Hits Planet (Bottom of Screen) or Hits Ship
		//Take Away Player Life, Set Asteroid as Destroyed, Reset Health and Play Explosion Sound

			_player->setLives(_player->getLives() - 1);
			destroyed = true;
			currHealth = health;
			Mix_PlayChannel(-1, explode, 0);

	}
	else {//If None of the Above, Asteroid is Not Destroyed

		destroyed = false;

	}

	return score;

}

bool Asteroid::getDestroyed() { return destroyed; }

void Asteroid::reset(int _x, int _y) {

	position.x = _x;
	position.y = _y;

}