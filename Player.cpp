#include "Game.h"
#include "Player.h"

Player::Player()
	:mPlayerH(30)
	,hp(700)
	,mPlayerDir(0)
	,mPlayerJump(false)
	,AttackUp(false)
	,AttackDown(false)
	,power(20)
{
	mPlayerPos.x = 640.0f / 2.0f;
	mPlayerPos.y = 400.0f - mPlayerH / 2.0f;
	mPlayerVel.x = 350.0f;
	mPlayerVel.y = 400.0f;
	mAttackRightRange = 0;
	mAttackLeftRange = 0;
	HpW = 100;
	HpH = 10;
}

void Player::UpdateActor(float deltaTime)
{
	mAttackLeftRange = mPlayerPos.x - (mPlayerH / 2.0f) - 10.0f;
	mAttackRightRange = mPlayerPos.x + mPlayerH / 2.0f + 10.0f;
	HpW = hp/7;
	if (mPlayerDir != 0)
	{
		mPlayerPos.x += mPlayerDir * mPlayerVel.x * deltaTime;
		if (mPlayerPos.x < (mPlayerH / 2.0f))
		{
			mPlayerPos.x = mPlayerH / 2.0f;
		}
		else if (mPlayerPos.x > (640.0f - mPlayerH / 2.0f))
		{
			mPlayerPos.x = 640.0f - mPlayerH / 2.0f;
		}
		if (mPlayerPos.y < (mPlayerH / 2.0f))
		{
			mPlayerPos.y = mPlayerH / 2.0f;
		}
	}
	if (mPlayerJump)
	{
		
		float gravity = -15.0f;
		mPlayerVel.y += gravity;
		mPlayerPos.y -= mPlayerVel.y * deltaTime;
		if (mPlayerPos.y >= 400.0f - mPlayerH / 2.0f)
		{
			mPlayerPos.y = 400.0f - mPlayerH / 2.0f;
			mPlayerVel.y = 400.0f;
			mPlayerJump = false;
		}
	}
}

void Player::ProcessKeyboard(const uint8_t* state)
{
	mPlayerDir = 0;
	AttackUp = false;
	AttackDown = false;
	if (state[SDL_SCANCODE_A])
	{
		mPlayerDir -= 1;
	}
	if (state[SDL_SCANCODE_D])
	{
		mPlayerDir += 1;
	}

	if (state[SDL_SCANCODE_SPACE] && (mPlayerPos.y == 400 - mPlayerH / 2))
	{
		mPlayerJump = true;
	}
	if (state[SDL_SCANCODE_UP])
	{
		AttackUp = true;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		AttackDown = true;
	}
	if (state[SDL_SCANCODE_W])
	{
		AttackDown = true;
	}
}

void Player::Draw(SDL_Renderer* renderer)
{
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect player{
		static_cast<int>(mPlayerPos.x - mPlayerH / 2),
		static_cast<int>(mPlayerPos.y - mPlayerH / 2),
		mPlayerH,
		mPlayerH
	};
	SDL_RenderFillRect(renderer, &player);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect HP{
		10,
		440,
		HpW,
		HpH
		
	};
	SDL_RenderFillRect(renderer, &HP);
}

void Player::DoAttackL(EnemyL* enemyl)
{
	if (AttackUp)
	{
		if (enemyl->get_Color() > 0.5)
		{
			enemyl->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
	}
	if (AttackDown)
	{
		if (enemyl->get_Color() <= 0.5)
		{
			enemyl->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
	}
}
void Player::DoAttackR(EnemyR* enemyr)
{
	if (AttackUp)
	{
		if (enemyr->get_Color() > 0.5)
		{
			enemyr->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
	}
	if (AttackDown)
	{
		if (enemyr->get_Color() <= 0.5)
		{
			enemyr->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
		
	}
}
void Player::DoAttackBoss(Boss* boss)
{
	if (AttackUp)
	{
		if (boss->get_Color() == 1)
		{
			boss->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
	}
	if (AttackDown)
	{
		if (boss->get_Color() == 0)
		{
			boss->get_damage(power);
		}
		else
		{
			hp -= 10;
		}
		
	}
}