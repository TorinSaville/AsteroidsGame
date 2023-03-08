#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <math.h>

#include "Setup.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"

const int windowSizeX = 1280;
const int windowSizeY = 720;

void gameLoop(SDL_Window* _window, SDL_Renderer* _renderer, Mix_Music* _bkgMusic, Mix_Chunk* _shotAud, Mix_Chunk* _explodeAud);
void updateScore(SDL_Renderer* _renderer, int _score, TTF_Font* _font, SDL_Color _color, std::string _type, SDL_Rect _rect);
bool gameOver(int _score, Player* _player);

int main(int argv, char* argc[]) {

	Setup* setup = new Setup(windowSizeX, windowSizeY);

	gameLoop(setup->getWindow(), setup->getRenderer(), setup->getBKGMusic(), setup->getLaserSFX(), setup->getExplodeSFX());

	delete setup;

	return 0;

}

void gameLoop(SDL_Window* _window, SDL_Renderer* _renderer, Mix_Music* _bkgMusic, Mix_Chunk* _shotAud, Mix_Chunk* _explodeAud) {

	//The Main Game Loop, Handling Updates While Running

	//Play Background Music, Set it to Loop and Check
	if (Mix_PlayMusic(_bkgMusic, -1) < 0) {

		std::cout << "Mix_ERROR: " << Mix_GetError() << std::endl;

	}

	//Create and Initialise Necessary Variables Such as Bool and Objects
	bool running = true;
	bool menu = true;
	bool game = false;
	bool gameFinished = false;
	bool instruct = false;
	bool fire = false;

	srand(time(NULL));

	int score = 0;
	TTF_Font* fontRG = TTF_OpenFont("Resources/Fonts/RetroGaming.ttf", 28);
	SDL_Color orange = {255, 0, 0};

	SDL_Event e;

	GameObject* background = new GameObject(_renderer,"Resources/Images/space_background.bmp", 0, 0, windowSizeX, windowSizeY);
	GameObject* title = new GameObject(_renderer, "Resources/Images/title.bmp", (windowSizeX/2) - 376, 50, 752, 110);
	GameObject* play_btn = new GameObject(_renderer, "Resources/Images/play_button.bmp", (windowSizeX / 2) - 125, (windowSizeY / 2) - 50, 250, 100);
	GameObject* instruct_btn = new GameObject(_renderer, "Resources/Images/instruct_button.bmp", (windowSizeX / 2) - 125, (windowSizeY / 2) + 60, 250, 100);
	GameObject* quit_btn = new GameObject(_renderer, "Resources/Images/quit_button.bmp", (windowSizeX / 2) - 125, (windowSizeY / 2) + 170, 250, 100);
	GameObject* close_btn = new GameObject(_renderer, "Resources/Images/close_button.bmp", 25, 25, 50, 50);
	GameObject* instructions = new GameObject(_renderer, "Resources/Images/instruct.bmp", (windowSizeX / 2) - 500, 180, 1000, 500);
	GameObject* win_board = new GameObject(_renderer, "Resources/Images/win_board.bmp", (windowSizeX / 2) - 500, (windowSizeY / 2) - 250, 1000, 500);
	GameObject* lose_board = new GameObject(_renderer, "Resources/Images/lose_board.bmp", (windowSizeX / 2) - 500, (windowSizeY / 2) - 250, 1000, 500);

	Player* ship = new Player(_renderer, "Resources/Images/spaceship.bmp", (windowSizeX / 2) - 40, (windowSizeY / 2) - 40);
	Bullet* laser = new Bullet(_renderer, "Resources/Images/laser.bmp", (windowSizeX / 2) - 5, (windowSizeY / 2) - 37, 10, 20);

	Asteroid* small_asteroid_1 = new Asteroid(_renderer, "Resources/Images/small_asteroid.bmp", rand() % (windowSizeX-100), 0, 100, 100, 1, 10, _explodeAud);
	Asteroid* small_asteroid_2 = new Asteroid(_renderer, "Resources/Images/small_asteroid.bmp", rand() % (windowSizeX - 100), -150, 100, 100, 1, 10, _explodeAud);
	Asteroid* small_asteroid_3 = new Asteroid(_renderer, "Resources/Images/small_asteroid.bmp", rand() % (windowSizeX - 100), -150, 100, 100, 1, 10, _explodeAud);
	Asteroid* large_asteroid = new Asteroid(_renderer, "Resources/Images/large_asteroid.bmp", rand() % (windowSizeX - 200), -250, 200, 200, 2, 50, _explodeAud);

	SDL_Rect shipBox = ship->getPosition();
	SDL_Rect scoreboardPos{ windowSizeX - 300, 25, 250, 50 };
	SDL_Rect livesPos{ windowSizeX - 300, 75, 250, 50 };

	//Looping While Game is Running
	do {

		//Check Mouse Poistion, Mouse Buttons and Keyboard Buttons
		while (SDL_PollEvent(&e)) {

			//Grab Mouse Position
			int x = e.motion.x;
			int y = e.motion.y;

			//Grab Button Rects
			SDL_Rect btn1 = play_btn->getPosition();
			SDL_Rect btn2 = instruct_btn->getPosition();
			SDL_Rect btn3 = quit_btn->getPosition();
			SDL_Rect btn4 = close_btn->getPosition();

			switch (e.type) {

			case SDL_QUIT:

				running = false;
				break;

			case SDL_MOUSEBUTTONDOWN:

				if (e.button.button == SDL_BUTTON_LEFT) { //When Left Mouse Clicked

					if (menu == true) { //If Statement to Check what Screen is Displayed, If on Menu

						if (x >= btn1.x && x <= btn1.x + btn1.w && y >= btn1.y && y <= btn1.y + btn1.h) { //If Play is Clicked, Stop Menu and Start Game

							menu = false;
							game = true;

						}
						else if (x >= btn2.x && x <= btn2.x + btn2.w && y >= btn2.y && y <= btn2.y + btn2.h) {//If Instructions is Clicked, Stop Menu and Start Instructions

							menu = false;
							instruct = true;

						}
						else if (x >= btn3.x && x <= btn3.x + btn3.w && y >= btn3.y && y <= btn3.y + btn3.h) { //If Quit is Clicked, Stop Menu and Stop Running

							menu = false;
							running = false;

						}

					}
					else if (instruct == true) { //If on Instructions

						if (x >= btn4.x && x <= btn4.x + btn4.w && y >= btn4.y && y <= btn4.y + btn4.h) { //If Close Button Clicked, Stop Instructions and Start Menu

							menu = true;
							instruct = false;

						}

					}
					else if (game == true) {//If on Game

						if (gameFinished == false) {//If Not GameOver

							if (x >= btn4.x && x <= btn4.x + btn4.w && y >= btn4.y && y <= btn4.y + btn4.h) { //If Close Button Clicked, Stop Game and Start Menu. Reset GameObjects

								menu = true;
								game = false;
								score = 0;
								ship->gameOver();
								small_asteroid_1->reset((rand() % 10) * 100, -150);
								small_asteroid_2->reset((rand() % 10) * 100, -150);
								small_asteroid_3->reset((rand() % 10) * 100, -150);
								large_asteroid->reset((rand() % 10) * 100, -250);

							}

						}
						else {//If Game Over

							//If Click Anywhere, Stop Game and Start Menu, Reset GameObjects
							menu = true;
							game = false;
							gameFinished = false;
							score = 0;
							ship->gameOver();

						}

					}

				}

				break;

			case SDL_KEYDOWN://When Key Pressed Down

				if (game == true && gameFinished == false) {//If Game is Running But Not Gameover

					if (e.key.keysym.sym == SDLK_SPACE) {//If Spacebar Pressed

						if (laser->getFired() == false) {//Check if Laser Already Fired, If Not Then...

							//Play Laser Sound,Then Set Laser to Fired
							Mix_PlayChannel(-1, _shotAud, 0);
							laser->setFired(true);

						}


					}

				}

				break;

			default:

				break;

			}

		}

		SDL_RenderClear(_renderer); //Clear Screen

		background->draw(); //Draw Background

		if (menu == true) {//If on Menu, Draw Menu Objects

			title->draw();
			play_btn->draw();
			instruct_btn->draw();
			quit_btn->draw();

		}

		if (instruct == true) {//If on Instructions, Draw Instruction Objects

			title->draw();
			instructions->draw();
			close_btn->draw();

		}

		if (game == true) {//If on Game

			gameFinished = gameOver(score, ship);//GameOver Check

			if (gameFinished == false) {//If not GameOver

				if (laser->getFired() == true) {//If Laser has Been Fired, Draw Laser and Move it. Check if Laser has Hit an Asteroid

					laser->draw();
					laser->fire();

					large_asteroid->hit(laser);
					small_asteroid_1->hit(laser);
					small_asteroid_2->hit(laser);
					small_asteroid_3->hit(laser);

				}
				else {// If Laser Not Fired, Update it to Ship Position Ready to be Fired

					laser->reload(ship);

				}

				//Update and Draw Ship
				ship->update(windowSizeX, windowSizeY);
				ship->draw();

				//Check if Asteroids Have Been Destroyed, Update Position and Draw Them
				score += large_asteroid->isDestroyed(ship);
				large_asteroid->update((rand() % 10) * 100);
				large_asteroid->draw();

				score += small_asteroid_1->isDestroyed(ship);
				small_asteroid_1->update((rand() % 10) * 100);
				small_asteroid_1->draw();


				score += small_asteroid_2->isDestroyed(ship);
				small_asteroid_2->update((rand() % 10) * 100);
				small_asteroid_2->draw();

				score += small_asteroid_3->isDestroyed(ship);
				small_asteroid_3->update((rand() % 10) * 100);
				small_asteroid_3->draw();

				//Update and Draw Scores and Draw Close Button
				updateScore(_renderer, score, fontRG, orange, "Score: ", scoreboardPos);
				updateScore(_renderer, ship->getLives(), fontRG, orange, "Lives: ", livesPos);

				close_btn->draw();

			}
			else {//If GameOver
				
				

				if (score >= 1000) {//Check Win Condition, If 1000 Points Scored Draw Win Object

					win_board->draw();

				}
				else {// If 3 Lives Lost, Draw Lose Object

					lose_board->draw();

				}

				//Reset Asteroids 
				small_asteroid_1->reset((rand() % 10) * 100, -150);
				small_asteroid_2->reset((rand() % 10) * 100, -150);
				small_asteroid_3->reset((rand() % 10) * 100, -150);
				large_asteroid->reset((rand() % 10) * 100, -250);

			}

		}

		//Display Updated Screen
		SDL_RenderPresent(_renderer);

	} while (running == true);

	//When Running Equals False, Delete All Objects
	delete background;
	delete ship;
	delete title;
	delete play_btn;
	delete instruct_btn;
	delete small_asteroid_1;
	delete small_asteroid_2;
	delete small_asteroid_3;
	delete large_asteroid;
	delete quit_btn;
	delete instructions;
	delete win_board;
	delete lose_board;

}

//Function to Update ScoreBoards
void updateScore(SDL_Renderer* _renderer, int _score, TTF_Font* _font, SDL_Color _color, std::string _type, SDL_Rect _rect) {

	//Turn Score int Value into String Value and Add to Score Board STring
	std::stringstream ss;
	ss << _score;
	std::string scoreboard = _type + ss.str();

	//Update Texture
	SDL_Surface* temp = TTF_RenderText_Solid(_font, scoreboard.c_str(), _color);
	SDL_Texture* textTex = SDL_CreateTextureFromSurface(_renderer, temp);
	SDL_FreeSurface(temp);

	SDL_RenderCopy(_renderer, textTex, NULL, &_rect);

}

//Function to Check if GameOver
bool gameOver(int _score, Player* _player) {

	//If Score is 1000 or More or if No Lives Remaining, GameOver
	//Otherwise Carry on Game
	if (_score >= 1000 || _player->getLives() <= 0) {
		return true;
	}
	else {
		return false;
	}

}