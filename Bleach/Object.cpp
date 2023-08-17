#include "Object.h"
#include "Texture.h"

int nY = 0, posY, pX;
SDL_Rect* current;
int k;
bool right = true;

Player::Player(SDL_Renderer* ren) {
	renderer = ren;
	LoadTexture();

	picX = (Width - PicWidth) / 2;
	picY = Height- PicHeight;
	Go[0] = { 10,130,75,45 };
	Go[1] = { 95,130,75,45 };
	Go[2] = { 175,130,75,45 };
	Go[3] = { 260,130,80,45 };
	Go[4] = { 345,130,75,45 };
	Go[5] = { 430,130,75,45 };
	Go[6] = { 515,130,75,45 };
	Go[7] = { 600,130,75,45 };

	Stay[0] = { 10,45,70,45 };
	Stay[1] = Stay[0];
	Stay[2] = { 85,45,70,45 };
	Stay[3] = Stay[2];
	Stay[4] = { 170,45,70,45 };
	Stay[5] = Stay[4];
	Stay[6] = { 255,45,70,45};
	Stay[7] = Stay[6];

	Defend[0] = { 375,45,60,45 };
	Defend[1] = Defend[0];
	Defend[2] = Defend[0];
	Defend[3] = Defend[0];
	Defend[4] = Defend[0];
	Defend[5] = { 440,30,50,60 };
	Defend[6] = { 498,46,60,45 };

	Jump[0] = { 80,845,55,45 };
	Jump[1] = { 80,845,55,45 };
	Jump[2] = { 80,845,55,45 };
	Jump[3] = { 80,845,55,45 };
	Jump[4] = { 80,845,55,45 };
	Jump[5] = { 80,845,55,45 };
	Jump[6] = { 150,840,50,70 };
	Jump[7] = { 150,840,50,70 };
	Jump[8] = { 150,840,50,70 };

	Attack[0] = { 15,233,45,45 };
	Attack[1] = Attack[0];
	Attack[2] = { 70,233,70,45 };
	Attack[3] = { 140,233,85,45 };
	Attack[4] = Attack[3];
	Attack[5] = { 235,233,45,45 };
	Attack[6] = { 300,233,55,45 };
	Attack[7] = Attack[6];
	Attack[8] = Attack[6];
}
void Player::LoadTexture() {
	PlayerTexture = Texture::LoadTexture("Environment/Ichigo Kurosaki.png", renderer, true);
}
void Player::handleEvent(SDL_Event* e, int& Stay_Fr, int& Run_Fr, int& Defend_Fr, int& Jump_Fr, int& Attack_Fr) {
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_a:
			velX -= picVel;
			go = true;
			Runleft = true;
			break;
		case SDLK_d:
			velX += picVel;
			go = true;
			Runright = true;
			break;
		case SDLK_w:
			if (OnGround && !defend) {
				velY = -15;
				OnGround = false;
			}
			break;
		case SDLK_s:
			if(OnGround) defend = true;
			nY++;
			break;
		case SDLK_j:
			if (OnGround && !defend) Sword = true;
			break;
		}
		if (velX == 0) go = false;
		else if (velX == picVel) FlipType = SDL_FLIP_NONE;
		else FlipType = SDL_FLIP_HORIZONTAL;
		if (nY == 1) {
			posY = picY - 15;
		}
	}
	else if (e->type == SDL_KEYUP && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_a:
			velX += picVel;
			if (velX == 0) go = false;
			else go = true;
			Runleft = false;
			Run_Fr = 0;
			break;
		case SDLK_d:
			velX -= picVel;
			if (velX == 0) go = false;
			else go = true;
			Runright = false;
			Run_Fr = 0;
			break;
		case SDLK_s:
			Defend_Fr = 0;
			nY = 0;
			Dfdown = true;
			defend = false;
			break;
		case SDLK_j:
			Sword = false;
			Attack_Fr = 0;
			break;
		}
		if (!Runleft && velX == picVel) FlipType = SDL_FLIP_NONE;
		if (!Runright && velX == -picVel) FlipType = SDL_FLIP_HORIZONTAL;
	}
	if (FlipType == SDL_FLIP_NONE) right = true;
	else right = false;
}
void Player::MoveLoad(int& frame, Block* Platform[]) {
	picX += velX;
	
	if (picX < 0 || (picX + PicWidth) > Width ) {
		picX -= velX;
	}
	if (!OnGround) {
		picX += velX;
		picY += velY;
		velY += ACCELERATOR;
		SDL_Delay(15);
	}
	if (picX < 0 || (picX + PicWidth) > Width ) {
		picX -= velX;
	}
	if (picY < 0 || (picY + PicHeight) > Height - 25) {
		OnGround = true;
		frame = 0;
		//picY -= velY;
		picY = Height - PicHeight - 25;
	}
	else 
		for (int i = 0; i<5; i++) 
			if (Platform[i]->CheckCollision(picX, picY) && velY > 0) {
				OnGround = true;
				frame = 0;
				picY = Platform[i]->GetRect()->y - 44;
				k = i;
			}
	else {
		if (Platform[k]->CheckOut(picX, picY) && (picY + PicHeight) < Height - 25) OnGround = false;
	}
	frame++;
}
void Player::StayLoad(int& frame, Block* Platform[]) {
	if (!OnGround) {
		picY += velY;
		velY += ACCELERATOR;
		SDL_Delay(15);
	}
	if (picY < 0 || (picY + PicHeight) > Height - 25) {
		OnGround = true;
		frame = 0;
		//picY -= velY;
		picY = Height - PicHeight - 25  ;
	}
	else 
		for (int i = 0; i<5; i++) 
			if (Platform[i]->CheckCollision(picX, picY) && velY > 0) {
				OnGround = true;
				frame = 0;
				picY = Platform[i]->GetRect()->y - 44;
				k = i;
			}
	else {
		if (Platform[k]->CheckOut(picX, picY) && (picY + PicHeight) < Height - 25) OnGround = false;
	}
	frame++;
}

void Player::Makeanimation(int& Stay_Fr, int& Run_Fr, int& Defend_Fr, int& Jump_Fr, int& Attack_Fr, Block* Platform[]) {
	//SDL_Rect* current;
	if (defend) {
		if (nY <= 5) { current = &Defend[nY - 1]; nY++; }
		else current = &Defend[5];
		
		if (current == &Defend[5]) {
			Texture::Render(PlayerTexture, renderer, current, picX, posY, 0, NULL, FlipType);
		}
		else Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
	}
	else if (Dfdown) {
		current = &Defend[6];
		
		Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
		Dfdown = false;
	}
	else if (Sword) {
		current = &Attack[Attack_Fr / AttackFrame];
		Attack_Fr += 1;
		if (current == &Attack[3] || current == &Attack[4])
		{
			if (right) pX = picX - 35;
			else pX = picX + 30;
		}
		else if ((current == &Attack[5]) && (!right)) pX = picX + 30;
		else if ((current == &Attack[2]) && !right) pX = picX + 10;
		else if (!right) pX = picX + 20;
		else pX = picX;
		//std::cout << pX << '\n';
		if (Attack_Fr / AttackFrame >= AttackFrame) {
			Attack_Fr = 0; 
		}
		Texture::Render(PlayerTexture, renderer, current, pX, picY, 0, NULL, FlipType);
	}
	else if (go) {
		if (!OnGround) {
			
			MoveLoad(Jump_Fr,Platform);
			current = &Jump[Jump_Fr / JumpFrame];
			
			if (Jump_Fr / JumpFrame >= JumpFrame) Jump_Fr = 0;
			Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
			//SDL_Delay(15);
		}
		else {
			MoveLoad(Run_Fr,Platform);
			current = &Go[Run_Fr / GoFrame];
			
			if (Run_Fr / GoFrame >= GoFrame) Run_Fr = 0;
			Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
			//SDL_Delay(5);

		}
	}
	else if (!go && !defend && !Dfdown) {
		if (!OnGround) {
			StayLoad(Jump_Fr,Platform);
			current = &Jump[Jump_Fr / JumpFrame];
			
			if (Jump_Fr / JumpFrame >= JumpFrame) Jump_Fr = 0;
			Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
			//SDL_Delay(15);

		}
		else {
			StayLoad(Stay_Fr,Platform);
			current = &Stay[Stay_Fr / StayFrame];
			
			if (Stay_Fr / StayFrame >= StayFrame) Stay_Fr = 0;
			Texture::Render(PlayerTexture, renderer, current, picX, picY, 0, NULL, FlipType);
			//SDL_Delay(5);
		}
	}
}