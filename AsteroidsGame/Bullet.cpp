#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h) :
	GameObject(_renderer, _fileName, _x, _y, _w, _h) {

	fired = false;
	timer = 0;

}

bool Bullet::getFired() { return fired; }
void Bullet::setFired(bool _fired) { fired = _fired; }

void Bullet::fire() {

	if (fired == true) {//If Bullet Fired

		timer++;

		if ((position.y <= 0 - position.h) || (timer == 400)) {//If Bullet is OffScreen or has Been Fired for Too Long, Turn Fired off and Reset Timer

			fired = false;
			timer = 0;

		}
		else {//Else Keep Moving Bullet Up

			position.y -= 1;
			fired = true;

		}

	}
	else {//If Bullet Not Fired, Make Sure Timer is 0

		timer = 0;

	}

}

void Bullet::reload(Player* _player) {

	//Function that Resets Laser to Ship Position
	//Reset Timer to 0

	SDL_Rect pPos = _player->getPosition();

	position.x = pPos.x + 35;
	position.y = pPos.y + 3;

	timer = 0;

}