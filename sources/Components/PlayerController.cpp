#include "PlayerController.h"

PlayerController::PlayerController()
{
	
}

PlayerController::~PlayerController()
{

}

int PlayerController::Update(MyTransform* transform)
{
	if (IsKeyDown(KEY_RIGHT))
	{
		transform->SetX(transform->GetX() + MOVE_SPEED);
		return 0;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		transform->SetX(transform->GetX() - MOVE_SPEED);
		return 0;
	}
	else if (IsKeyDown(KEY_UP))
	{
		transform->SetY(transform->GetY() - MOVE_SPEED);
		return 0;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		transform->SetY(transform->GetY() + MOVE_SPEED);
		return 0;
	}
	else if (IsKeyPressed(KEY_SPACE))
	{
		//spawn a game object next to the player
		return 1;
	}
	else if (IsKeyPressed(KEY_D))
	{
		//Delete the game object closest to the player
		return 2;
	}
	else if (IsKeyPressed(KEY_R))
	{
		//TODO: Toggle rapid creation and deletion mode
		return 3;
	}
	else if (IsKeyPressed(KEY_F))
	{
		//TODO: Fill all of the component pools to their max capacity
		return 4;
	}
	else if (IsKeyPressed(KEY_C))
	{
		//TODO: Remove all game objects except for the player, including all of their components
		return 5;
	}
	else if (IsKeyPressed(KEY_M))
	{
		//Saves the world
		return 6;
	}
	
}
