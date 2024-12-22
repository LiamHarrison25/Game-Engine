#pragma once

#include "MyTransform.h"
#include "AStar/AStar.h"
//#include <future>

const float DEFAULT_MOVE_SPEED = 2.0f;

class Pathfinder : public MyComponent
{

public:

	Pathfinder();
	Pathfinder(MyTransform transform);
	Pathfinder(float x, float y);

	void AquireAStarInstance();

	void SetTarget(MyTransform transform);
	void SetTarget(float x, float y);
	void SetTargetX(float x);
	void SetTargetY(float y);
	//void SetMoveSpeed(float speed);

	MyTransform GetTarget();
	//float GetMoveSpeed();

	MyTransform Update(MyTransform transform);
	//void UpdateThreaded(std::promise<MyTransform>&& promise, MyTransform transform);

private:
	MyTransform target; 
	AStar* aStar;
	std::vector<MyTransform> path;
	//float moveSpeed;

};