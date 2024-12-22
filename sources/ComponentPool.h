#pragma once

//#include "Components/Base/MyComponent.h"
#include <vector>
#include <cassert>

template <typename T>
class ComponentPool
{
public:

	ComponentPool(int size) :
		pool(size),
		inUse(size, false)
	{}

	ComponentPool() = default;

	/*pool()
	{

	}*/

	template <typename ...Us>
	T* New(Us ...args)
	{
		int i;
		for (i = 0; i < pool.size(); i++)
		{
			if (!inUse[i])
			{
				inUse[i] = true; 

				new (&pool[i]) T(args...);
				return &pool[i];
			}
		}

		assert(false); //should only reach this section if the object pool is empty
	}

	T* New()
	{
		int i;
		for (i = 0; i < pool.size(); i++)
		{
			if (!inUse[i])
			{
				inUse[i] = true;

				new (&pool[i]) T();
				return &pool[i];
			}
		}

		assert(false); //should only reach this section if the object pool is empty
	}

	void SetSize(int size)
	{
		pool.resize(size);
		inUse.resize(size);
	}

	void Delete(T* component)
	{
		int i;
		for (i = 0; i < pool.size(); i++) //loops through the entire pool until it find the gameobject to delete
		{
			T* currentCom = &pool[i];
			if (currentCom = component)
			{
				assert(inUse[i]); //checks to see if the component exists
				inUse[i] = false;

				currentCom->~T();
				return;

			}
		}

		assert(false); //should only reach this section if a component was not inside of the pool
	}

	//static ComponentPool instance;

	//ComponentPool<MyTransform> ComponentPool<MyTransform>::instance(32);

private:

	std::vector<T> pool;
	std::vector<bool> inUse;
};