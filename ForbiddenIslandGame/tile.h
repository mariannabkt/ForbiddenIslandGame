#pragma once
#include "defines.h"

static int m_tiles_array[4][6] = { {0,1,1,1,1,0}, {1,1,1,1,1,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0} };

class Tile
{
	string m_image_path;
	tile_type m_type;
	bool m_sunken = false;;
	bool m_flooded = false;;
	bool m_hasTreasure = false;
	bool m_treasureTaken = false;
	bool m_hasPlayer = false;

public:

	Tile(string tile_name); 
	~Tile() {};


	static int(&getArray())[4][6] { return m_tiles_array; }

	void draw(float x, float y);
	void update();
};