#pragma once
#include "defines.h"
#include "tile.h"

class Player 
{
	float m_icon_posX;
	float m_icon_posY;
	float m_pawn_posX;
	float m_pawn_posY;
	float m_color[3];

	bool m_active = false;
	bool m_selected = false;
	bool m_highlighted = false;

	int m_turn = 0;
	string m_name;

	player_role m_role;
	string m_icon_path;
	string m_pawn_path;
	Tile* m_standing_tile;

	void drawPawn();
	void drawIcon(float width, float height);
	void drawActions(float x, float y);

public:
	
	Player(player_role r);

	void init();
	void draw();
	void update();
	void isStartTile(Tile* t);
	bool contains(float x, float y);

	Tile* getStandingTile() { return m_standing_tile; }
	player_role getPlayerRole() { return m_role; }

	float getPosX() { return m_pawn_posX; }
	float getPosY() { return m_pawn_posY; }

	void setPawnCords(float x, float y) { m_pawn_posX = x; m_pawn_posY = y; }
	void setIconCords(float x, float y) { m_icon_posX = x; m_icon_posY = y; }

	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
	
	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	int getPlayersTurn() { return m_turn; }
	void setPlayersTurn(int t) { m_turn = t; }
};