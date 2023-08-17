#pragma once
#include "Game.h"

class Texture {
public:
	static SDL_Texture* LoadTexture(std::string path, SDL_Renderer* ren, bool color = false);
	void static Render(SDL_Texture* Texture, SDL_Renderer* ren, SDL_Rect* Clip, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect* strec = nullptr);
};

