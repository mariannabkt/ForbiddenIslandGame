#ifndef P_H
#define P_H

#pragma once
#include "defines.h"
#include "treasure.h"
#include "tile.h"
#include <map> 

#include "action.h"

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
	string m_icon_img;
	string m_pawn_img;

	Action* m_actions;
	player_role m_role;
	Tile* m_standing_tile;
	map<treasure_type, Treasure*> m_treasures = map<treasure_type, Treasure*>();

	void drawPawn();
	void drawIcon(float width, float height);

public:

	Player(player_role r);

	void init();
	void draw();
	void update();
	void isStartTile(Tile* t);
	bool contains(float x, float y);

	player_role getPlayerRole() { return m_role; }

	Tile* getStandingTile() { return m_standing_tile; }
	void setStandingTile(Tile* t) { m_standing_tile = t; m_standing_tile->setTaken(true); }

	float getPosX() { return m_pawn_posX; }
	float getPosY() { return m_pawn_posY; }

	void setCords(float x, float y) { m_pawn_posX = x; m_pawn_posY = y; }
	void setIconCords(float x, float y) { m_icon_posX = x; m_icon_posY = y; }

	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	int getPlayerTurn() { return m_turn; }
	void setPlayerTurn(int t) { m_turn = t; }

	map<treasure_type, Treasure*>& getTreasures() { return m_treasures; }

	Action* getActions() { return m_actions; }
	void setActions(Action* act) { m_actions = act; }
};
#endif