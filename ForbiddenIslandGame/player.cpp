#include "player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "game.h"
#include <string>

using namespace graphics;
using namespace std;



Player::Player(player_role r) : m_role(r)
{
	Game* game = Game::getInstance();
	
	switch (m_role)
	{
	case EXPLORER:
		m_icon_path = EXPLORER_ROLE;
		m_pawn_path = EXPLORER_PAWN;
		SETCOLOR(m_color, 0.0f, 0.3f, 0.0f);
		break;
	case DIVER:
		m_icon_path = DIVER_ROLE;
		m_pawn_path = DIVER_PAWN;
		SETCOLOR(m_color, 0.5f, 0.5f, 0.5f);
		break;
	case PILOT:
		m_icon_path = PILOT_ROLE;
		m_pawn_path = PILOT_PAWN;
		SETCOLOR(m_color, 0.0f, 0.0f, 0.3f);
		break;
	}

	for (auto t : game->getTiles())
	{
		if (t->getImage() == PILI_AGNOIAS && m_role == EXPLORER)
			m_start_tile = t;
		else if (t->getImage() == PILI_PROSMONIS && m_role == DIVER)
			m_start_tile = t;
		else if (t->getImage() == XEFWTO && m_role == PILOT)
			m_start_tile = t;
	}
	setCords(m_start_tile->getPosX(), m_start_tile->getPosY());
}


void Player::drawBackLight(float x, float y)
{
	Brush back;
	back.fill_opacity = 1.0f * isActive();
	back.outline_opacity = 0.0f;
	back.texture = WHITE_PAWN;
	drawRect(x, y, PLAYER_SIZE + 0.1f, PLAYER_SIZE + 0.2f, back);
}

void Player::drawIcon(float x, float y, float width, float height)
{
	Brush icon;
	icon.texture = m_icon_path;
	icon.outline_opacity = 0.0f;
	drawRect(x, y, width, height, icon);
}

void Player::drawPawn(float x, float y)
{
	Brush pawn;
	pawn.texture = m_pawn_path;
	pawn.outline_opacity = 0.0f;
	drawRect(x, y, PLAYER_SIZE, PLAYER_SIZE + 0.1, pawn);
}


void Player::drawPlayer() 
{
	//--- DRAW PLAYER'S BACK LIGHT ---
	drawBackLight(m_player_posX, m_player_posY);

	//--- DRAW PLAYER'S PAWN ---
	drawPawn(m_player_posX, m_player_posY);
}

void Player::updatePlayer() 
{
	Game* game = Game::getInstance();

	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// highlight player
	if (contains(mx, my)) 
	{
		//setHighlight(true);

		// activate player
		if (ms.button_left_released)
		{
			setActive(true);
			game->setActivePlayer(this);
			
			// disable other players
			for (auto player : game->getPlayers())
			{
				if (player != game->getActivePlayer())
					player->setActive(false);
			}
		}
	}
	/*else 
		setHighlight(false);*/
}

bool Player::contains(float x, float y)
{
	return (distance(x, y, m_player_posX, m_player_posY) < PLAYER_SIZE);
}