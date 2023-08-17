#pragma once
#include "Game.h"
#include "Collision.h"

class Player {
public:
	Player(SDL_Renderer* ren);
	//void Update();
	void LoadTexture();
	void handleEvent(SDL_Event* e, int& Stay_Fr, int& Run_Fr, int& Defend_Fr, int& Jump_Fr, int& Attack_Fr);
	void MoveLoad(int& frame, Block* Platform[]);
	void StayLoad(int& frame, Block* Platform[]);
	void Makeanimation(int& Stay_Fr, int& Run_Fr, int& Defend_Fr, int& Jump_Fr, int& Attack_Fr, Block* Platform[]);
private:
	SDL_Rect Go[GoFrame + 1], Stay[StayFrame + 1],
		Defend[DeFendFrame + 1], Jump[JumpFrame + 1], Attack[AttackFrame + 1];
	SDL_Texture* PlayerTexture;
	SDL_Renderer* renderer;
	int picVel = 2, ACCELERATOR = 1;
	int PicWidth = 55;
	int PicHeight = 45;
};
