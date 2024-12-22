#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>

class Grid
{

public:

	Grid();
	Grid(int width, int height, int tileSize);
	~Grid();

	void InitMap(int width, int height, int tileSize);
	void InitMap();

	bool CheckTile(int x, int y); //Checks if there is an object on that tile
	bool CheckTile(int xy);

	bool verifyTile(int x, int y); //Checks if the tile is within the grid
	bool verifyTile(int xy);

	bool UpdateTile(int x, int y, bool state);

	int GetHeight();
	int GetWidth();

private:
	std::unordered_map<int, bool> map;

	void Cleanup();

	int height;
	int width;
	int tileSize;
};

//NOTE: Convert 2d to 1d: [width * row + column]
//NOTE: Convert 1d to 2d: [(i / w)] [(i % w)]
