#include "tile.h"
#include "game.h"
#include "defines.h"

using namespace graphics;


Tile::Tile(string tile_name) : m_image_path(tile_name) 
{
	if (m_image_path == XEFWTO)
		m_type = LANDING;
	else if (m_image_path == KIPOS_KRA || m_image_path == KIPOS_PSI)
	{
		m_type = AIR;
		m_hasTreasure = true;
	}
	else if (m_image_path == NAOS_FEGGARIOY || m_image_path == NAOS_ILIOY)
	{
		m_type = EARTH;
		m_hasTreasure = true;
	}
	else if (m_image_path == PALATI_KOR || m_image_path == PALATI_PAL)
	{
		m_type = WATER;
		m_hasTreasure = true;
	}
	else if (m_image_path == SPILIA_LAVAS || m_image_path == SPILIA_SKIWN)
	{
		m_type = FIRE;
		m_hasTreasure = true;
	}
	else 
		m_type = BASIC;
}


void Tile::draw(float x, float y)
{
	Brush br;
	br.outline_opacity = 0.0f;

	br.texture = m_image_path;
	drawRect(x, y, TILE_SIZE, TILE_SIZE, br);
}


void Tile::update()
{
}


void Tile::setCords(float x, float y)
{
	m_pos_x = x;
	m_pos_y = y;
}
;