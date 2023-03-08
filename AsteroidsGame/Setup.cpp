#include "Setup.h"

Setup::Setup(int _windowSizeX, int _windowSizeY) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {

		std::cout << "ERROR: Unable to Initialise SDL. SDL_ERROR: " << SDL_GetError() << std::endl;

	}

	//Create AND Check SDL_TTF Initialised
	if (TTF_Init() < 0) {
		std::cout << "ERROR: Unable to Initialise TTF. TTF_ERROR: " << TTF_GetError() << std::endl;
	}

	//Open and Check SDL_Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		std::cout << "ERROR: Unable to Open Audio. Mix_ERROR: " << Mix_GetError() << std::endl;

	//Create and Init Mixer Music and Chunks
	bkgMusic = Mix_LoadMUS("Resources/Audio/background_music.mp3");
	laserSFX = Mix_LoadWAV("Resources/Audio/laser_chunk.wav");
	explodeSFX = Mix_LoadWAV("Resources/Audio/explode_chunk.wav");

	//Create and Check Window
	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_windowSizeX, _windowSizeY, SDL_WINDOW_SHOWN);

	if (!window)
		std::cout << "ERROR: Unable to Create Window. SDL_ERROR: " << SDL_GetError() << std::endl;

	//Create and Check Window
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
		std::cout << "ERROR: Unable to Create Renderer. SDL_ERROR: " << SDL_GetError() << std::endl;

}

Setup::~Setup() {

	//Destroy and Free
	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	Mix_FreeChunk(explodeSFX);
	Mix_FreeChunk(laserSFX);
	Mix_FreeMusic(bkgMusic);

	//Quit SDL
	Mix_CloseAudio();

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();


}

Mix_Music* Setup::getBKGMusic() { return bkgMusic; }
Mix_Chunk* Setup::getLaserSFX() { return laserSFX; }
Mix_Chunk* Setup::getExplodeSFX() { return explodeSFX; }
SDL_Window* Setup::getWindow() { return window; }
SDL_Renderer* Setup::getRenderer() { return renderer; }