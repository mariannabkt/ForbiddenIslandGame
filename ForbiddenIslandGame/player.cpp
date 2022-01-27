#include "player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "game.h"
#include <string>

using namespace graphics;
using namespace std;


/*___________________________________________________________________________

  >>>>> CREATE NEW PLAYER AND INITIALIZE IT'S MEMBERS BASED ON IT'S ROLE <<<<<
  ___________________________________________________________________________
*/
Player::Player(player_role r) : m_role(r)
{
	switch (m_role)
	{
	case EXPLORER:
		m_name = "Explorer";
		m_icon_img = EXPLORER_ICON;
		m_pawn_img = EXPLORER_PAWN;
		SETCOLOR(m_color, 0.0f, 0.3f, 0.0f);
		setIconCords(CANVAS_WIDTH / 2 - 7.5f, CANVAS_HEIGHT / 2 + 3.5f);
		break;

	case DIVER:
		m_name = "Diver";
		m_icon_img = DIVER_ICON;
		m_pawn_img = DIVER_PAWN;
		SETCOLOR(m_color, 0.1f, 0.1f, 0.1f);
		setIconCords(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 3.5f);
		break;

	case PILOT:
		m_name = "Pilot";
		m_icon_img = PILOT_ICON;
		m_pawn_img = PILOT_PAWN;
		SETCOLOR(m_color, 0.0f, 0.0f, 0.3f);
		setIconCords(CANVAS_WIDTH / 2 + 7.5f, CANVAS_HEIGHT / 2 + 3.5f);
		break;
	}
	m_treasures[AIR] = new Treasure(AIR);
	m_treasures[FIRE] = new Treasure(FIRE);
	m_treasures[EARTH] = new Treasure(EARTH);
	m_treasures[WATER] = new Treasure(WATER);
}


/*_________________________________________________________

  >>>>> INIT NECESSARY MEMBERS FOR EVERY PLAY SESSION <<<<<
  _________________________________________________________
*/
void Player::init()
{
	m_turn = 0;
	m_active = false;
	m_selected = false;
	m_highlighted = false;

	switch (m_role) {
	case EXPLORER:
		setIconCords(CANVAS_WIDTH / 2 - 7.5f, CANVAS_HEIGHT / 2 + 3.5f);
		break;
	case DIVER:
		setIconCords(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 3.5f);
		break;
	case PILOT:
		setIconCords(CANVAS_WIDTH / 2 + 7.5f, CANVAS_HEIGHT / 2 + 3.5f);
		break;
	}
	for (auto t : m_treasures) 
		t.second->setCollected(false);
}


/*______________________________________________

  >>>>> DRAW PLAYER'S ICON WITH BACK LIGHT <<<<<
  ______________________________________________
*/
void Player::drawIcon(float width, float height)
{
	//--- DRAW PLAYER'S ICON BACK LIGHT ---
	Brush back;
	back.outline_opacity = 0.0f;

	back.fill_opacity = (!isActive() && game->getState() == CHOOSE_PLAYER && isHighlighted()) || 
						( isActive() && game->getState() == PLAYING) ? 0.8f : 0.0f;

	if ((isActive() || isSelected()) && game->getState() == CHOOSE_PLAYER)
	{
		SETCOLOR(back.fill_color, m_color[0], m_color[1], m_color[2]);
		back.fill_opacity = 0.9f;
	}
	drawDisk(m_icon_posX, m_icon_posY, height / 2, back);

	//--- DRAW PLAYER'S ICON ---
	Brush icon;
	icon.texture = m_icon_img;
	icon.outline_opacity = 0.0f;
	drawRect(m_icon_posX, m_icon_posY, width, height, icon);
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
	drawRect(m_pawn_posX, m_pawn_posY, PLAYER_SIZE + 0.3f, PLAYER_SIZE + 0.3f, back);

	//--- DRAW PLAYER'S PAWN ---
	Brush pawn;
	pawn.texture = m_pawn_img;
	pawn.outline_opacity = 0.0f;
	drawRect(m_pawn_posX, m_pawn_posY, PLAYER_SIZE, PLAYER_SIZE + 0.1, pawn);
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
	drawRect(x + 1.2f, y, 1.0f, 1.0f, act2);

	Brush act3;
	act3.texture = ACTION_THREE;
	act3.outline_opacity = 0.0f;
	drawRect(x + 2.4f, y, 1.0f, 1.0f, act3);
}


/*_______________________________________________________

  >>>>> DRAW PLAYER FOR CHOOSING AND PLAYING STATES <<<<<
  _______________________________________________________
*/
void Player::draw()
{
	if (game->getState() == CHOOSE_PLAYER)
		drawIcon(7.0f, 4.0f);

	else if (game->getState() == PLAYING)
	{
		Brush br;
		br.outline_opacity = 0.0f;
		br.texture = PLAYER_CARD;
		setFont(FREESANS_FONT);

		if (m_turn == 1)
		{
			m_treasures[AIR]->setCords(1.5f, 14.5f);
			m_treasures[FIRE]->setCords(3.1f, 14.6f);
			m_treasures[EARTH]->setCords(4.5f, 14.6f);
			m_treasures[WATER]->setCords(5.7f, 14.5f);
			setIconCords(1.5f, 12.5f);

			drawRect(3.5f, 13.5f, 6.5f, 4.5f, br);
			drawActions(3.5f,13.0f);
			SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
			drawText(3.0f, 12.2f, 0.4f, "PLAYER " + to_string(m_turn) + " " + m_name, br);
		}
		else if (m_turn == 2)
		{
			m_treasures[AIR]->setCords(22.4f, 14.5f);
			m_treasures[FIRE]->setCords(24.0f, 14.6f);
			m_treasures[EARTH]->setCords(25.4f, 14.6f);
			m_treasures[WATER]->setCords(26.7f, 14.5f);
			setIconCords(22.5f, 12.5f);

			drawRect(24.5f, 13.5f, 6.5f, 4.5f, br);
			drawActions(24.5f, 13.0f);
			SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
			drawText(24.0f, 12.2f, 0.4f, "PLAYER " + to_string(m_turn) + " " + m_name, br);
		}
		drawPawn();
		drawIcon(3.5f, 2.0f);
		for (auto t : m_treasures)
			t.second->draw();
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
void Player::isStartTile(Tile* t)
{
	if ((t->getImage() == PILI_AGNOIAS && m_role == EXPLORER) ||
		(t->getImage() == PILI_PROSMONIS && m_role == DIVER) ||
		(t->getImage() == XEFWTO && m_role == PILOT))
	{
		setStandingTile(t);
		setCords(m_standing_tile->getPosX(), m_standing_tile->getPosY());
	}
}


/*____________________________________________

  >>>>> CHECK IF PLAYER IS INSIDE BOUNDS <<<<<
  ____________________________________________
*/
bool Player::contains(float x, float y)
{
	return (sqrt(pow(x - m_icon_posX, 2) + pow(y - m_icon_posY, 2))) < DEMO_PLAYER_SIZE;
}