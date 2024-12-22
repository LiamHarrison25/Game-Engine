#pragma once

#include "Components/MyTransform.h"

struct AStarNode
{
	AStarNode()
	{
		position = MyTransform{ 0, 0 };
		priority = 0;
	}

	AStarNode(MyTransform t)
	{
		position = t;
		priority = 0;
	}

	AStarNode(MyTransform t, double p)
	{
		position = t;
		priority = p;
	}

	MyTransform position;
	double priority;

	bool operator<(const AStarNode& other) const
	{
		return priority < other.priority;
	}

};