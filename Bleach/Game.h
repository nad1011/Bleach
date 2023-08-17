#pragma once
#ifndef Game_h
#define Game_h
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

static int Width = 1000;
static int Height = 600;
static int picX = 0, picY = 0;
static int velX=0, velY=0;
static bool OnGround = true, Right = true, go = false, Runright = false, 
	Runleft = false, defend = false, Dfdown = false, Sword = false ;
static const int GoFrame = 7, StayFrame = 7, DeFendFrame = 6, JumpFrame = 8, AttackFrame = 8;
static SDL_RendererFlip FlipType = SDL_FLIP_NONE;
static SDL_Rect Scr = { 0,0,Width,Height };
class Game {
public:
	Game();
	~Game();
	void Init(int Wi, int He);
	void LoadMedia();
	void LoadObj();
	void HandleEvent();
	void Update();
	void Render();
	void Clear();
	bool Running() { return isRunning; }
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !Game_h
