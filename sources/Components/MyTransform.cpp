#include "MyTransform.h"


MyTransform::MyTransform()
{
	x = 0, y = 0;
}

MyTransform::MyTransform(float x, float y)
{
	this->x = x;
	this->y = y;
}

MyTransform::~MyTransform()
{
	this->x = 0;
	this->y = 0;
}

MyTransform::MyTransform(const MyTransform& obj)
{
	this->x = obj.x;
	this->y = obj.y;
}

float MyTransform::GetX()
{
	return x;
}

float MyTransform::GetY()
{
	return y;
}

void MyTransform::SetX(float x)
{
	this->x = x;
}

void MyTransform::SetY(float y)
{
	this->y = y;
}

std::pair<int, int> MyTransform::ConvertToPair()
{
	std::pair<int, int> pair;
	pair.first = this->GetX();
	pair.second = this->GetY();
	return pair;
}

MyTransform MyTransform::ConvertFromPair(const std::pair<int, int> p)
{
	MyTransform transform;
	transform.SetX(p.first);
	transform.SetY(p.second);
	return transform;
}

int MyTransform::ConvertToOneD(const int width, const int row, const int column)
{
	return width * row + column;
}

MyTransform MyTransform::ConvertTo2D(int index, int width)
{
	MyTransform transform;
	transform.SetX(index / width);
	transform.SetY(index % width);
	return transform;
}

//NOTE: Convert 2d to 1d: [width * row + column]
//NOTE: Convert 1d to 2d: [(i / w)] [(i % w)]

//Operator overloads

bool MyTransform::operator == (const MyTransform& t)
{
	if (x == t.x && y == t.y)
	{
		return true;
	}
	return false;
}

MyTransform MyTransform::operator + (const MyTransform& t)
{
	MyTransform sum;
	sum.SetX(x + t.x);
	sum.SetY(y + t.y);
	return sum;
}

bool MyTransform::operator < (const MyTransform& t) const
{
	if (x < t.x && y < t.y)
	{
		return true;
	}
	return false;
}

bool MyTransform::operator > (const MyTransform& t)
{
	if (x > t.x && y > t.y)
	{
		return true;
	}
	return false;
}

bool MyTransform::operator != (const MyTransform& t)
{
	if (x != t.x || y != t.y)
	{
		return true;
	}

	return false;
}

