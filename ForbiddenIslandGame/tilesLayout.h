#pragma once
#include "defines.h"
#include "clickable.h"

class TilesLayout : public Clickable
{
	int m_rows;
	int m_cols;

	int m_posX_offset = 3.6f;
	int m_posY_offset = 0.7f;

	int m_layout[7][9];

	bool m_highlighted = false;
	bool m_selected = false;

	int CLASSIC_ISLAND[6][6] = { {0,0,1,1,0,0}, {0,1,1,1,1,0}, {1,1,1,1,1,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0}, {0,0,1,1,0,0} };
	int SKULL_ISLAND[6][6] = { {1,1,1,1,1,1}, {1,0,1,1,0,1}, {1,1,1,1,1,1}, {0,1,1,1,1,0}, {0,1,1,1,1,0} };
	int HARPOON_HIDEOUT[6][6] = { {1,1,1,1,0,0}, {1,1,1,0,0,0}, {1,1,1,1,0,1}, {1,0,1,1,1,1}, {0,0,0,1,1,1}, {0,0,1,1,1,1} };
	int ATOLL_OF_DECISIONS[7][7] = { {0,0,1,1,1,0,0}, {0,1,1,0,1,1,0}, {1,1,0,0,0,1,1}, {1,0,0,0,0,0,1}, {1,1,0,0,0,1,1}, {0,1,1,0,1,1,0}, {0,0,1,1,1,0,0} };
	int BAY_OF_GULLS[6][8] = { {0,0,0,1,1,0,0,0}, {0,0,0,1,1,0,0,0}, {1,0,0,1,1,0,0,1}, {1,1,1,1,1,1,1}, {0,1,1,1,1,1,0}, {0,0,0,1,1,0,0,0} };
	int SHIPWRECK_BAY[4][8] = { {1,1,1,1,1,1,1,1}, {1,1,0,1,1,0,1,1}, {0,1,1,0,0,1,1,0}, {0,1,1,1,1,1,0} };
	int PALM_SPINGS[6][7] = { {0,0,1,1,1,0,0}, {0,1,1,1,1,1,0}, {0,1,0,1,0,1,0}, {0,0,0,1,0,0,0}, {0,1,1,1,1,1,0}, {1,1,1,1,1,1,1} };
	int MUTINY_TOWERS[6][7] = { {1,0,0,0,0,0,1}, {1,0,0,0,0,0,1}, {1,0,0,0,0,0,1}, {1,1,0,0,0,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1} };
	int DAVY_JONES[6][9] = { {0,0,0,0,1,0,0,0,0}, {0,1,1,1,1,0,0,0,0}, {1,0,1,1,1,1,1,1,0}, {0,1,1,1,1,0,1,1,1}, {0,0,0,0,1,1,1,1,0}, {0,0,0,0,1,0,0,0,0} };


public:

	TilesLayout(string img);

	void draw();
	void update();

	int (&getLayout())[7][9] { return m_layout; }

	const int& getRows() const { return m_rows; }
	const int& getCols() const { return m_cols; }

	int& getPosXoffset() { return m_posX_offset; }
	int& getPosYoffset() { return m_posY_offset; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

};
