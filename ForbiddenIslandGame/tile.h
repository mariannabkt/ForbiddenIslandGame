#pragma once
#include "defines.h"

static int m_tiles_grid[6][6] = { {0,0,1,1,0,0}, {0,1,1,1,1,0}, {1,1,1,1,1,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0}, {0,0,1,1,0,0} };

class Tile
{
	string m_tile_img;
	tile_type m_type;
	treasure_type m_treasure;

	float m_tile_posX = 0.0f;
	float m_tile_posY = 0.0f;

	float m_tile_left;
	float m_tile_right;
	float m_tile_up;
	float m_tile_down;

	int m_grid_i = 0;
	int m_grid_j = 0;
	
	bool m_sunken = false;
	bool m_flooded = false;

	bool m_hasTreasure = false;
	bool m_treasureTaken = false;

	bool m_hasPlayer = false;
	bool m_canPerformAction = false;

public:

	Tile(string tile_name); 

	void init();
	void draw();
	void update();
	bool contains(float x, float y);

	static int(&getTilesGrid())[6][6] { return m_tiles_grid; }
	string getImage() { return m_tile_img; }
	bool hasPlayer() { return m_hasPlayer; }

	float getPosX() { return m_tile_posX; }
	float getPosY() { return m_tile_posY; }

	int getPosI() { return m_grid_i; }
	int getPosJ() { return m_grid_j; }

	void setCords(float x, float y);
	void setGridPos(float x, float y) { m_grid_i = x; m_grid_j = y; }

	void setTaken(bool a) { m_hasPlayer = a; }
	void setCanPerformAction(bool b) { m_canPerformAction = b; }
};