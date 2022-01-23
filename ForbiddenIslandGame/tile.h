#pragma once
#include "defines.h"

static int m_tiles_array[6][4] = { {0,1,1,0}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {0,1,1,0} };

class Tile
{
	float m_pos_x = 0.0f;
	float m_pos_y = 0.0f;

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


	static int(&getTilesArray())[6][4] { return m_tiles_array; }

	void draw(float x, float y);
	void update();

	string getImage() { return m_image_path; }
	float getPosX() { return m_pos_x; }
	float getPosY() { return m_pos_y; }
	void setCords(float x, float y);
};