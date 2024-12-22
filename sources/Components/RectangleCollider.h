#pragma once

#include <raylib.h>
#include "MyComponent.h"
#include "MyTransform.h"

//requires MyTransform

class RectangleCollider : public MyComponent
{
public:

	RectangleCollider();

	bool CheckCollision(Rectangle r1, Rectangle r2);

	bool GetIsColliding();

	void ResetCollision();

private:

	bool isColliding;
};
