#pragma once

struct Vector2
{
	float x;
	float y;
};

class Actor
{
public:
	Actor();
	virtual ~Actor();
	void Update(float deltaTime);
	virtual void  UpdateActor(float deltaTime);

private:
};


