#include "RectangleCollider.h"

bool RectangleCollider::CheckCollision(Rectangle r1, Rectangle r2)
{
	bool collisionDetected = CheckCollisionRecs(r1, r2); //BUG: If there are more than 2 colliders in the world, this value can get overwritten!

	if (collisionDetected)
	{
		isColliding = collisionDetected;
	}

	return collisionDetected;
}

bool RectangleCollider::GetIsColliding()
{
	if (isColliding != NULL)
	{
		return isColliding;
	}

	return false;
	
}

void RectangleCollider::ResetCollision()
{
	isColliding = false;
}


RectangleCollider::RectangleCollider()
{
	isColliding = false;
}
