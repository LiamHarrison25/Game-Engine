#pragma once

#include "ComponentPool.h"
#include "StackAllocator.h"
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include "AStar/AStar.h";

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int POOL_SIZE = 15;
const std::string WORLD_FILE_NAME = "world.txt";
const std::string WORLD_FILE_PATH = "../../../";
const int MAX_COMMENT_SIZE = 256;

#include "GameObject.h"
#include <thread>
#include <future>

class GameManager
{
public:

	static GameManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();

	void Init();
	void Cleanup();

	void DoLoop();

	void ThreadedPathfindCall(std::promise<MyTransform>&& promise, MyTransform transform, Pathfinder* pathfinder);

private:

	GameManager();
	~GameManager();

	void LoadWorld();

	void UpdateWorld();
	void RenderWorld();

	void ClearWorld();
	
	static GameManager* gameManager;

	//GameObjectManager* gameObjectManager;

	std::unordered_map<int, GameObject*> world;

	//Section: ComponentLoading

	typedef void (*ComponentFn)(GameObject* go, GameManager* gm);

	std::unordered_map<int, ComponentFn> componentLoadMap;

	void LoadComponentMap();

	int LoadComponentValue(std::string stream);

	void SaveWorld();

	int objectIDIndex;

	GameObject* CreateNewGameObject();

	void GONewTransform(GameObject* go);
	void GONewColorChanger(GameObject* go);
	void GONewController(GameObject* go);
	void GONewCollider(GameObject* go);
	void GONewRenderer(GameObject* go);
	void GONewPathfinder(GameObject* go);

	MyTransform* CreateNewTransform();
	MyTransform* CreateNewTransform(float x, float y);

	CollisionColorChanger* CreateNewColorChanger();
	CollisionColorChanger* CreateNewColorChanger(Color changedColor, Color defaultColor);

	PlayerController* CreateNewController();

	RectangleCollider* CreateNewCollider();

	RectangleRenderer* CreateNewRenderer();
	RectangleRenderer* CreateNewRenderer(float width, float height, float topLeftX, float topLeftY, Color color);
	RectangleRenderer* CreateNewRenderer(Vector2 dimensions, Vector2 topLeft, Color color);

	Pathfinder* CreateNewPathfinder();
	Pathfinder* CreateNewPathfinder(MyTransform target);

	void SpawnBasicGameObject(MyTransform* playerTransform);

	void DeleteFromWorld(GameObject* go);

	GameObject* GetClosestGO(MyTransform* transform);

	int GetNewObjectID();

	void DebugFrames();

	int* frames;

	RectangleCollider* activeCollisions;

	size_t numCollisions;

	//component pools:

	//NOTE: The pools may need to be static in order for the static functions to access them. 

	//transform
	ComponentPool<MyTransform> transformPool;
	std::vector<MyTransform*> transformList;

	//ComponentPool MyTransform::pool(32);

	//ComponentPool transformPool2(32)

	//TODO: Make these pools static so that they can be accessed by the static GO new component functions

	//collision color changer
	ComponentPool<CollisionColorChanger> colorChangerPool;
	std::vector<CollisionColorChanger*> colorChangerList;

	//player controller
	ComponentPool<PlayerController> controllerPool;
	std::vector<PlayerController*> controllerList;

	//rectangle collider
	ComponentPool<RectangleCollider> colliderPool;
	std::vector<RectangleCollider*> colliderList;

	//rectangle renderer
	ComponentPool<RectangleRenderer> rendererPool;
	std::vector<RectangleRenderer*> rendererList;

	ComponentPool<Pathfinder> pathfinderPool;
	std::vector<Pathfinder*> pathfinderList;
};
