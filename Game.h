#pragma once
#include "SDL.h"
#include <vector>
#include "Player.h"
#include "EnemyL.h"
#include "EnemyR.h"
#include "Boss.h"
#include "iMemoryAllocator.h"
#include "LinearAllocator.h"
// Game class
class Game
{
public:
	Game();
	
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void Enemy();
	void Count();
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	
	class Player player;
	EnemyL** enemyl = new EnemyL * [7];
	EnemyR** enemyr = new EnemyR * [7];
	Boss boss;
	bool enemygeneration;
	int Level;
	int Enemycount;
	bool BossOn;
	bool GameOn;
	bool GameOver;
	size_t allocate_size = 1 * 1024 * 1024;
	void* ptr = new char[allocate_size];
	iMemoryAllocator* allocator;
};
