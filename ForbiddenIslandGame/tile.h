#pragma once
#include "defines.h"
#include "clickable.h"
#include "treasure.h"

/*
	A tile entity can be clicked and make player perform actions.
*/
class Tile : public Clickable
{
	TILE_TYPE m_type;
	Treasure* m_treasure;

	int m_grid_i;
	int m_grid_j;

	bool m_sunken = false;
	bool m_flooded = false;

	bool m_hasTreasure = false;
	bool m_hasPlayer = false;
	bool m_canPerformAction = false;

public:

	Tile(string tile_name);

	void init();
	void draw();
	void update();

	int getPosI() const { return m_grid_i; }
	int getPosJ() const { return m_grid_j; }

	TILE_TYPE getType() const { return m_type; }

	Treasure* getTreasure() { return m_treasure; }
	bool hasTreasure() { return m_hasTreasure; }

	void setGridPos(float x, float y) { m_grid_i = x; m_grid_j = y; }

	bool getFlooded() const { return m_flooded; }
	bool getSunken() const { return m_sunken; }

	void flood() { m_flooded = true; }
	void sink() { m_sunken = true; }

	void setTaken(bool a) { m_hasPlayer = a; }

	void canPerformAction(bool c) { m_canPerformAction = c; }
	void checkCanPerfomrAction();
};