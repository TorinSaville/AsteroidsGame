#include "Button.h"

Button::Button(SDL_Renderer* _renderer, const char* _fileName, int _x, int _y, int _w, int _h, SDL_Event _e) :
	GameObject(_renderer, _fileName, _x, _y, _w, _h) {

	e = _e;
	pressed = false;

}

void Button::press() {

	int x, y{ 0 };

	if (e.type == SDL_MOUSEBUTTONDOWN) {

		if (e.button.button == SDL_BUTTON_LEFT) {

			x = e.motion.x;
			y = e.motion.y;

			if (x >= position.x && x <= position.x + position.w && y >= position.y && y <= position.y + position.h) {

				std::cout << "Button Pressed" << std::endl;
				pressed = true;

			}

		}

	}

}