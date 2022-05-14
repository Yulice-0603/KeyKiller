#pragma once
#include "Actor.h"
#include "SDL.h"

class EnemyL :public Actor
{
public:
	EnemyL(int n, float c);
	void  UpdateActor(float deltaTime) override;
	void Draw(SDL_Renderer* renderer);
	int get_hp() { return hp; }
	float get_mEnemyPosX() { return mEnemyPos.x; }
	void get_damage(int damage);
	bool dead();
	float get_Color() { return Color; }
private:
	int hp;
	Vector2 mEnemyPos;
	int mEnemyH;
	int mEnemyDir;
	Vector2 mEnemyVel;
	float Color;
};
