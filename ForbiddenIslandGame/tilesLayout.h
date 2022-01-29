#pragma once
#include "defines.h"
#include "clickable.h"
#include "array2d.h"

static int CLASSIC_ISLAND[6][6] = { {0,0,1,1,0,0}, {0,1,1,1,1,0}, {1,1,1,1,1,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0}, {0,0,1,1,0,0} };
static int SKULL_ISLAND[5][6] = { {1,1,1,1,1,1}, {1,0,1,1,0,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0}, {0,1,1,1,1,0} };
static int HARPOON_HIDEOUT[6][6] = { {1,1,1,1,0,0}, {1,1,1,0,0,0}, {1,1,1,1,0,1}, {1,0,1,1,1,1}, {0,0,0,1,1,1}, {0,0,1,1,1,1} };
static int ATOLL_OF_DECISIONS[7][7] = { {0,0,1,1,1,0,0}, {0,1,1,0,1,1,0}, {1,1,0,0,0,1,1}, {1,0,0,0,0,0,1}, {1,1,0,0,0,1,1}, {0,1,1,0,1,1,0}, {0,0,1,1,1,0,0} };
static int BAY_OF_GULLS[6][8] = { {0,0,0,1,1,0,0,0}, {0,0,0,1,1,0,0,0}, {1,0,0,1,1,0,0,1}, {1,1,1,1,1,1,1}, {0,1,1,1,1,1,0}, {0,0,0,1,1,0,0,0} };
static int SHIPWRECK_BAY[4][8] = { {1,1,1,1,1,1,1,1}, {1,1,0,1,1,0,1,1}, {0,1,1,0,0,1,1,0}, {0,1,1,1,1,1,0} };
static int PALM_SPINGS[6][7] = { {0,0,1,1,1,0,0}, {0,1,1,1,1,1,0}, {0,1,0,1,0,1,0}, {0,0,0,1,0,0,0}, {0,1,1,1,1,1,0}, {1,1,1,1,1,1,1} };
static int MUTINY_TOWERS[6][7] = { {1,0,0,0,0,0,1}, {1,0,0,0,0,0,1}, {1,0,0,0,0,0,1}, {1,1,0,0,0,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1} };
static int DAVY_JONES[6][9] = { {0,0,0,0,1,0,0,0,0}, {0,1,1,1,1,0,0,0,0}, {1,0,1,1,1,1,1,1,0}, {0,1,1,1,1,0,1,1,1}, {0,0,0,0,1,1,1,1,0}, {0,0,0,0,1,0,0,0,0} };


class TilesLayout : public Clickable
{
	int m_rows;
	int m_cols;

	float m_posX_offset = 3.6f;
	float m_posY_offset = 0.7f;

	//array2d arr;
	int** m_layout;

	bool m_highlighted = false;
	bool m_selected = false;

public:

	TilesLayout(string img);

	void draw();
	void update();

	int** (getLayout());

	void initArray(int rows, int cols);

	const int getRows() const { return m_rows; }
	const int getCols() const { return m_cols; }

	float getPosXoffset() { return m_posX_offset; }
	float getPosYoffset() { return m_posY_offset; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

};
