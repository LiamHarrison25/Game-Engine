#include "RectangleRenderer.h"

RectangleRenderer::RectangleRenderer()
{
	Init();
}

RectangleRenderer::RectangleRenderer(float width, float height, float topLeftX, float topLeftY, Color color)
{
	this->width = width;
	this->height = height;
	this->topLeftX = topLeftX;
	this->topLeftY = topLeftY;
	this->color = color;
}

RectangleRenderer::~RectangleRenderer()
{
	Cleanup();
}

void RectangleRenderer::Init()
{
	width, height = 0;
	color = { 0, 0, 0, 0 };
}

void RectangleRenderer::Cleanup()
{
	
}

float RectangleRenderer::GetWidth()
{
	return width;
}

float RectangleRenderer::GetHeight()
{
	return height;
}

float RectangleRenderer::GetTopLeftX()
{
	return topLeftX;
}

float RectangleRenderer::GetTopLeftY()
{
	return topLeftY;
}

Color RectangleRenderer::GetColor()
{
	return color;
}

void RectangleRenderer::SetWidth(float width)
{
	this->width = width;
}

void RectangleRenderer::SetHeight(float height)
{
	this->height = height;
}

void RectangleRenderer::SetColor(Color color)
{
	this->color = color;
}

void RectangleRenderer::SetTopLeftX(float x)
{
	this->topLeftX = x;
}

void RectangleRenderer::SetTopLeftY(float y)
{
	this->topLeftY = y;
}

void RectangleRenderer::SetR(float r)
{
	this->color.r = r;
}

void RectangleRenderer::SetG(float g)
{
	this->color.g = g;
}

void RectangleRenderer::SetB(float b)
{
	this->color.b = b;
}

void RectangleRenderer::SetA(float a)
{
	this->color.a = a;
}
