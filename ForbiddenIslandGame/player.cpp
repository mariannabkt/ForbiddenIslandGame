#include "player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "game.h"
#include <string>

using namespace graphics;
using namespace std;

Game* game = Game::getInstance();


/*___________________________________________________________________________

  >>>>> CREATE NEW PLAYER AND INITIALIZE IT'S FIELDS BASED ON IT'S ROLE <<<<<
  ___________________________________________________________________________
*/
Player::Player(player_role r) : m_role(r)
{
	switch (m_role)
	{
	case EXPLORER:
		m_name = "Explorer";
		m_icon_path = EXPLORER_ROLE;
		m_pawn_path = EXPLORER_PAWN;
		SETCOLOR(m_color, 0.0f, 0.3f, 0.0f);
		setCords(CANVAS_WIDTH / 2 - 7.0f, CANVAS_HEIGHT / 2 + 4.0f);
		break;

	case DIVER:
		m_name = "Diver";
		m_icon_path = DIVER_ROLE;
		m_pawn_path = DIVER_PAWN;
		SETCOLOR(m_color, 0.1f, 0.1f, 0.1f);
		setCords(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 4.0f);
		break;

	case PILOT:
		m_name = "Pilot";
		m_icon_path = PILOT_ROLE;
		m_pawn_path = PILOT_PAWN;
		SETCOLOR(m_color, 0.0f, 0.0f, 0.3f);
		setCords(CANVAS_WIDTH / 2 + 7.0f, CANVAS_HEIGHT / 2 + 4.0f);
		break;
	}
}


/*________________________________________________________

  >>>>> INIT NECESSARY FIELDS FOR EVERY PLAY SESSION <<<<<
  ________________________________________________________
*/
void Player::init()
{
	m_turn = 0;
	m_active = false;
	m_selected = false;
	m_highlighted = false;
}


/*______________________________________________

  >>>>> DRAW PLAYER'S ICON WITH BACK LIGHT <<<<<
  ______________________________________________
*/
void Player::drawIcon(float x, float y, float width, float height)
{
	//--- DRAW PLAYER'S ICON BACK LIGHT ---
	Brush back;
	back.outline_opacity = 0.0f;

	if ((!isActive() && game->getState() == CHOOSE_PLAYER && isHighlighted()) ||
		( isActive() && game->getState() == PLAYING))
		back.fill_opacity = 0.8f;
	else
		back.fill_opacity = 0.0f;

	if ((isActive() || isSelected()) && game->getState() == CHOOSE_PLAYER)
	{
		SETCOLOR(back.fill_color, m_color[0], m_color[1], m_color[2]);
		back.fill_opacity = 0.9f;
	}
	drawDisk(x, y, height / 2, back);

	//--- DRAW PLAYER'S ICON ---
	Brush icon;
	icon.texture = m_icon_path;
	icon.outline_opacity = 0.0f;
	drawRect(x, y, width, height, icon);
}


/*______________________________________________

  >>>>> DRAW PLAYER'S PAWN WITH BACK LIGHT <<<<<
  ______________________________________________
*/
void Player::drawPawn()
{
	//--- DRAW PLAYER'S PAWN BACK LIGHT ---
	Brush back;
	back.fill_opacity = 1.0f * isActive();
	back.outline_opacity = 0.0f;
	back.texture = WHITE_PAWN;
	drawRect(m_player_posX, m_player_posY, PLAYER_SIZE + 0.17f, PLAYER_SIZE + 0.22f, back);

	//--- DRAW PLAYER'S PAWN ---
	Brush pawn;
	pawn.texture = m_pawn_path;
	pawn.outline_opacity = 0.0f;
	drawRect(m_player_posX, m_player_posY, PLAYER_SIZE, PLAYER_SIZE + 0.1, pawn);
}


/*___________________________________________

  >>>>> DRAW REMAINING PLAYER'S ACTIONS <<<<<
  ___________________________________________
*/
void Player::drawActions(float x, float y)
{
	Brush act1;
	act1.texture = ACTION_ONE;
	act1.outline_opacity = 0.0f;
	drawRect(x, y, 1.0f, 1.0f, act1);

	Brush act2;
	act2.texture = ACTION_TWO;
	act2.outline_opacity = 0.0f;
	drawRect(x, y + 1.2f, 1.0f, 1.0f, act2);

	Brush act3;
	act3.texture = ACTION_THREE;
	act3.outline_opacity = 0.0f;
	drawRect(x, y + 2.4f, 1.0f, 1.0f, act3);
}


/*_______________________________________________________

  >>>>> DRAW PLAYER FOR CHOOSING AND PLAYING STATES <<<<<
  _______________________________________________________
*/
void Player::draw()
{
	if (game->getState() == CHOOSE_PLAYER)
		drawIcon(m_player_posX, m_player_posY, 7.0f, 4.0f);

	else if (game->getState() == PLAYING)
	{
		drawPawn();
		setFont(SCRATCHED_FONT);

		if (m_turn == 1)
		{
			drawIcon(1.5f, 1.5f, 3.5f, 2.0f);
			drawActions(1.5f, 3.2f);

			Brush pl1;
			SETCOLOR(pl1.fill_color, m_color[0], m_color[1], m_color[2]);
			drawText(3.0f, 1.5f, 0.7f, "PLAYER " + to_string(m_turn), pl1);
			drawText(3.0f, 2.2f, 0.7f, m_name, pl1);
		}
		else if (m_turn == 2)
		{
			drawIcon(1.5f, 14.5f, 3.5f, 2.0f);
			drawActions(1.5f, 10.5f);

			Brush pl2;
			SETCOLOR(pl2.fill_color, m_color[0], m_color[1], m_color[2]);
			drawText(3.0f, 14.5f, 0.7f, "PLAYER " + to_string(m_turn), pl2);
			drawText(3.0f, 15.2f, 0.7f, m_name, pl2);
		}
	}
}


/*_________________________________________________________

  >>>>> UPDATE PLAYER FOR CHOOSING AND PLAYING STATES <<<<<
  _________________________________________________________
*/
void Player::update() 
{
	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	if (game->getState() == CHOOSE_PLAYER)
	{
		// highlight demo player
		if (contains(mx, my) && !isSelected())
		{
			setHighlight(true);

			// activate player
			if (ms.button_left_released)
			{
				setActive(true);
				game->setActivePlayer(this);

				// disable other players
				for (auto dp : game->getPlayers())
					if (dp.second != game->getActivePlayer())
						dp.second->setActive(false);
			}
		}
		else
			setHighlight(false);
	}
	else if (game->getState() == PLAYING)
	{

	}
}


/*______________________________________________________

  >>>>> FIND STARTING TILE FOR THE PLAYING SESSION <<<<<
  ______________________________________________________
*/
void Player::findStartTile()
{
	if (game->getState() == CHOOSE_PLAYER)
	{
		for (auto t : game->getTiles())
		{
			if ((t->getImage() == PILI_AGNOIAS && m_role == EXPLORER) ||
				(t->getImage() == PILI_PROSMONIS && m_role == DIVER) ||
				(t->getImage() == XEFWTO && m_role == PILOT))
			{
				m_start_tile = t;
				t->setTaken(true);
			}
		}
	}
	else if (game->getState() == PLAYING)
	{
		setCords(m_start_tile->getPosX(), m_start_tile->getPosY());
	}
}


/*____________________________________________

  >>>>> CHECK IF PLAYER IS INSIDE BOUNDS <<<<<
  ____________________________________________
*/
bool Player::contains(float x, float y)
{
	return (distance(x, y, m_player_posX, m_player_posY) < DEMO_PLAYER_SIZE);
}