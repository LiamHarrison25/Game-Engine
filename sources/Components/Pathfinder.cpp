#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
	target = MyTransform(0, 0);
	aStar = nullptr;
	//moveSpeed = DEFAULT_MOVE_SPEED;
}

Pathfinder::Pathfinder(MyTransform transform)
{
	target = transform;
	aStar = nullptr;
	//moveSpeed = DEFAULT_MOVE_SPEED;
}

Pathfinder::Pathfinder(float x, float y)
{
	target = MyTransform{ x, y };
	aStar = nullptr;
	//moveSpeed = DEFAULT_MOVE_SPEED;
}

void Pathfinder::AquireAStarInstance()
{
	aStar = AStar::GetInstance();
	if (aStar == nullptr)
	{
		std::cerr << "AStar does not have an instance\n";
	}
}

void Pathfinder::SetTarget(MyTransform transform)
{
	target = transform;
}

void Pathfinder::SetTarget(float x, float y)
{
	target = MyTransform{ x, y };
}

void Pathfinder::SetTargetX(float x)
{
	target.SetX(x);
}

void Pathfinder::SetTargetY(float y)
{
	target.SetY(y);
}

//void Pathfinder::SetMoveSpeed(float speed)
//{
//	moveSpeed = speed;
//}

MyTransform Pathfinder::GetTarget()
{
	return target;
}

//float Pathfinder::GetMoveSpeed()
//{
//	return moveSpeed;
//}


MyTransform Pathfinder::Update(MyTransform transform)
{
	if (aStar != nullptr && path.size() == 0)
	{
		 path = aStar->CalculatePath(transform, target);
	}
	
	if (path.size() > 0)
	{
		MyTransform nextMove = path.back();
		path.pop_back();
		return nextMove;
	}
	else
	{
		return transform; //fails to generate a path, so it returns itself
	}

}

//void Pathfinder::UpdateThreaded(std::promise<MyTransform>&& promise, MyTransform transform)
//{
//	promise.set_value(Update(transform));
//}
