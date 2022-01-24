#pragma once
#include "defines.h"
#include "tile.h"

class Player 
{
protected:

	float m_player_posX = 0.0f;
	float m_player_posY = 0.0f;
	float m_color[3];

	bool m_active = false;
	bool m_selected = false;
	bool m_highlighted = false;

	int m_turn = 0;
	string m_name;

	player_role m_role;
	string m_icon_path;
	string m_pawn_path;
	Tile* m_start_tile;

	void drawIcon(float x, float y, float width, float height);
	void drawPawn();
	void drawActions(float x, float y);

public:
	
	Player(player_role r);

	void init();
	void draw();
	void update();

	float getPosX() { return m_player_posX; }
	float getPosY() { return m_player_posY; }

	void findStartTile();
	Tile* getStartTile() { return m_start_tile; }
	player_role getPlayerRole() { return m_role; }

	void setCords(float x, float y) { m_player_posX = x; m_player_posY = y; }

	void setActive(bool a) { m_active = a; }
	bool isActive() { return m_active; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	int getPlayersTurn() { return m_turn; }
	void setPlayersTurn(int t) { m_turn = t; }

	bool contains(float x, float y);
};
