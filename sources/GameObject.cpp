#include "GameObject.h"

GameObject::GameObject()
{
	Init();
}

GameObject::~GameObject()
{
	Cleanup();
}


void GameObject::Init()
{
	renderer = NULL;
	collider = NULL;
	controller = NULL;
	colorChanger = NULL;
	transform = NULL;
	pathfinder = NULL;
}

void GameObject::Update()
{

	if (colorChanger != nullptr && renderer != nullptr)
	{
		bool stateChanged = colorChanger->Update(collider->GetIsColliding());

		if (stateChanged)
		{
			if (colorChanger->GetIsDefaultColor())
			{
				renderer->SetColor(colorChanger->GetDefaultColor());

			}
			else
			{
				renderer->SetColor(colorChanger->GetChangedColor());
			}
		}
	}

	if (controller != nullptr && transform != nullptr)
	{
		controller->Update(transform);
	}
}

void GameObject::Cleanup() //TODO: May not need this function. These should be getting deleted by the 
{
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}

	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}

	if (controller != nullptr)
	{
		delete controller;
		controller = nullptr;
	}

	if (colorChanger != nullptr)
	{
		delete colorChanger;
		colorChanger = nullptr;
	}

	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}

	if (pathfinder != nullptr)
	{
		delete pathfinder;
		pathfinder = nullptr;
	}
}

int GameObject::GetObjectID()
{
	return objectID;
}

void GameObject::SetObjectID(int objectID)
{
	this->objectID = objectID;

	if (renderer != NULL)
	{
		renderer->SetGameObjectID(objectID);
	}

	if (collider != NULL)
	{
		collider->SetGameObjectID(objectID);
	}

	if (controller != NULL)
	{
		controller->SetGameObjectID(objectID);
	}

	if (colorChanger != NULL)
	{
		colorChanger->SetGameObjectID(objectID);
	}

	if (transform != NULL)
	{
		transform->SetGameObjectID(objectID);
	}

	if (pathfinder != NULL)
	{
		pathfinder->SetGameObjectID(objectID);
	}
}

void GameObject::SetRenderer(RectangleRenderer* rect)
{
	this->renderer = rect;
}

void GameObject::SetCollider(RectangleCollider* col)
{
	this->collider = col;
}

void GameObject::SetController(PlayerController* con)
{
	this->controller = con;
}

void GameObject::SetColorChanger(CollisionColorChanger* colChange)
{
	this->colorChanger = colChange;
}

void GameObject::SetTransform(MyTransform* transform)
{
	this->transform = transform;
}

void GameObject::SetPathfinder(Pathfinder* pathfinder)
{
	this->pathfinder = pathfinder;
}

RectangleRenderer* GameObject::GetRenderer()
{
	if (renderer == nullptr)
	{
		return NULL;
	}

	return renderer;
}

RectangleCollider* GameObject::GetCollider()
{
	if (collider == nullptr)
	{
		return NULL;
	}

	return collider;
}

PlayerController* GameObject::GetPlayerController()
{
	if (controller == nullptr)
	{
		return NULL;
	}

	return controller;
}

CollisionColorChanger* GameObject::GetCollisionColorChanger()
{
	if (colorChanger == nullptr)
	{
		return NULL;
	}

	return colorChanger;
}

MyTransform* GameObject::GetTransform()
{
	if(transform == nullptr)
	{
		return NULL;
	}

	return transform;
}

Pathfinder* GameObject::GetPathfinder()
{
	if (pathfinder == nullptr)
	{
		return NULL;
	}

	return pathfinder;
}
