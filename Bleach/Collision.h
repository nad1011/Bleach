#pragma once
#include "Texture.h"

class Block {
public:
	Block(SDL_Renderer* ren, int x, int y, int w, int h);
	bool CheckCollision(int x,int y);
	bool CheckOut(int x, int y);
	SDL_Rect* GetRect() {
		return &PlatForm;
	}
private:
	SDL_Renderer* renderer;
	SDL_Rect PlatForm;	
};

