#include "Collision.h"
#include "Object.h"
#include "Texture.h"
int BlockVel = 1;
Block::Block(SDL_Renderer* ren, int x, int y, int w, int h) {
	renderer = ren;
	PlatForm = {x,y,w,h};
}
bool Block::CheckCollision(int x, int y) {
	if (y + 44 <= PlatForm.y) return false;
	if (y + 44 >= PlatForm.y + PlatForm.h) return false;
	if (x + 55 <= PlatForm.x) return false;
	if (x >= PlatForm.x + PlatForm.w) return false;
	return true;
}
bool Block::CheckOut(int x, int y) {
	if (x + 55 <= PlatForm.x) return true;
	if (x >= PlatForm.x + PlatForm.w) return true;
	return false;
}


