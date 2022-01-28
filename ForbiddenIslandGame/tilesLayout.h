#pragma once
#include "defines.h"

class TilesLayout
{
	int rows;
	int cols;

	int* m_layout;
	string m_layout_img;

	float m_img_posX = 0.0f;
	float m_img_posY = 0.0f;

	float m_img_left = 0.0f;
	float m_img_right = 0.0f;
	float m_img_up = 0.0f;
	float m_img_down = 0.0f;

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

	bool contains(float x, float y);
};
