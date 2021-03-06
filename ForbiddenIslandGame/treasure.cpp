#include "game.h"
#include "treasure.h"
#include "defines.h"
#include "sgg/graphics.h" 

using namespace graphics;

/*_______________________________

  >>>>> CREATE NEW TREASURE <<<<<
  _______________________________
*/
Treasure::Treasure(TREASURE_TYPE t, float x, float y, bool c) : GameObject(x, y), m_type(t), m_collected(c)
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


/*_________________________

  >>>>> DRAW TREASURE <<<<<
  _________________________
*/
void Treasure::draw()
{
	Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.5f + 1.0f * m_collected;
	br.texture = m_treas_img;
	drawRect(m_posX, m_posY, 2.0f, 2.5f, br);
}
