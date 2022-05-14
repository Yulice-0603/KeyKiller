#include "Game.h"
#include <random>
#include "SDL.h"

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, enemygeneration(true)
	, Level(1)
	, Enemycount(0)
	, BossOn(false)
	, GameOn(true)
	,GameOver(false)
{
	allocator = new LinearAllocator(ptr, allocate_size);
}

bool Game::Initialize()
{
	
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	
	mWindow = SDL_CreateWindow(
		"KeyKiller", //ウィンドウのタイトル
		100, //ウィンドウ左上隅のx座標
		100, //ウィンドウ左上隅のy座標
		640, //ウィンドウの幅(width)
		480, //ウィンドウの高さ(height)
		0 //フラグ
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	
	mRenderer = SDL_CreateRenderer(
		mWindow, 
		-1,		 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	Enemy();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	if (GameOn==false)
	{
		if (state[SDL_SCANCODE_RETURN])
		{
			GameOn = true;
		}
	}
	if (GameOver)
	{
		if (state[SDL_SCANCODE_RETURN])
		{
			mIsRunning = false;
		}
	}
	player.ProcessKeyboard(state);
}

void Game::UpdateGame()
{
	
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	
	mTicksCount = SDL_GetTicks();
	if (enemygeneration) 
	{
		Count();
		enemygeneration = false;
	}
	
	player.UpdateActor(deltaTime);
	for (int i = 0; i < Level; i++)
	{
		if (enemyl[i] != nullptr)
		{
			enemyl[i]->UpdateActor(deltaTime);
		}
		if (enemyr[i] != nullptr)
		{
			enemyr[i]->UpdateActor(deltaTime);
		}
	}
	for (int i = 0; i < Level; i++)
	{
		if (enemyl[i] != nullptr)
		{
			if ((player.get_mAttackLeftRange() <= enemyl[i]->get_mEnemyPosX())&& (enemyl[i]->get_mEnemyPosX() <= player.get_mAttackRightRange()))
			{
				player.DoAttackL(enemyl[i]);
			}
			if (enemyl[i]->dead())
			{
				delete enemyl[i];
				Enemycount++;
				enemyl[i] = nullptr;
				
			}
		}
		if (enemyr[i] != nullptr)
		{
			if ((player.get_mAttackLeftRange() <= enemyr[i]->get_mEnemyPosX()) &&(enemyr[i]->get_mEnemyPosX() <= player.get_mAttackRightRange()))
			{
				player.DoAttackR(enemyr[i]);
			}
			if (enemyr[i]->dead())
			{
				delete enemyr[i];
				Enemycount++;
				enemyr[i] = nullptr;
			}
		}
		if ((enemyl[Level - 1] == nullptr) && (enemyr[Level - 1] == nullptr))
		{
			enemygeneration = true;
		}
	}
	if (BossOn)
	{
		boss.UpdateActor(deltaTime);
		if ((player.get_mAttackLeftRange() <= boss.get_mBossPosX()) && (boss.get_mBossPosX() <= player.get_mAttackRightRange()))
		{
			player.DoAttackBoss(&boss);
		}
		if (boss.dead())
		{
			BossOn = false;
			GameOn = false;
			GameOver = true;
		}
	}
	if (player.get_hp()<=0)
	{
		GameOn = false;
		GameOver = true;
	}
	
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer,255,255,255,255);

	SDL_RenderClear(mRenderer);
	
	if (GameOn)
	{
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

		SDL_Rect stage{
			0,
			400,
			640,
			80
		};
		SDL_RenderFillRect(mRenderer, &stage);
		for (int i = 0; i < Level; i++)
		{
			if (enemyl[i] != nullptr)
			{
				enemyl[i]->Draw(mRenderer);
			}
			if (enemyr[i] != nullptr)
			{
				enemyr[i]->Draw(mRenderer);
			}
		}

		if (BossOn)
		{
			std::random_device rd;
			std::default_random_engine eng(rd());
			std::uniform_real_distribution<float> distr(0, 1);
			boss.get_Random(distr(eng));
			boss.Draw(mRenderer);
		}
		player.Draw(mRenderer);
	}
	
	SDL_RenderPresent(mRenderer);
}
void Game::Enemy()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(0, 1);

	for  (int i= 0; i < Level; i++)
	{
		enemyl[i] = new EnemyL(i, distr(eng));
		enemyr[i] = new EnemyR(i, distr(eng));
		allocator->Alloc(sizeof(enemyl[i]));
		allocator->Alloc(sizeof(enemyr[i]));
	}
}



void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
void Game::Count()
{
	
	if (Enemycount==2)
	{
		Level = 2;
		Enemy();
	}
	if (Enemycount == 6)
	{
		Level = 3;
		Enemy();
	}
	if (Enemycount == 12)
	{
		Level = 4;
		Enemy();
	}
	if (Enemycount == 20)
	{
		Level = 5;
		Enemy();
	}
	if (Enemycount == 30)
	{
		Level = 6;
		Enemy();
	}
	if (Enemycount == 42)
	{
		Level = 7;
		Enemy();
	}
	if (Enemycount ==56)
	{
		BossOn = true;
	}
}

