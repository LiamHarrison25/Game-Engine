#include "AStar.h"

AStar* AStar::aStar = nullptr;

AStar* AStar::GetInstance()
{
	if (aStar != nullptr)
	{
		return aStar;
	}
}

void AStar::CreateInstance()
{
	if (aStar == nullptr)
	{
		aStar = new AStar();
		//grid = new Grid();
	}
}

void AStar::DestroyInstance()
{
	delete aStar;
	aStar = nullptr;
}

void AStar::InitGrid(int width, int height, int tileSize)
{
	grid = new Grid(width, height, tileSize);
	grid->InitMap();
}

AStar::AStar()
{
	grid = nullptr;
}

std::vector<MyTransform> AStar::CalculatePath(MyTransform start, MyTransform target)
{

	std::priority_queue<MyTransform> frontier; 
	//std::priority_queue<AStarNode> frontier;
	std::unordered_map<int, MyTransform> cameFrom;  //NOTE: First came from second
	std::vector<MyTransform> neighbors;	
	std::unordered_map<int, double> totalCost;

	cameFrom[MyTransform::ConvertToOneD(grid->GetWidth(), start.GetX(), start.GetY())] = start;
	totalCost[MyTransform::ConvertToOneD(grid->GetWidth(), start.GetX(), start.GetY())] = 0; //zero cost at the start


	MyTransform nextMove;

	//AStarNode startA(start, 0);
	//frontier.push(startA);
	frontier.push(start);

	while (!frontier.empty()) //goes through the frontier until it runs out of moves
	{
		MyTransform current = frontier.top(); //MyTransform current = frontier.top().position;
		frontier.pop();

		if (current == target) //Early exit
		{
			nextMove = current;
			break;
		}

		neighbors = GetNeighbors(current, cameFrom);

		for (MyTransform next : neighbors)
		{
			double nextCost = totalCost[MyTransform::ConvertToOneD(grid->GetWidth(), current.GetX(), current.GetY())] + 1;
			totalCost[MyTransform::ConvertToOneD(grid->GetWidth(), next.GetX(), next.GetY())] = nextCost;

			//double priority = nextCost; //+ heuristic(next, target);
			//AStarNode nextA(next, 0);
			//frontier.push(nextA); 
			frontier.push(next);
			cameFrom[MyTransform::ConvertToOneD(grid->GetWidth(), next.GetX(), next.GetY())] = current;
		}
	}

	std::vector<MyTransform> path;

	while (nextMove != start)
	{
		path.push_back(cameFrom[MyTransform::ConvertToOneD(grid->GetWidth(), nextMove.GetX(), nextMove.GetY())]);
		nextMove = cameFrom[MyTransform::ConvertToOneD(grid->GetWidth(), nextMove.GetX(), nextMove.GetY())];
	}

	return path;

	//return start; //NOTE: Temporary
}

//std::vector<MyTransform> AStar::CalculatePathThreaded(MyTransform start, MyTransform target)
//{
//
//	//std::future<std::vector<MyTransform>> result = std::async())
//
//	//std::thread threadObject(CalculatePath(start, target));
//	
//	//threadObject.join();
//
//
//}


std::vector<MyTransform> AStar::GetNeighbors(MyTransform position, const std::unordered_map<int, MyTransform>& cameFrom) //returns the neighbors to the position passed in
{
	std::vector<MyTransform> neighbors;

	MyTransform pos;

	pos.SetX(position.GetX());
	pos.SetY(position.GetY() - 1);

	if (grid->verifyTile(pos.GetX(), pos.GetY()) && !cameFrom.contains(MyTransform::ConvertToOneD(grid->GetWidth(), pos.GetX(), pos.GetY()))) //TODO: cameFrom.contains()
	{
		neighbors.push_back(pos);
	}

	pos.SetX(position.GetX() + 1);
	pos.SetY(position.GetY());
	if (grid->verifyTile(pos.GetX(), pos.GetY()) && !cameFrom.contains(MyTransform::ConvertToOneD(grid->GetWidth(), pos.GetX(), pos.GetY())))
	{
		neighbors.push_back(pos);
	}

	pos.SetX(position.GetX());
	pos.SetY(position.GetY() + 1);
	if (grid->verifyTile(pos.GetX(), pos.GetY()) && !cameFrom.contains(MyTransform::ConvertToOneD(grid->GetWidth(), pos.GetX(), pos.GetY())))
	{
		neighbors.push_back(pos);
	}

	pos.SetX(position.GetX() - 1);
	pos.SetY(position.GetY());
	if (grid->verifyTile(pos.GetX(), pos.GetY()) && !cameFrom.contains(MyTransform::ConvertToOneD(grid->GetWidth(), pos.GetX(), pos.GetY())))
	{
		neighbors.push_back(pos);
	}

	return neighbors;
}

std::vector<MyTransform> AStar::GetNeighbors(std::pair<int, int> pair, const std::unordered_map<int, MyTransform>& cameFrom)
{
	return GetNeighbors(MyTransform::ConvertFromPair(pair), cameFrom);
}

double AStar::heuristic(MyTransform pos, MyTransform target)
{
	return std::abs(pos.GetX() - target.GetX()) + std::abs(pos.GetY() - target.GetY());
}

//std::size_t std::hash<MyTransform>::operator()(MyTransform& k) const //hash function for MyTransform for the unordered_map
//{
//	return ((std::hash<float>()(k.GetX())
//		^ (std::hash<float>()(k.GetY()) << 1)));
//}

//NOTE: Convert 2d to 1d: [width * row + column]
//NOTE: Convert 1d to 2d: [(i / w)] [(i % w)]