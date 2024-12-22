#pragma once

#include "raylib.h"
#include "MyComponent.h"

// Requires MyTransform

class RectangleRenderer : public MyComponent
{

public:

	RectangleRenderer();
	RectangleRenderer(float width, float height, float x, float y, Color color);
	~RectangleRenderer();

	void Init();
	void Cleanup();

	float GetWidth();
	float GetHeight();
	float GetTopLeftX();
	float GetTopLeftY();
	Color GetColor();

	void SetWidth(float width);
	void SetHeight(float height);
	void SetTopLeftX(float x);
	void SetTopLeftY(float y);
	void SetColor(Color color);
	void SetR(float r);
	void SetG(float g);
	void SetB(float b);
	void SetA(float a);

private:

	float width;
	float height;
	float topLeftX;
	float topLeftY;
	Color color;
};