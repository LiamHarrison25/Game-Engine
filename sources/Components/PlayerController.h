#pragma once

#include "raylib.h"
#include "MyTransform.h"
#include "MyComponent.h"

const float MOVE_SPEED = 2.0f;

class PlayerController : public MyComponent
{

public:

	PlayerController();
	~PlayerController();

	int Update(MyTransform* transform);

private:

};
