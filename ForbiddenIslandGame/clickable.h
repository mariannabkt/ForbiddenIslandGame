#pragma once
#include "sgg/graphics.h"
#include "gameObject.h"

using namespace graphics;
using namespace std;

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

	string getImage() { return m_img; }

	void setCords(float x, float y);

	virtual bool contains(float x, float y);
};