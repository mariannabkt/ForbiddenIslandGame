#pragma once
#include "defines.h"

class Tile
{
	tile_type m_type;
	bool m_sunken;
	bool m_flooded;
	bool m_hasTreasure;
	bool m_treasureTaken;
	bool m_hasPlayer;
};