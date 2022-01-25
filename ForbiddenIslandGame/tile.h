#pragma once
#include "defines.h"

static int m_tiles_grid[6][4] = { {0,1,1,0}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {0,1,1,0} };

class Tile
{
	string m_tile_img;
	tile_type m_type;

	float m_tile_posX = 0.0f;
	float m_tile_posY = 0.0f;
	
	bool m_sunken = false;
	bool m_flooded = false;
	bool m_hasTreasure = false;
	bool m_treasureTaken = false;
	bool m_hasPlayer = false;

public:

	Tile(string tile_name); 

	void init();
	void draw();
	void update();

	static int(&getTilesGrid())[6][4] { return m_tiles_grid; }
	string getImage() { return m_tile_img; }
	float getPosX() { return m_tile_posX; }
	float getPosY() { return m_tile_posY; }

	bool hasPlayer() { return m_hasPlayer; }
	void setCords(float x, float y) { m_tile_posX = x; m_tile_posY = y; }
	void setTaken(bool a) { m_hasPlayer = a; }
};