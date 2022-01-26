#include "treasure.h"
#include "defines.h"
#include "sgg/graphics.h" 

using namespace graphics;

Treasure::Treasure(treasure_type t, float x, float y, bool c) : m_type(t), m_collected(c), 
	m_treas_posX(CANVAS_WIDTH / 2 + x), m_treas_posY(CANVAS_HEIGHT / 2 + y)
{
	switch (m_type) {
	case FIRE:
		m_treas_img = FIRE_TREASURE;
		break;
	case EARTH:
		m_treas_img = EARTH_TREASURE;
		break;
	case AIR:
		m_treas_img = AIR_TREASURE;
		break;
	case WATER:
		m_treas_img = WATER_TREASURE;
		break;
	}
}

void Treasure::draw()
{
	Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.6f + 1 * m_collected;
	br.texture = m_treas_img;
	drawRect(m_treas_posX, m_treas_posY, 2.0f, 2.5f, br);
}
