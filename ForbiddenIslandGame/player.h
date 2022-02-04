#ifndef P_H
#define P_H

#pragma once
#include "defines.h"
#include "treasure.h"
#include "tile.h"
#include <map> 

class Action;

/*
	A player entity can collect treasures performing actions on tiles.
*/
class Player : public Clickable
{
	float m_icon_posX;
	float m_icon_posY;
	float m_color[3];

	bool m_active = false;
	bool m_selected = false;
	bool m_highlighted = false;

	int m_turn = 0;
	string m_name;
	string m_icon_img;

	PLAYER_ROLE m_role;
	Action* m_actions;
	Tile* m_standing_tile;
	map<TREASURE_TYPE, Treasure*> m_treasures = map<TREASURE_TYPE, Treasure*>();

	void drawPawn();
	void drawIcon(float width, float height);

public:

	Player(PLAYER_ROLE r);

	void init();
	void draw();
	void update();

	bool allTreasCollected();
	void move(Tile* t);
	void isStartTile(Tile* t);
	bool contains(float x, float y) override;

	string getPlayerName() const { return m_name; }
	string getIconImage() const { return m_icon_img; }

	PLAYER_ROLE getPlayerRole() const { return m_role; }
	Tile* getStandingTile() const { return m_standing_tile; }

	void setIconCords(float x, float y) { m_icon_posX = x; m_icon_posY = y; }

	bool isActive() const { return m_active; }
	void setActive(bool a) { m_active = a; }

	bool isSelected() const { return m_selected; }
	void setSelected(bool s) { m_selected = s; }

	int getPlayerTurn() const { return m_turn; }
	void setPlayerTurn(int t) { m_turn = t; }

	map<TREASURE_TYPE, Treasure*>& getTreasures() { return m_treasures; }
	Action* getActions() { return m_actions; }
};
#endif