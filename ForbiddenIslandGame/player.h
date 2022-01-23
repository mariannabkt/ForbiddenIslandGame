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

	player_role m_role;
	string m_icon_path;
	string m_pawn_path;
	Tile* m_start_tile;

	virtual void drawBackLight(float x, float y);
	void drawIcon(float x, float y, float width, float height);
	void drawPawn(float x, float y);

public:
	
	Player(player_role r);


	void drawPlayer();
	void updatePlayer();

	float getPosX() { return m_player_posX; }
	float getPosY() { return m_player_posY; }

	Tile* getStartTile() { return m_start_tile; }
	player_role getPlayerPole() { return m_role; }

	void setCords(float x, float y) { m_player_posX = x; m_player_posY = y; }

	void setActive(bool a) { m_active = a; }
	bool isActive() { return m_active; }

	virtual bool contains(float x, float y);
};

