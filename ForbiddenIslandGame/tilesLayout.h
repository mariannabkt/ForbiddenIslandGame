#pragma once
#include "defines.h"
#include "clickable.h"

class TilesLayout : public Clickable
{
	int rows;
	int cols;

	int* m_layout;

	bool m_highlighted = false;
	bool m_selected = false;

public:

	TilesLayout(int* l);

	void draw();
	void update();

	int& getRows() { return rows; }
	int& getCols() { return cols; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

};
