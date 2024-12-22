#pragma once

#include "MyComponent.h"
#include "ComponentPool.h"

class MyTransform : public MyComponent
{

public:

	MyTransform();
	MyTransform(float x, float y);
	~MyTransform();

	MyTransform(const MyTransform& obj); //copy contructor

	float GetX();
	float GetY();

	void SetX(float x);
	void SetY(float y);

	std::pair<int, int> ConvertToPair();

	static MyTransform ConvertFromPair(const std::pair<int, int> p);
	static int ConvertToOneD(const int width, const int row, const int column);

	MyTransform ConvertTo2D(int index, int width);

	//Operator overloads

	bool operator == (const MyTransform& t);

	MyTransform operator + (const MyTransform& t);

	bool operator < (const MyTransform& t) const;

	bool operator > (const MyTransform& t);

	bool operator != (const MyTransform& t);

	//static ComponentPool<MyTransform> pool;

private:

	float x;
	float y;
};
