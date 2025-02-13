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

### Level Loading

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
	* x: (float) x position value
 	* y: (float) y position value	 
* component(1): Rectangle Renderer
	* w: (float) width of the rectangle
 	* h: (float) height of the rectangle
  	* x: (float) x position value
 	* y: (float) y position value
  	* r: (float) red color value
  	* g: (float) green color value
  	* b: (float) blue color value
  	* a: (float) alpha color value
* component(2): Rectangle Collider
* component(3): Player Controller
* component(4): Collision Color Changer
	* r: (float) red color value
  	* g: (float) green color value
  	* b: (float) blue color value
  	* a: (float) alpha color value
* component(5): Pathfinder
	* x: (float) x position value
 	* y: (float) y position value
 
### Level Loading Example:

This will spawn in a game object at the position (800, 400). It will be rendered as a rectangle with the dimensions of (60 x 60). The color of the rectangle in srgb will be (0, 255, 156, 255). It will be able to collide with other objects in the scene, and will change its color whenever it detects a collision. The color will change to the srgb value of (64, 156, 156, 255). 

```
gameobject
{
	component(0)
	{
	x800;
	y400;
	}
	component(1)
	{
	w60;
	h60;
	x800;
	y400;
	r0;
	g255;
	b156;
	a255;
	}
	component(2)
	{
	}
	component(4)
	{
	r64;
	g156;
	b156;
	a255;
	}
}
```

### Player Controls

If you have a game object with a player controller attached, you will be able to utilize several different controls. 

Controls:
* Up Arrow Key: Moves the object with the player controller up
* Down Arrow Key: Moves the object with the player controller down
* Left Arrow Key: Moves the object with the player controller to the left
* Right Arrow Key: Moves the object with the player controller to the right
* Space Key: Spawns a basic game object next to the game object with the player controller
* D Key: Deletes the closest game object to the game object with the player controller
* M Key: Saves the game objects in the level to world.txt

## 💼 License

## 📧 Contacts

<a href="https://www.linkedin.com/in/liam-t-harrison/" target="blank"><img align="center" src="https://img.shields.io/badge/linkedin-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white" alt="linkedin" /><a/>
<a href="https://liamharrison.dev" target="blank"><img align="center" src="https://img.shields.io/badge/github%20pages-121013?style=for-the-badge&logo=github&logoColor=white" alt="liamHarrison.dev"  /></a>

## 🧾 Acknowledgements 
- <https://github.com/raysan5/raylib.git>
- <https://github.com/SasLuca/raylib-cmake-template>

[back to top](#top)
