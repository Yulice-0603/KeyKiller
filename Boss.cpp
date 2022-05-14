#include "Game.h"
#include "Boss.h"

Boss::Boss()
	:mBossH(50)
	, hp(4000)
	, mBossDir(1)
	,Color(0)
	,CounterPlus(0)
	,CounterMin(0)
{
	mBossPos.x = 440.0f;
	mBossPos.y = 400.0f - mBossH / 2.0f;
	mBossVel.x = 450.0f;
	mBossVel.y = 400.0f;
	HpW = 200;
	HpH = 20;
	Random = 0;
}

void Boss::UpdateActor(float deltaTime)
{
	HpW = hp / 20;
	if (mBossDir != 0)
	{
		
		mBossPos.x += mBossDir * mBossVel.x * deltaTime;

		if (mBossPos.x < (mBossH / 2.0f))
		{
			mBossPos.x = mBossH / 2.0f;
			mBossDir = 1;
			CounterPlus++;
			CounterMin--;
			set_Color();
		}
		else if (mBossPos.x > (640.0f - mBossH / 2.0f))
		{
			mBossPos.x = 640.0f - mBossH / 2.0f;
			mBossDir = -1;
			CounterPlus++;
			CounterMin--;
			set_Color();
		}
		if (mBossPos.y < (mBossH / 2.0f))
		{
			mBossPos.y = mBossH / 2.0f;
			
		}
		if (CounterPlus==4)
		{
			mBossVel.x = 650.0f;
			CounterMin = 4;
		}
		if (CounterMin==0)
		{
			CounterPlus = 0;
			mBossVel.x = 450.0f;
		}
	}
}

void Boss::Draw(SDL_Renderer* renderer)
{
	if (Color == 1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		SDL_Rect Boss{
			static_cast<int>(mBossPos.x - mBossH / 2),
			static_cast<int>(mBossPos.y - mBossH / 2),
			mBossH,
			mBossH
		};
		SDL_RenderFillRect(renderer, &Boss);
	}
	else if (Color == 0)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_Rect Boss{
			static_cast<int>(mBossPos.x - mBossH / 2),
			static_cast<int>(mBossPos.y - mBossH / 2),
			mBossH,
			mBossH
		};
		SDL_RenderFillRect(renderer, &Boss);
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect HP{
		220,
		420,
		HpW,
		HpH
	};
	SDL_RenderFillRect(renderer, &HP);
	
}

void Boss::get_damage(int damage)
{
	hp -= damage;
}

bool Boss::dead()
{
	if (hp <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Boss::get_Random(float r)
{
	Random = r;
}
void Boss::set_Color()
{
	if (Random>0.5)
	{
		Color = 1;
	}
	else
	{
		Color = 0;
	}
}