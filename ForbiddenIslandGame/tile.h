#pragma once
#include "defines.h"

static int m_tiles_grid[6][4] = { {0,1,1,0}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {0,1,1,0} };

class Tile
{
	float m_tile_posX = 0.0f;
	float m_tile_posY = 0.0f;

	string m_tile_img;
	tile_type m_type;

	bool m_sunken;
	bool m_flooded;
	bool m_hasTreasure;
	bool m_treasureTaken;
	bool m_hasPlayer;

public:

	Tile(string tile_name); 
	~Tile() {};

	void init();
	void draw();
	void update();

	static int(&getTilesGrid())[6][4] { return m_tiles_grid; }
	string getImage() { return m_tile_img; }
	float getPosX() { return m_tile_posX; }
	float getPosY() { return m_tile_posY; }
	void setCords(float x, float y) { m_tile_posX = x; m_tile_posY = y; }
	bool hasPlayer() { return m_hasPlayer; }
	void setTaken(bool a) { m_hasPlayer = a; }
};