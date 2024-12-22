#pragma once

#include "AStarNode.h"
#include "Grid.h"
#include <unordered_map>
#include <queue>
#include <iostream>
#include <utility>

//#include <thread>
//#include <future>

//TODO: Add singleton behavior to the AStar. This makes sure that it can only be created once, and is only stored in the game manager

class AStar
{
public:

	static AStar* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();

	void InitGrid(int height, int width, int tileSize);

	std::vector<MyTransform> CalculatePath(MyTransform start, MyTransform target); 

	//std::vector<MyTransform> CalculatePathThreaded(MyTransform start, MyTransform target);
private:

	AStar();

	std::vector<MyTransform> GetNeighbors(MyTransform position, const std::unordered_map<int, MyTransform> &cameFrom);

	std::vector<MyTransform> GetNeighbors(std::pair<int, int> pair, const std::unordered_map<int, MyTransform>& cameFrom);

	double heuristic(MyTransform pos, MyTransform target);

	static AStar* aStar;

	Grid* grid;
};

//template<>
//struct std::hash<MyTransform>
//{
//	std::size_t operator()(MyTransform& k) const;
//};

//NOTE: Just for testing:
//template<>
//struct std::hash<std::pair<float, float>>
//{
//	std::size_t operator()(const std::pair<float, float>& k) const
//	{
//		return ((std::hash<float>()(k.first)
//			^ (std::hash<float>()(k.second) << 1)));
//	}
//};