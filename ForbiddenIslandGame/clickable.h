#pragma once
#include "sgg/graphics.h"
#include "gameObject.h"

using namespace graphics;
using namespace std;

/*
	Abstract class for clickable game objects such as buttons, tiles, players and layouts.
*/
class Clickable : public GameObject
{
protected:

	Brush m_br;
	string m_img;

	float m_width;
	float m_height;

	float m_left;
	float m_right;
	float m_up;
	float m_down;

public:

	Clickable(string img = "", float w = 0.0f, float h = 0.0f, float x = 0.0f, float y = 0.0f);

	string getImage() const{ return m_img; }

	float getLeft() const { return m_left; }
	float getRight() const { return m_right; }
	float getUp() const { return m_up; }
	float getDown() const { return m_down; }

	void setCords(float x, float y);

	virtual bool contains(float x, float y);
};