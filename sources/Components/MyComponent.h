#pragma once

//#include "ComponentPool.h"

//const enum ComponentType
//{
//	IDtransform, IDplayerController, IDrectangleCollider, IDrectangleRenderer, IDcollisionColorChanger
//};

class MyComponent
{
public:

	//MyComponent() = default;

	int GetGameObjectID();

	void SetGameObjectID(int id);

protected: 
	int gameObjectID;
};