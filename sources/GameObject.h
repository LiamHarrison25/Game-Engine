#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "Components/RectangleRenderer.h"
#include "Components/RectangleCollider.h"
#include "Components/PlayerController.h"
#include "Components/CollisionColorChanger.h"
#include "Components/Pathfinder.h"

#include <vector>

class GameObject
{
public:

	GameObject();
	~GameObject();

	void Init();
	void Cleanup();
	void Update();

	int GetObjectID();

	void SetObjectID(int objectID);

	void SetRenderer(RectangleRenderer* rect);
	void SetCollider(RectangleCollider* col);
	void SetController(PlayerController* con);
	void SetColorChanger(CollisionColorChanger* colChange);
	void SetTransform(MyTransform* transform);
	void SetPathfinder(Pathfinder* pathfinder);

	RectangleRenderer* GetRenderer();
	RectangleCollider* GetCollider();
	PlayerController* GetPlayerController();
	CollisionColorChanger* GetCollisionColorChanger();
	MyTransform* GetTransform();
	Pathfinder* GetPathfinder();

protected:

	int objectID;

	RectangleRenderer* renderer;
	RectangleCollider* collider;
	PlayerController* controller;
	CollisionColorChanger* colorChanger;
	MyTransform* transform;
	Pathfinder* pathfinder;

};
