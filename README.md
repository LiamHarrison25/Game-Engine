<a name="top"></a>
# Game-Engine

[![language](https://img.shields.io/badge/language-c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![RayLib](https://img.shields.io/badge/framework-RAYLIB-FFFFFF?style=for-the-badge&logo=raylib&logoColor=black)](https://www.raylib.com)
[![CMake](https://img.shields.io/badge/tool-CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org)
[![Windows](https://img.shields.io/badge/os-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/en-us/windows?r=1)

## Table of Contents
- [About](#-about)
- [Documentation](#-documentation)
- [License](#-license)
- [Contacts](#-contacts)
- [Acknowledgements](#-acknowledgements)

## 🎮 About

This is a project that I started working on for a game engine class in college. This is a 2D game engine built in C++ and utilizes the Raylib framework. I have been working on expanding this to add more features. 

## 📖 Documentation

Currently, the only way to really add objects to the game is to add them to the level file. This level file is named world.txt and uses a custom format. 

The format to add a new object is as follows:

```
gameobject
{
  component(0)
	{
		x0;
		y0;
		//etc
	}
}
```

Each game object can have multiple components, with the number corresponding to the type of component. The values inside of that component are the variables that will be assigned to it. 

### Component types:

* component(0): Transform
* component(1): Rectangle Renderer 
* component(2): Rectangle Collider
* component(3): Player Controller
* component(4): Collision Color Changer
* component(5): Pathfinder

## 💼 License

## 📧 Contacts

## 🧾 Acknowledgements 
- <https://github.com/raysan5/raylib.git>
- <https://github.com/SasLuca/raylib-cmake-template>

[back to top](#top)
