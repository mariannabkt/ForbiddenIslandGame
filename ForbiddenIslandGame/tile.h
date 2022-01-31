#pragma once
#include "defines.h"
#include "clickable.h"


class Tile : public Clickable
{
	TILE_TYPE m_type;
	TREASURE_TYPE m_treasure;

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

	bool hasPlayer() { return m_hasPlayer; }

	int getPosI() { return m_grid_i; }
	int getPosJ() { return m_grid_j; }

	void setGridPos(float x, float y) { m_grid_i = x; m_grid_j = y; }

	bool getFlooded() { return m_flooded; }
	bool getSunken() { return m_sunken; }

	void collectTreasure();

	void flood() { m_flooded = true; }
	void sunk() { m_sunken = true; }

	void setTaken(bool a) { m_hasPlayer = a; }
	void setCanPerformAction(bool b) { m_canPerformAction = b; }
	void checkCanPerfomrAction();
	void canPerformAction(bool c) { m_canPerformAction = c; }
};