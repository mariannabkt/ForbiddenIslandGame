#pragma once
#include "defines.h"
#include "player.h"

class DemoPlayer : public Player
{
protected:
	bool m_selected = false;
	bool m_highlighted = false;

	bool isSelected() { return m_selected; }
	

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }
public:

	DemoPlayer(player_role r) : Player(r) {}
	void drawBackLight(float center_width_offset, float center_height_offset) override;
	void draw() override;
	void update() override;
	bool contains(float x, float y) override;
	void setSelected(bool s) { m_selected = s; }
};