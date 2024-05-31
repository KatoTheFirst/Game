#include "Birb.h"
#include<iostream>

void Birb::Render(SDL_Renderer* ren)
{
	animationTimer++;
	if (animationTimer < 16)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer >= 16 && animationTimer <= 32)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer > 32)
	{
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	if (animationTimer > 48)
	{
		animationTimer = 0;
	}
}

int Birb::getYpos()
{
	return Ypos;
}

void Birb::Gravity()
{
	if (JumpState())
	{
		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		jumpHeight = jumpHeight + gravity;
		Ypos = Ypos + gravity + accelerator1 + accelerator2 + jumpHeight;
		setDest(25, Ypos, 28, 38);
		if (jumpHeight > 0)
		{
			inJump = false;
			jumpHeight = -6;
		}
	}
	else
	{

		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		Ypos = Ypos + gravity + accelerator1 + accelerator2;
		setDest(25, Ypos, 28, 38);
	}

}

void Birb::Jump()
{
	if (jumpTimer - lastJump > 50)
	{
		accelerator1 = 0;
		accelerator2 = 0;
		inJump = true;
		lastJump = jumpTimer;
	}
	else
	{
		Gravity();
	}
}

void Birb::GetJumpTime()
{
	jumpTimer = SDL_GetTicks();
}

bool Birb::JumpState()
{
	return inJump;
}

void Birb::Reset()
{
	accelerator1 = 0;
	accelerator2 = 0;
	Ypos = 256;
	lastJump = 0;
}

void Birb::CreateTexture1(const char* address, SDL_Renderer* ren)
{
	Tex1 = TextureManager::LoadTexture(address, ren);
}

void Birb::CreateTexture2(const char* address, SDL_Renderer* ren)
{
	Tex2 = TextureManager::LoadTexture(address, ren);
}