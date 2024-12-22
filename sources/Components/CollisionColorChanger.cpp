#include "CollisionColorChanger.h"

CollisionColorChanger::CollisionColorChanger()
{
	changedColor = Color{ 0, 0, 0, 0 };
	defaultColor = Color{ 0, 0, 0, 0 };
	isDefaultColor = true;
	lastState = 0;
}

CollisionColorChanger::CollisionColorChanger(Color changedColor, Color defaultColor)
{
	this->changedColor = changedColor;
	this->defaultColor = defaultColor;
	isDefaultColor = true;
	lastState = 0;
}

CollisionColorChanger::~CollisionColorChanger()
{

}

bool CollisionColorChanger::Update(bool isColliding)
{
	if (isColliding)
	{
		if (lastState == 0)
		{
			lastState = 1;
			isDefaultColor = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (lastState == 1)
		{
			lastState = 0;
			isDefaultColor = true;
			return true;
		}
		else
		{
			
		}
	}
}

void CollisionColorChanger::SetChangedColor(Color color)
{
	changedColor = color;
}

void CollisionColorChanger::SetChangedR(float r)
{
	changedColor.r = r;
}

void CollisionColorChanger::SetChangedG(float g)
{
	changedColor.g = g;
}

void CollisionColorChanger::SetChangedB(float b)
{
	changedColor.b = b;
}

void CollisionColorChanger::SetChangedA(float a)
{
	changedColor.a = a;
}

Color CollisionColorChanger::GetChangedColor()
{
	return changedColor;
}

bool CollisionColorChanger::GetIsDefaultColor()
{
	return isDefaultColor;
}

void CollisionColorChanger::SetDefaultColor(Color color)
{
	defaultColor = color;
}

Color CollisionColorChanger::GetDefaultColor()
{
	return defaultColor;
}
