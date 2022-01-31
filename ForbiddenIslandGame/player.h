#ifndef P_H
#define P_H

#pragma once
#include "defines.h"
#include "treasure.h"
#include "tile.h"
#include <map> 

class Action;

class Player : public Clickable
{
	float m_icon_posX;
	float m_icon_posY;
	float m_color[3];

	bool m_active = false;
	bool m_selected = false;
	bool m_highlighted = false;
	bool m_allTreasuresCollected = false;
	bool m_won = false;

	int m_turn = 0;
	string m_name;
	string m_icon_img;
	string m_pawn_img;

	Action* m_actions;
	PLAYER_ROLE m_role;
	Tile* m_standing_tile;
	map<TREASURE_TYPE, Treasure*> m_treasures = map<TREASURE_TYPE, Treasure*>();

	void drawPawn();
	void drawIcon(float width, float height);

public:

	Player(PLAYER_ROLE r);

	void init();
	void draw();
	void update();
	void isStartTile(Tile* t);
	bool contains(float x, float y) override;

	PLAYER_ROLE getPlayerRole() { return m_role; }

	Tile* getStandingTile() { return m_standing_tile; }
	void setStandingTile(Tile* t) { m_standing_tile = t; m_standing_tile->setTaken(true); }

	void setIconCords(float x, float y) { m_icon_posX = x; m_icon_posY = y; }

	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }

	bool isSelected() { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

	bool isHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }

	int getPlayerTurn() { return m_turn; }
	void setPlayerTurn(int t) { m_turn = t; }

	map<TREASURE_TYPE, Treasure*>& getTreasures() { return m_treasures; }

	Action* getActions() { return m_actions; }
	void setActions(Action* act) { m_actions = act; }

	bool AllTreasCollected() {
		for (auto t : m_treasures)
			m_allTreasuresCollected = m_allTreasuresCollected && t.second->isCollected();
		return m_allTreasuresCollected;
	}

	void move(Tile* t);
	void victory() { m_won = true; }
};
#endif