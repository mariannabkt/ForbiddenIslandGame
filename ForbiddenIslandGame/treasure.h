#pragma once
#include "defines.h"
#include "gameObject.h"

/*
	A treasure entity can be collected by players when they're on top of it's tile.
*/
class Treasure : public GameObject
{
	string m_treas_img;
	TREASURE_TYPE m_type;
	bool m_collected;

public:

	Treasure(TREASURE_TYPE t, float x = 0.0f, float y = 0.0f , bool c = false);
	void draw();
	void update() {}
		
	bool isCollected() { return m_collected; }
	void setCollected(bool x) { m_collected = x; }

	TREASURE_TYPE getType() const { return m_type; }
};