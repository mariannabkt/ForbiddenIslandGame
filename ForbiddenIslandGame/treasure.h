#pragma once
#include "defines.h"
#include "gameObject.h"

class Treasure : public GameObject
{
	float m_width = 2.0f;
	float m_height = 2.5f;

	string m_treas_img;
	TREASURE_TYPE m_type;
	bool m_collected;

public:

	Treasure(TREASURE_TYPE t, float x = 0.0f, float y = 0.0f , bool c = false);
	void draw();
	void update();
		
	bool isCollected() { return m_collected; }
	void setCollected(bool x) { m_collected = x; }


	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	void setDimensions(float w, float h) { m_width = w; m_height = h; }

};