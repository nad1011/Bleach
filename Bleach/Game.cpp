#include "Game.h"
#include "Texture.h"
#include "Object.h"
#include "Collision.h"
int x, y;
int Run_Fr = 0, Stay_Fr = 0, Defend_Fr = 0, Jump_Fr = 0, Attack_Fr = 0;
SDL_Texture* Background;
SDL_Rect Back = { 2,2,320,470 };
bool Down = true;
Player* Bleach;
Block* Platform[5];
Game::Game() {}
Game::~Game() {}

void Game::Init(int Wi, int He) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error: SDL can't be initialized!" << std::endl << SDL_GetError() << std::endl;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!";
	}
	window = SDL_CreateWindow("Bleach!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Wi, He, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Can't create window" << std::endl << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Can't create renderer" << std::endl << SDL_GetError() << std::endl;
	}
	isRunning = true;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int iF = IMG_INIT_PNG;
	if (!(IMG_Init(iF) & iF)) {
		std::cout << "SDL_image could not initialize!" << std::endl << IMG_GetError() << std::endl;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
	}
}
void Game::HandleEvent() {
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT: 
		isRunning = false;
		break;
	default:
		Bleach->handleEvent(&e,Stay_Fr,Run_Fr,Defend_Fr,Jump_Fr,Attack_Fr);
		break;
	}
}
void Game::LoadMedia() {
	Background = Texture::LoadTexture("Environment/Bleach Stage.png", renderer);
}
void Game::LoadObj() {
	Bleach = new Player(renderer);
	Platform[0] = new Block(renderer, 300, 490, 400, 20);
	Platform[1] = new Block(renderer, 0, 408, 1000, 20);
	Platform[2] = new Block(renderer, 0, 327, 200, 20);
	Platform[3] = new Block(renderer, 800, 327, 200, 20);
	Platform[4] = new Block(renderer, 200, 245, 600, 20);
}
void Game::Update() {

}
void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 250, 0, 250, 255);
	SDL_RenderClear(renderer);
	Texture::Render(Background, renderer, &Back, 0, 0, 0, NULL, FlipType, &Scr);
	Bleach->Makeanimation(Stay_Fr, Run_Fr, Defend_Fr, Jump_Fr, Attack_Fr, Platform);
	
	SDL_RenderPresent(renderer);
}
void Game::Clear() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}