#pragma once
#include "defines.h"

class Treasure
{
	float m_treas_posX = 0.0f;
	float m_treas_posY = 0.0f;
	string m_treas_img;
	treasure_type m_type;
	bool m_collected = false;

public:

	Treasure(treasure_type t, float x=0.0f, float y=0.0f, bool c = false);

	void setCords(float x, float y) { m_treas_posX = x; m_treas_posY = y; }
	float getPosX() { return m_treas_posX; }
	float getPosY() { return m_treas_posY; }
	void draw();

	void setCollected(bool x) { m_collected = x; }
};