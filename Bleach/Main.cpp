#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 120;
	const int FrameDelay = 1000 / FPS;
	Uint32 FrameStart;
	int FrameTime;

	game = new Game();
	game->Init(Width, Height);
	game->LoadMedia();
	game->LoadObj();
	while (game->Running()) {
		FrameStart = SDL_GetTicks();
		game->HandleEvent();
		//game->Update();
		game->Render();
		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameDelay > FrameTime) SDL_Delay(FrameDelay - FrameTime);
	}
	game->Clear();
	return 0;
}