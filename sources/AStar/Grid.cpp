#include "Grid.h"

Grid::Grid()
{
	height = 1;
	width = 1;
	tileSize = 1;
}

Grid::Grid(int width, int height, int tileSize)
{
	this->height = height;
	this->width = width;
	this->tileSize = tileSize;
}

Grid::~Grid()
{
	Cleanup();
}

void Grid::InitMap(int width, int height, int tileSize)
{
	this->height = height;
	this->width = width;
	this->tileSize = tileSize;

	//map.reserve(height * width);

	InitMap();	
}

void Grid::InitMap()
{
	int i, j;
	//Sets all of the initial tiles to false;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			//[width * row + column]
			map[width * i + j] = false;
		}
	}
}

bool Grid::CheckTile(int x, int y)
{
	if (!verifyTile(x, y))
	{
		std::cerr << "Tile input was not in the map" << std::endl;
		return true; //returns true because the object should not be able to move to the tile because it does not exist
	}
	else
	{
		return map[width * x + y];
	}
}

bool Grid::CheckTile(int xy)
{
	int x = xy / width;
	int y = xy % width;

	return CheckTile(x, y);
}

bool Grid::verifyTile(int x, int y)
{
	if (x  < 0 || x > width || y  < 0 || y > height)
	{
		//std::cerr << "Tile input was not in the map" << std::endl;
		return false; 
	}
	return true;
}

bool Grid::verifyTile(int xy)
{
	int x = xy / width;
	int y = xy % width;
	return verifyTile(x, y);
}

bool Grid::UpdateTile(int x, int y, bool state)
{
	if (x < 0 || x > width || y < 0 || y > height)
	{
		//std::cerr << "Tile input was not in the map" << std::endl;
		return false; //Fails to update the tile
	}
	else
	{
		map[width * x + y] = state;
	}
}

int Grid::GetHeight()
{
	return height;
}

int Grid::GetWidth()
{
	return width;
}

void Grid::Cleanup()
{

}
