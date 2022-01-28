#pragma once
#include "sgg/graphics.h"

using namespace graphics;
using namespace std;

class RectClickable
{
protected:
	Brush m_br;
	string m_img;

	float m_posX;
	float m_posY;
	float m_width;
	float m_height;

	float m_left;
	float m_right;
	float m_up;
	float m_down;

public:
	RectClickable(string img, float w = 0.0f, float h = 0.0f, float x = 0.0f, float y = 0.0f);

	string getImage() { return m_img; }
	float getPosX() { return m_posX; }
	float getPosY() { return m_posY; }
	void setCords(float x, float y);

	virtual void draw() = 0;
	virtual void update() = 0;

	bool contains(float x, float y);
};