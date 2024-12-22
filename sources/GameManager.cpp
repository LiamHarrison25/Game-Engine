#include "GameManager.h"

const int MAX_COMPONENTS = 20;

GameManager* GameManager::gameManager = nullptr;

GameManager* GameManager::GetInstance()
{
	if (gameManager != nullptr)
	{
		return gameManager;
	}
}

void GameManager::CreateInstance()
{
	if (gameManager == nullptr)
	{
		gameManager = new GameManager;

		//GameManager::transformPool.SetSize(MAX_COMPONENTS);
		//GameManager::transformList.reserve(MAX_COMPONENTS);
	}
}

void GameManager::DestroyInstance()
{
	delete gameManager;
	gameManager = nullptr;
}

void GameManager::Init()
{
	//aStar = new AStar(SCREEN_HEIGHT, SCREEN_WIDTH, 1);

	AStar::CreateInstance();
	AStar* aStar = AStar::GetInstance();
	aStar->InitGrid(SCREEN_WIDTH, SCREEN_HEIGHT, 1);

	objectIDIndex = 0;

	transformPool.SetSize(MAX_COMPONENTS);
	colorChangerPool.SetSize(MAX_COMPONENTS);
	controllerPool.SetSize(MAX_COMPONENTS);
	colliderPool.SetSize(MAX_COMPONENTS);
	rendererPool.SetSize(MAX_COMPONENTS);
	pathfinderPool.SetSize(MAX_COMPONENTS);

	//Background

	//GameObject* background = new GameObject;
	//background->SetObjectID(GetNewObjectID());
	GameObject* background = CreateNewGameObject();

	background->SetTransform(CreateNewTransform(0, 0));
	background->GetTransform()->SetGameObjectID(background->GetObjectID());

	//background->SetRenderer(CreateNewRenderer(13000, 8000, -6000, 0, Color{ 0, 50, 25, 255 }));
	background->SetRenderer(CreateNewRenderer(Vector2{ 13000, 8000 }, Vector2{ -6000, 0 }, Color{ 0, 50, 25, 255 }));
	background->GetRenderer()->SetGameObjectID(background->GetObjectID());

	//world.emplace(background->GetObjectID(), background);

	//Player

	//GameObject* player = new GameObject;
	//player->SetObjectID(GetNewObjectID());

	GameObject* player = CreateNewGameObject();

	player->SetTransform(CreateNewTransform(400, 280));
	player->GetTransform()->SetGameObjectID(player->GetObjectID());

	player->SetCollider(CreateNewCollider());
	player->GetCollider()->SetGameObjectID(player->GetObjectID());

	player->SetController(CreateNewController());
	player->GetPlayerController()->SetGameObjectID(player->GetObjectID());

	//player->SetRenderer(CreateNewRenderer(40, 40, 400, 280, Color{ 0, 100, 255, 255 }));
	player->SetRenderer(CreateNewRenderer(Vector2{ 40, 40 }, Vector2{ 400, 280 }, Color{ 0, 100, 255, 255 }));
	player->GetRenderer()->SetGameObjectID(player->GetObjectID());

	player->SetColorChanger(CreateNewColorChanger(Color{ 255, 0, 0, 255 }, Color{ 0, 100, 255, 255 }));
	player->GetCollisionColorChanger()->SetGameObjectID(player->GetObjectID());

	LoadWorld();

	//world.emplace(player->GetObjectID(), player);
}

void GameManager::Cleanup()
{
	ClearWorld();
	componentLoadMap.clear();
}

void GameManager::DoLoop()
{
	int frameNumber = 0;

	float targetTime = 16.67;

	while (!WindowShouldClose())
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		BeginDrawing();

		ClearBackground(RAYWHITE);

		//Create frame allocators

		StackAllocator frameAllocator;

		frames = frameAllocator.Alloc<int>();

		activeCollisions = (RectangleCollider*)frameAllocator.GetCurrentHead();
		numCollisions = 0;

		int i;
		for (i = 0; i < colliderList.size(); i++)
		{
			if (colliderList[i]->GetIsColliding()) //if that collider is currently colliding
			{
				frameAllocator.Alloc<RectangleCollider*>(colliderList[i]); //TODO: Fix this so that it can allocate properly
				numCollisions++;
			}
		}

		//std::cout << "NUM Collisions during this frame: " << numCollisions << std::endl;

		UpdateWorld();
		RenderWorld();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		*frames = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

		DebugFrames();
		//DrawText(TextFormat("Frame: %08i", *frames), 200, 80, 20, RED);

		//Delete frame allocators

		frameAllocator.Reset();

		//NO use after free bugs!!!!
		frames = nullptr;
		activeCollisions = nullptr;

		EndDrawing();
	}
}

void GameManager::LoadWorld()
{
	//LoadComponentMap();

	std::fstream file;
	file.open(WORLD_FILE_PATH + WORLD_FILE_NAME); //NOTE: file must be placed in the out folder

	if (file.is_open() && file.good())
	{
		char input = 0;
		std::string inputStream;

		std::string previousInput;

		bool writingToComponent = false;
		//int currentLayer = 0;

		GameObject* currentGO = nullptr;

		int currentComponent = 0;

		//ComponentTypes currentComponentType; 

		while (!file.eof())
		{
			file >> input;
			if (input == '*')
			{
				file.ignore(MAX_COMMENT_SIZE, '*'); //NOTE: This is used to create comments within the file
			}
			else if (writingToComponent && inputStream.size() >= 2 && input == ';') //checks to see if it is reading in component values and if the input stream contains a value
			{
				switch (currentComponent)
				{
				case 0: //MyTransform
					switch (inputStream[0])
					{
					case 'x':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetTransform()->SetX(value);
						printf("Setting x value on the transform to: %i \n", value);
						break;
					}
					case 'y':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetTransform()->SetY(value);
						printf("Setting y value on the transform to: %i \n", value);
						break;
					}
					break;
					}					
				case 1: //RectangleRenderer
					if (currentGO->GetRenderer() == nullptr) //NOTE: Ensures that the renderer is not null when trying to add values to it
					{
						break;
					}
					switch (inputStream[0])
					{
					case 'w':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetWidth(value);
						printf("Setting w value on the renderer to: %i \n", value);
						break;
					}
					case 'h':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetHeight(value);
						printf("Setting h value on the renderer to: %i \n", value);
						break;
					}
					case 'x':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetTopLeftX(value);
						printf("Setting x value on the renderer to: %i \n", value);
						break;
					}
					case 'y': 
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetTopLeftY(value);
						printf("Setting y value on the renderer to: %i \n", value);
						break;
					}
					case 'r':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetR(value);
						printf("Setting r value on the renderer to: %i \n", value);
						break;
					}
					case 'g':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetG(value);
						printf("Setting g value on the renderer to: %i \n", value);
						break;
					}
					case 'b':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetB(value);
						printf("Setting b value on the renderer to: %i \n", value);
						break;
					}
					case 'a':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetRenderer()->SetA(value);
						printf("Setting a value on the renderer to: %i \n", value);
						break;
					}						
					}
					break;
				case 2: //RectangleCollider
					break;
				case 3: //PlayerController
					break;
				case 4: //CollisionColorChanger
					if (currentGO->GetRenderer() == nullptr || currentGO->GetCollisionColorChanger() == nullptr) //NOTE: Ensures that the color changer is not null when trying to add values to it
					{
						break;
					}
					switch (inputStream[0])
					{
					case 'r':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetCollisionColorChanger()->SetChangedR(value);
						printf("Setting r value on the color changer to: %i \n", value);
						break;
					}
					case 'g':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetCollisionColorChanger()->SetChangedG(value);
						printf("Setting g value on the color changer to: %i \n", value);
						break;
					}
					case 'b':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetCollisionColorChanger()->SetChangedB(value);
						printf("Setting b value on the color changer to: %i \n", value);
						break;
					}
					case 'a':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetCollisionColorChanger()->SetChangedA(value);
						printf("Setting a value on the color changer to: %i \n", value);
						break;
					}
					}
					break;
				case 5: //Pathfinder
					if (currentGO->GetPathfinder() == nullptr)
					{
						break;
					}
					switch (inputStream[0])
					{
					case 'x':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetPathfinder()->SetTargetX(value);
						printf("Setting x value on the target for the pathfinder to: %i \n", value);
						break;
					}
					case 'y':
					{
						int value = LoadComponentValue(inputStream);
						currentGO->GetPathfinder()->SetTargetY(value);
						printf("Setting y value on the target for the pathfinder to: %i \n", value);
						break;
					}
					}
					break;
				}

				inputStream = "";
				continue;
			}
			else
			{
				//TODO: Create a file input system that can read and understand the format

				if (input == '(' || input == ')' || input == '{' || input == '}')
				{
					if (input == '}') //Ensures that it turns off the component loading when a component has been fully loaded. 
					{
						writingToComponent = false;
						//previousInput = "";
					}

					if (inputStream == "gameobject" && !writingToComponent)
					{
						//currentLayer = 1;
						printf("\nCreating new GameObject\n");
						currentGO = CreateNewGameObject();
						previousInput = inputStream;

					}
					else if (inputStream == "component" && !writingToComponent)
					{
						//currentLayer = 2;
						printf("\nCreating new component\n");

						previousInput = inputStream;
					}
					else
					{
						//componentLoadMap[0](newGO); //BUG: Exception thrown: Read access violation
						//componentLoadMap[3](newGO);

						//auto iter = componentLoadMap.find(0);
						//if (iter != componentLoadMap.end())
						//{
						//	//(*iter->second)(newGO);	
						//}

						//NOTE: Using a switch for now to get it working:

						if (previousInput == "component")
						{
							int id = std::atoi(inputStream.c_str());

							currentComponent = id;

							if (currentGO != nullptr)
							{
								switch (id)
								{
								case 0: //MyTransform
									printf("\nCreating a transform component on the gameobject\n");
									GONewTransform(currentGO);
									
									break;
								case 1: //RectangleRenderer
									printf("\nCreating a rectangle render component on the gameobject\n");
									GONewRenderer(currentGO);
									/*currentGO->GetRenderer()->SetColor(Color{ 255, 0, 255, 255 });
									currentGO->GetRenderer()->SetHeight(40);
									currentGO->GetRenderer()->SetWidth(40);
									*/
									//currentGO->GetRenderer()->SetTopLeftX(400);
									//currentGO->GetRenderer()->SetTopLeftY(800);
									break;
								case 2: //RectangleCollider
									printf("\nCreating a rectangle collider component on the gameobject\n");
									GONewCollider(currentGO);
									break;
								case 3: //PlayerController
									printf("\nCreating a player controller component on the gameobject\n");
									GONewController(currentGO);
									break;
								case 4: //CollisionColorChanger
									printf("\nCreating a collision color changer component on the gameobject\n");
									GONewColorChanger(currentGO);
									currentGO->GetCollisionColorChanger()->SetDefaultColor(currentGO->GetRenderer()->GetColor());
									break;
								case 5: //Pathfinder
									printf("\nCreating a pathfinder component on the gameobject\n");
									GONewPathfinder(currentGO);
									break;
								default:
									printf("\nComponent ID does not exist\n");
									break;
								}
							}

							writingToComponent = true;
						}
						else
						{
							//previous input was not important for this iteration. 
						}

						previousInput = inputStream;
					}
					
					inputStream = "";
					continue;
				}
				

				inputStream.push_back(input);

				printf("Input from file: %c\n", input);
			}
		}
	}

	file.close();
}

void GameManager::LoadComponentMap()
{
	//NOTE: Loads in function pointers to the map
	
	//TODO: Make the ID's immutable!
	//componentLoadMap[0] = GameManager::GetInstance()->GONewTransform;
	//componentLoadMap[1] = GameManager::GetInstance()->GONewCollider;
	//componentLoadMap[2] = GameManager::GetInstance()->GONewController;
	//componentLoadMap[3] = GameManager::GetInstance()->GONewRenderer;
	//componentLoadMap[4] = GameManager::GetInstance()->GONewColorChanger;
}

int GameManager::LoadComponentValue(std::string stream)
{
	stream.erase(0, 1); //erases the first value in the stream
	//inputStream.erase(inputStream.size() - 1);
	return std::atoi(stream.c_str());
}

void GameManager::SaveWorld()
{

	if (world.size() <= 1) //ensures that nothing will be saved if only the player and background are in the world
	{
		return;
	}

	std::ofstream file(WORLD_FILE_PATH + WORLD_FILE_NAME); //NOTE: file must be placed in the out folder

	if (file.is_open() && file.good())
	{

		int i;
		for (i = 3; i <= world.size(); i++) //Loops through the world, and generate a file with the data
		{
			file << "gameobject\n";
			file << "{";

			if (world[i]->GetTransform() != nullptr)
			{
				file << "\tcomponent(";
				file << "0)\n";
				file << "\t{\n";

				//Component values:
				file << "\tx";
				file << world[i]->GetTransform()->GetX();
				file << ";\n";

				file << "\ty";
				file << world[i]->GetTransform()->GetY();
				file << ";\n";

				file << "\t}\n";

			}

			if (world[i]->GetRenderer() != nullptr)
			{
				bool changedColor = false;
				
				if (world[i]->GetCollisionColorChanger() && world[i]->GetCollider()->GetIsColliding()) //Checks to see if a color changing object is currently changed
				{
					world[i]->GetRenderer()->SetColor(world[i]->GetCollisionColorChanger()->GetDefaultColor()); //Ensures that the default color of the renderer will be saved
					changedColor = true;
				}

				file << "\tcomponent(";
				file << "1)\n";
				file << "\t{\n";

				//Component values:

				file << "\tw";
				file << world[i]->GetRenderer()->GetWidth();
				file << ";\n";

				file << "\th";
				file << world[i]->GetRenderer()->GetHeight();
				file << ";\n";

				file << "\tx";
				file << world[i]->GetRenderer()->GetTopLeftX();
				file << ";\n";

				file << "\ty";
				file << world[i]->GetRenderer()->GetTopLeftY();
				file << ";\n";

				Color color = world[i]->GetRenderer()->GetColor();

				file << "\tr";
				file << int(color.r);
				file << ";\n";

				file << "\tg";
				file << int(color.g);
				file << ";\n";

				file << "\tb";
				file << int(color.b);
				file << ";\n";

				file << "\ta";
				file << int(color.a);
				file << ";\n";

				file << "\t}\n";

				if (changedColor)
				{
					world[i]->GetRenderer()->SetColor(world[i]->GetCollisionColorChanger()->GetChangedColor()); //Resets the color back to what it's suppost to display on the screen. 
				}
			}

			if (world[i]->GetCollider() != nullptr)
			{
				file << "\tcomponent(";
				file << "2)\n";
				file << "\t{\n";

				file << "\t}\n";
			}

			if (world[i]->GetPlayerController() != nullptr)
			{
				file << "\tcomponent(";
				file << "3)\n";
				file << "\t{\n";

				file << "\t}\n";
			}

			if (world[i]->GetCollisionColorChanger() != nullptr)
			{
				file << "\tcomponent(";
				file << "4)\n";
				file << "\t{\n";

				//Component values:

				Color color = world[i]->GetCollisionColorChanger()->GetChangedColor();

				file << "\tr";
				file << int(color.r);
				file << ";\n";

				file << "\tg";
				file << int(color.g);
				file << ";\n";

				file << "\tb";
				file << int(color.b);
				file << ";\n";

				file << "\ta";
				file << int(color.a);
				file << ";\n";

				file << "\t}\n";
			}

			if (world[i]->GetPathfinder() != nullptr)
			{
				file << "\tcomponent(";
				file << "5)\n";
				file << "\t{\n";

				//Component values:

				file << "\tx";
				file << world[i]->GetPathfinder()->GetTarget().GetX();
				file << ";\n";

				file << "\ty";
				file << world[i]->GetPathfinder()->GetTarget().GetY();
				file << ";\n";

				file << "\t}\n";
			}

			file << "}\n";
		}
		file.close();
	}
}

GameObject* GameManager::CreateNewGameObject()
{
	GameObject* newGO = new GameObject();
	newGO->SetObjectID(GetNewObjectID());
	world.emplace(newGO->GetObjectID(), newGO);
	return newGO;
}

void GameManager::GONewTransform(GameObject* go)
{
	go->SetTransform(CreateNewTransform());
	go->GetTransform()->SetGameObjectID(go->GetObjectID());
}

void GameManager::GONewColorChanger(GameObject* go)
{
	go->SetColorChanger(CreateNewColorChanger());
	go->GetCollisionColorChanger()->SetGameObjectID(go->GetObjectID());
}

void GameManager::GONewController(GameObject* go)
{
	go->SetController(CreateNewController());
	go->GetPlayerController()->SetGameObjectID(go->GetObjectID());
}

void GameManager::GONewCollider(GameObject* go)
{
	go->SetCollider(CreateNewCollider());
	go->GetCollider()->SetGameObjectID(go->GetObjectID());
}

void GameManager::GONewRenderer(GameObject* go)
{
	go->SetRenderer(CreateNewRenderer());
	go->GetRenderer()->SetGameObjectID(go->GetObjectID());
}

void GameManager::GONewPathfinder(GameObject* go)
{
	go->SetPathfinder(CreateNewPathfinder());
	go->GetPathfinder()->SetGameObjectID(go->GetObjectID());
	go->GetPathfinder()->AquireAStarInstance();
}

void GameManager::UpdateWorld()
{
	int i;

	//Variables for threading
	
	std::vector<std::thread> threadList;
	std::vector<GameObject*> gameObjectList;
	std::vector<std::promise<MyTransform>> promiseList;
	std::vector<std::future<MyTransform>> futureList;
	
	unsigned int availableThreads = std::thread::hardware_concurrency();

	/*if (availableThreads > 1)
	{
		threadList.reserve(availableThreads - 1);
		gameObjectList.reserve(availableThreads - 1);
		futureList.reserve(availableThreads - 1);
		promiseList.reserve(availableThreads - 1);
	}*/

	for (i = 0; i < pathfinderList.size(); i++)
	{
		if (i < availableThreads - 1) //checks if any threads are available
		{
			//std::promise<MyTransform> promise;
			promiseList.push_back(std::promise<MyTransform>());
			
			//std::future<MyTransform> future = promise.get_future();
			futureList.push_back(promiseList[i].get_future());
			//std::thread t;

			GameObject* go = world[pathfinderList[i]->GetGameObjectID()];

			gameObjectList.push_back(go);

			Pathfinder* p = pathfinderList[i];

			GameManager* gm = GameManager::GetInstance();

			//std::thread t(p->UpdateThreaded, std::move(promise), *go->GetTransform());
			//std::thread t(&GameManager::ThreadedPathfindCall, gm, std::move(promiseList[i]), std::ref(*go->GetTransform()), std::ref(p));

			threadList.push_back(std::thread(&GameManager::ThreadedPathfindCall, gm, std::move(promiseList[i]), std::ref(*go->GetTransform()), std::ref(p))); //= std::thread(&GameManager::ThreadedPathfindCall, gm, std::move(promiseList[i]), std::ref(*go->GetTransform()), std::ref(p));

		}
		else //Out of available threads, so it calculates it without multithreading
		{
			Pathfinder* p = pathfinderList[i];

			GameObject* go = world[p->GetGameObjectID()];

			MyTransform newPosition = p->Update(*go->GetTransform());

			go->GetTransform()->SetY(newPosition.GetY());
			go->GetTransform()->SetX(newPosition.GetX());
		}
		
		//&ThreadedPathfindCall, std::move(promise), *go->GetTransform(), p);

		//MyTransform newPosition = pathfinderList[i]->Update(*go->GetTransform());

		//printf("\nTest\n");

	}

	//NOTE: Does all of the following while it waits for the threads

	//Update player controller
	for (i = 0; i < controllerList.size(); i++)
	{
		int action = controllerList[i]->Update(world[controllerList[i]->GetGameObjectID()]->GetTransform());

		switch (action)
		{
		case 0: //Player movement. No other action required
			break;
		case 1: SpawnBasicGameObject(world[controllerList[i]->GetGameObjectID()]->GetTransform());
			break;
		case 2: DeleteFromWorld(world[GetClosestGO(world[controllerList[i]->GetGameObjectID()]->GetTransform())->GetObjectID()]);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			ClearWorld();
			break;
		case 6:
			SaveWorld();
			//TODO: Save the world
			break;
		}
	}

	//Check for collisions

	bool collisionDetected = false;
	int j;
	for (i = 0; i < colliderList.size(); i++)
	{
		collisionDetected = false;

		for (j = 0; j < colliderList.size(); j++)
		{
			if (colliderList[i] != colliderList[j])
			{
				GameObject* go1 = world[colliderList[i]->GetGameObjectID()];
				GameObject* go2 = world[colliderList[j]->GetGameObjectID()];
				bool collision1 = colliderList[i]->CheckCollision(Rectangle{ go1->GetTransform()->GetX(), go1->GetTransform()->GetY(), go1->GetRenderer()->GetWidth(), go1->GetRenderer()->GetHeight() }, Rectangle{ go2->GetTransform()->GetX(), go2->GetTransform()->GetY(), go2->GetRenderer()->GetWidth(), go2->GetRenderer()->GetHeight() });
				bool collision2 = colliderList[j]->CheckCollision(Rectangle{ go1->GetTransform()->GetX(), go1->GetTransform()->GetY(), go1->GetRenderer()->GetWidth(), go1->GetRenderer()->GetHeight() }, Rectangle{ go2->GetTransform()->GetX(), go2->GetTransform()->GetY(), go2->GetRenderer()->GetWidth(), go2->GetRenderer()->GetHeight() });

				if (collision1 || collision2)
				{
					collisionDetected = true;
				}
			}
		}
		if (!collisionDetected)
		{
			colliderList[i]->ResetCollision(); //No collisions detected between it and the rest of the colliders
		}
	}

	//Update collision collor changer
	for (i = 0; i < colorChangerList.size(); i++)
	{
		bool stateChanged = colorChangerList[i]->Update(world[colorChangerList[i]->GetGameObjectID()]->GetCollider()->GetIsColliding()); 

		if (stateChanged)
		{
			if (colorChangerList[i]->GetIsDefaultColor())
			{
				world[colorChangerList[i]->GetGameObjectID()]->GetRenderer()->SetColor(colorChangerList[i]->GetDefaultColor());
			}
			else
			{
				world[colorChangerList[i]->GetGameObjectID()]->GetRenderer()->SetColor(colorChangerList[i]->GetChangedColor());
			}
		}
	}

	//Get the new values from the threads:

	for (i = 0; i < threadList.size(); i++)
	{
		if (threadList[i].joinable())
		{
			threadList[i].join();
			//t.join();

			MyTransform newPosition = futureList[i].get();

			//Moves the game object to that new position

			gameObjectList[i]->GetTransform()->SetY(newPosition.GetY());
			gameObjectList[i]->GetTransform()->SetX(newPosition.GetX());
			//go->GetTransform()->SetY(newPosition.GetY());
			//go->GetTransform()->SetX(newPosition.GetX());
		}
	}
	
}

void GameManager::RenderWorld()
{
	int i;

	for (i = 0; i < rendererList.size(); i++)
	{
		RectangleRenderer* ren = rendererList[i];
		if (ren != nullptr)
		{
			if (world[ren->GetGameObjectID()]->GetTransform() != NULL)
			{
				DrawRectangle(world[ren->GetGameObjectID()]->GetTransform()->GetX(), world[ren->GetGameObjectID()]->GetTransform()->GetY(), ren->GetWidth(), ren->GetHeight(), ren->GetColor());
			}
			else
			{
				DrawRectangle(ren->GetTopLeftX(), ren->GetTopLeftY(), ren->GetWidth(), ren->GetHeight(), ren->GetColor());
			}
		}		
	}

	//NOTE: For testing grid system
	//rlPushMatrix();
	//	rlTranslatef(0, 25 * 50, 0);
	//	rlRotatef(90, 1, 0, 0);
	//	DrawGrid(1920, 2);
	//rlPopMatrix();

	//DrawGrid(1080, 10);
}

void GameManager::ClearWorld()
{
	//TODO: 

	int i;
	for (i = world.size() - 1; i > 2; i--)
	{
		//DeleteFromWorld(world[i]); //TODO: Fix errors with this. 
	}

}

int GameManager::GetNewObjectID()
{
	objectIDIndex++;
	return objectIDIndex;
}

void GameManager::DebugFrames()
{
	if (IsKeyDown(KEY_P))
	{
		printf("Time for frame (ms): %i \n", *frames);
	}
	else if (IsKeyDown(KEY_X))
	{
		printf("Number of collisions this frame: %i \n", numCollisions);
	}
}

void GameManager::SpawnBasicGameObject(MyTransform* playerTransform)
{
	//GameObject* go = new GameObject;
	//go->SetObjectID(GetNewObjectID());
	GameObject* go = CreateNewGameObject();

	go->SetTransform(CreateNewTransform(playerTransform->GetX() + 10, playerTransform->GetY() + 10));
	//GONewTransform(go);
	//go->GetTransform()->SetX(playerTransform->GetX() + 10);
	//go->GetTransform()->SetY(playerTransform->GetY() + 10);
	go->GetTransform()->SetGameObjectID(go->GetObjectID());

	go->SetCollider(CreateNewCollider());
	go->GetCollider()->SetGameObjectID(go->GetObjectID());

	//go->SetRenderer(CreateNewRenderer(80, 80, 800, 600, Color{ 255, 255, 0, 255 }));
	go->SetRenderer(CreateNewRenderer(Vector2{ 80, 80 }, Vector2{ 800, 600 }, Color{ 255, 255, 0, 255 }));
	go->GetRenderer()->SetGameObjectID(go->GetObjectID());

	//world.emplace(go->GetObjectID(), go);
}

void GameManager::DeleteFromWorld(GameObject* go) //TODO: Fix runtime error with this function!
{
	if (go->GetCollider() != NULL)
	{
		//Delete collider

		auto found = std::find(colliderList.begin(), colliderList.end(), (go->GetCollider()));
		if (found != colliderList.end()) {
			colliderList.erase(found);
		}

		colliderPool.Delete(go->GetCollider());
	}

	if (go->GetCollisionColorChanger() != NULL)
	{
		//Delete color changer
		
		auto found = std::find(colorChangerList.begin(), colorChangerList.end(), (go->GetCollisionColorChanger()));
		if (found != colorChangerList.end()) {
			colorChangerList.erase(found);
		}

		colorChangerPool.Delete(go->GetCollisionColorChanger());
	}

	if (go->GetPlayerController() != NULL)
	{
		//Delete controller
	
		auto found = std::find(controllerList.begin(), controllerList.end(), (go->GetPlayerController()));
		if (found != controllerList.end()) {
			controllerList.erase(found);
		}

		controllerPool.Delete(go->GetPlayerController());
	}

	if (go->GetRenderer() != NULL)
	{
		//Delete renderer
		
		auto found = std::find(rendererList.begin(), rendererList.end(), (go->GetRenderer()));
		if (found != rendererList.end()) {
			rendererList.erase(found);
		}

		rendererPool.Delete(go->GetRenderer());
	}

	if (go->GetTransform() != NULL)
	{
		//Delete Transform
		
		auto found = std::find(transformList.begin(), transformList.end(), (go->GetTransform()));
		if (found != transformList.end()) {
			transformList.erase(found);
		}

		transformPool.Delete(go->GetTransform());
	}

	world.erase(go->GetObjectID());
}

GameObject* GameManager::GetClosestGO(MyTransform* transform)
{
	MyTransform* closest = NULL;
	float closestDistance = 99999999.9f;

	for (MyTransform* t : transformList)
	{
		if (t != transform && t->GetGameObjectID() >= 3) //prevents the player and background from being deleted
		{
			float x = transform->GetX() - t->GetX();
			float y = transform->GetY() - t->GetY();

			float distance = sqrt((x * x) + (y * y));

			if (distance < closestDistance)
			{
				closestDistance = distance;
				closest = t;
			}
		}
	}
	return world[closest->GetGameObjectID()];
}

//SECTION: Create and add Components
#pragma region Components

MyTransform* GameManager::CreateNewTransform()
{
	MyTransform* t = transformPool.New();
	transformList.push_back(t);
	return t;
}

//Override:
MyTransform* GameManager::CreateNewTransform(float x, float y)
{
	MyTransform* t = transformPool.New(x, y);
	transformList.push_back(t);
	return t;
}

CollisionColorChanger* GameManager::CreateNewColorChanger()
{
	CollisionColorChanger* c = colorChangerPool.New();
	colorChangerList.push_back(c);
	return c;
}

//Override:
CollisionColorChanger* GameManager::CreateNewColorChanger(Color changedColor, Color defaultColor)
{
	CollisionColorChanger* c = colorChangerPool.New(changedColor, defaultColor);
	colorChangerList.push_back(c);
	return c;
}

PlayerController* GameManager::CreateNewController()
{
	PlayerController* p = controllerPool.New();
	controllerList.push_back(p);
	return p;
}

RectangleCollider* GameManager::CreateNewCollider()
{
	RectangleCollider* r = colliderPool.New();
	colliderList.push_back(r);
	return r;
}

RectangleRenderer* GameManager::CreateNewRenderer()
{
	RectangleRenderer* r = rendererPool.New();
	rendererList.push_back(r);
	return r;
}

//Override:
RectangleRenderer* GameManager::CreateNewRenderer(float width, float height, float topLeftX, float topLeftY, Color color)
{
	RectangleRenderer* r = rendererPool.New(width, height, topLeftX, topLeftY, color);
	rendererList.push_back(r);
	return r;
}

//Override:
RectangleRenderer* GameManager::CreateNewRenderer(Vector2 dimensions, Vector2 topLeft, Color color)
{
	RectangleRenderer* r = rendererPool.New(dimensions.x, dimensions.y, topLeft.x, topLeft.y, color);
	rendererList.push_back(r);
	return r;
}

Pathfinder* GameManager::CreateNewPathfinder()
{
	Pathfinder* p = pathfinderPool.New();
	pathfinderList.push_back(p);
	return p;
	
}

//Override:
Pathfinder* GameManager::CreateNewPathfinder(MyTransform target)
{
	Pathfinder* p = pathfinderPool.New(target);
	pathfinderList.push_back(p);
	return p;
}

#pragma endregion

GameManager::GameManager()
{
	Init();
}

GameManager::~GameManager()
{
	Cleanup();
}

void GameManager::ThreadedPathfindCall(std::promise<MyTransform>&& promise, MyTransform transform, Pathfinder* pathfinder)
{
	promise.set_value(pathfinder->Update(transform));
}
