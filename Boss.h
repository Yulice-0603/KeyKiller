#pragma once
#include "Actor.h"
#include "SDL.h"

class Boss:public Actor
{
public:
	Boss();
	void  UpdateActor(float deltaTime) override;
	void Draw(SDL_Renderer* renderer);
	int get_hp() { return hp; }
	float get_mBossPosX() { return mBossPos.x; }
	void get_damage(int damage);
	bool dead();
	void get_Random(float r);
	float get_Color() { return Color; }
	void set_Color();
private:
	int hp;
	Vector2 mBossPos;
	int mBossH;
	int mBossDir;
	Vector2 mBossVel;
	float Color;
	float Random;
	int CounterPlus;
	int CounterMin;
	int HpW;
	int HpH;
};
