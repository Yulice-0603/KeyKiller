#pragma once
#include "Actor.h"
#include "EnemyL.h"
#include "EnemyR.h"
#include "Boss.h"
#include "SDL.h"

class Player :public Actor
{
public:
	Player();
	void  UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	void Draw(SDL_Renderer* renderer);
	int get_hp() { return hp; }
	void DoAttackL(EnemyL* enemyl);
	void DoAttackR(EnemyR* enemyr);
	void DoAttackBoss(Boss* boss);
	float get_mAttackRightRange() { return mAttackRightRange; }
	float get_mAttackLeftRange() { return mAttackLeftRange; }
private:
	int hp;
	Vector2 mPlayerPos;
	int mPlayerH;
	int mPlayerDir;
	Vector2 mPlayerVel;
	bool mPlayerJump;
	bool AttackUp;
	bool AttackDown;
	float mAttackRightRange;
	float mAttackLeftRange;
	const int power;
	int HpW;
	int HpH;
};



