#pragma once
#include "gameObject.h"
#include "defines.h"

class Treasure : GameObject
{
	float m_treas_posX = 0.0f;
	float m_treas_posY = 0.0f;

	string m_treas_img;
	treasure_type m_type;
	bool m_collected = false;

public:

	Treasure(treasure_type t, float x = 0.0f, float y = 0.0f, bool c = false);
	void draw();
	
	float getPosX() { return m_treas_posX; }
	float getPosY() { return m_treas_posY; }
	
	void setCollected(bool x) { m_collected = x; }
	void setCords(float x, float y) { m_treas_posX = x; m_treas_posY = y; }
};