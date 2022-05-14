#include "Game.h"
#include "EnemyL.h"

EnemyL::EnemyL(int n, float c)
	:mEnemyH(30)
	, hp(10)
	, mEnemyDir(0)
{
	Color = c;
	mEnemyPos.x = mEnemyH+40.0f * n;
	mEnemyPos.y = 400.0f - mEnemyH / 2.0f;
	mEnemyVel.x = 200.0f;
	mEnemyVel.y = 200.0f;
}

void EnemyL::UpdateActor(float deltaTime)
{
	if (mEnemyDir != 0)
	{
		mEnemyPos.x += mEnemyDir * mEnemyVel.x * deltaTime;
		
		if (mEnemyPos.x < (mEnemyH / 2.0f))
		{
			mEnemyPos.x = mEnemyH / 2.0f;
		}
		else if (mEnemyPos.x > (640.0f - mEnemyH / 2.0f))
		{
			mEnemyPos.x = 640.0f - mEnemyH / 2.0f;
		}
		if (mEnemyPos.y < (mEnemyH / 2.0f))
		{
			mEnemyPos.y = mEnemyH / 2.0f;
		}
	}
}

void EnemyL::Draw(SDL_Renderer* renderer)
{
	if (Color>0.5)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		SDL_Rect Enemy{
			static_cast<int>(mEnemyPos.x - mEnemyH / 2),
			static_cast<int>(mEnemyPos.y - mEnemyH / 2),
			mEnemyH,
			mEnemyH
		};
		SDL_RenderFillRect(renderer, &Enemy);
	}
	if (Color<=0.5)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_Rect Enemy{
			static_cast<int>(mEnemyPos.x - mEnemyH / 2),
			static_cast<int>(mEnemyPos.y - mEnemyH / 2),
			mEnemyH,
			mEnemyH
		};
		SDL_RenderFillRect(renderer, &Enemy);
	}

}

void EnemyL::get_damage(int damage)
{
	hp -= damage;
}

bool EnemyL::dead()
{
	if (hp<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}