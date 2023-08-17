#include "Texture.h"

SDL_Texture* Texture::LoadTexture(std::string path, SDL_Renderer* ren, bool color) {

	SDL_Texture* newTex = NULL;
	SDL_Surface* loadedSur = IMG_Load(path.c_str());
	if (loadedSur == NULL) {
		std::cout << "Error: Can't load the image!" << std::endl << SDL_GetError() << std::endl;
	}
	else {
		if (color) {
			Uint32 color_key = SDL_MapRGB(loadedSur->format, 7, 121, 141);
			SDL_SetColorKey(loadedSur, SDL_TRUE, color_key);
		}
		newTex = SDL_CreateTextureFromSurface(ren, loadedSur);
		if (newTex == NULL) {
			std::cout << "Error: Can't create texture!" << std::endl << SDL_GetError();
		}
		SDL_FreeSurface(loadedSur);
	}
	return newTex;
}
void Texture::Render(SDL_Texture* Texture, SDL_Renderer* ren, SDL_Rect* Clip, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect *strec) {
	SDL_Rect renderQuad = { x, y,  Clip->w, Clip->h };
	//Render to screen
	if (strec!=nullptr) SDL_RenderCopyEx(ren, Texture, Clip, strec, angle, center, flip);
	else SDL_RenderCopyEx(ren, Texture, Clip, &renderQuad, angle, center, flip);
}