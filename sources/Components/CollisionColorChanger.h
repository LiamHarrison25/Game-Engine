#pragma once

#include "raylib.h"
#include "MyComponent.h"

//requires MyTransform, RectangleRenderer, RectangleCollider

class CollisionColorChanger : public MyComponent
{
public:

	CollisionColorChanger();
	CollisionColorChanger(Color color, Color defaultColor);
	~CollisionColorChanger();

	bool Update(bool isColliding);

	void SetChangedColor(Color color);
	void SetChangedR(float r);
	void SetChangedG(float g);
	void SetChangedB(float b);
	void SetChangedA(float a);
	Color GetChangedColor();
	bool GetIsDefaultColor();

	void SetDefaultColor(Color color);
	Color GetDefaultColor();

private:

	Color changedColor;
	Color defaultColor;
	bool isDefaultColor;
	int lastState;

};
