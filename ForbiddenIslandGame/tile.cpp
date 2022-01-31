#include "tile.h"
#include "game.h"
#include "event.h"
#include "defines.h"
#include "action.h"
#include "player.h"

using namespace graphics;


/*__________________________________________________________________________

  >>>>> CREATE NEW TILE AND INITIALIZE IT'S MEMBERS BASED ON IT'S NAME <<<<<
  __________________________________________________________________________
*/
Tile::Tile(string tile_name) : Clickable(tile_name, TILE_SIZE, TILE_SIZE)
{
	Game* game = Game::getInstance();

	if (m_img == XEFWTO) {
		m_type = LANDING;
	}
	else if (m_img == KIPOS_KRA || m_img == KIPOS_PSI)
	{
		m_treasure = new Treasure(AIR);
		game->getTreasures()[m_img] = m_treasure;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_img == NAOS_FEGGARIOY || m_img == NAOS_ILIOY)
	{
		m_treasure = new Treasure(EARTH);
		game->getTreasures()[m_img] = m_treasure;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_img == PALATI_KOR || m_img == PALATI_PAL)
	{
		m_treasure = new Treasure(WATER);
		game->getTreasures()[m_img] = m_treasure;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_img == SPILIA_LAVAS || m_img == SPILIA_SKIWN)
	{
		m_treasure = new Treasure(FIRE);
		game->getTreasures()[m_img] = m_treasure;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else
		m_type = BASIC;
}


/*_________________________________________________________
* 
  >>>>> INIT NECESSARY MEMBERS FOR EVERY PLAY SESSION <<<<<
  _________________________________________________________
*/
void Tile::init()
{
	m_sunken = false;;
	m_flooded = false;;
	m_hasPlayer = false;
	m_canPerformAction = false;
	if (m_img.find("_nt.png") < m_img.length())
		m_img.replace(m_img.find("_nt.png"), m_img.length() - 3, ".png");
	if (m_hasTreasure)
		m_treasure->setCollected(false);
}


/*_____________________
* 
  >>>>> DRAW TILE <<<<<
  _____________________
*/
void Tile::draw()
{
	m_br.outline_width = 3.0f;
	m_br.fill_opacity = 1.0f * !m_sunken;
	m_br.outline_opacity = 1.0f * m_canPerformAction;
	m_br.texture = m_img;
	drawRect(m_posX, m_posY, m_width, m_height, m_br);

	Brush water;
	water.outline_opacity = 0.0f;
	water.fill_opacity = 0.2f * (m_flooded && !m_sunken);
	SETCOLOR(water.fill_color, 0.0f, 0.0f, 0.8f);
	drawRect(m_posX, m_posY, m_width, m_height, water);

	/*if (m_hasTreasure && m_treasure->isCollected())
		m_treasure->draw();*/
}


/*_______________________
* 
  >>>>> UPDATE TILE <<<<<
  _______________________
*/
void Tile::update()
{
	Game* game = Game::getInstance();
	Player* p = game->getActivePlayer();
	Tile* t = p->getStandingTile();

	checkCanPerfomrAction();

	// obtain mouse state
	MouseState ms;
	graphics::getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// if tile clicked
	if (contains(mx, my) && ms.button_left_released && m_canPerformAction)
	{
		// and flooded
		if (m_flooded)
		{
			// unflood
			m_flooded = false;
			// and if diver also move
			if (p->getPlayerRole() == DIVER) {
				t->setTaken(false);
				p->move(this);
			}
		}
		// or active player is on top of this and wants to collect treasure
		else if (this == t && m_hasTreasure && !m_treasure->isCollected())
		{
			// replace tile image with the no treasure one
			m_img.replace(m_img.find(".png"), m_img.length() + 3, "_nt.png");

			// and collect treasure
			m_treasure->setCollected(true);
			Treasure* player_tr = p->getTreasures().find(m_treasure->getType())->second;
			playSound(TREASURE_SOUND, 1.0f, false);
			//game->addEvent(new ZoomOutEvent(m_treasure));
			game->addEvent(new MotionEvent<Treasure*, Treasure*>(m_treasure, player_tr));
			player_tr->setCollected(true);
		}
		// else just move to this tile
		else
		{
			// previous tile is not taken anymore
			t->setTaken(false);
			p->move(this);	
		}
		p->getActions()->update();
	}
}


/*__________________________________________________________________
* 
  >>>>> CHECK IF ACTIVE PLAYER CAN PERFORM ACTION AT THIS TILE <<<<<
  __________________________________________________________________
*/
void Tile::checkCanPerfomrAction()
{
	Game* game = Game::getInstance();
	Player* p = game->getActivePlayer();
	Tile* t = p->getStandingTile();

	if (m_sunken)
		return;

	bool isAdjacent =
		// left tile
		(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ()) ||
		// right tile
		(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ()) ||
		// top tile
		(m_grid_j == t->getPosJ() - 1 && m_grid_i == t->getPosI()) ||
		// buttom tile
		(m_grid_j == t->getPosJ() + 1 && m_grid_i == t->getPosI());

	bool isDiagonial =
		// left top tile
		(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ() - 1) ||
		// left buttom tile
		(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ() + 1) ||
		// right top tile
		(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ() - 1) ||
		// right buttom tile
		(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ() + 1);

	bool is2TilesAway =
		// left's left tile
		(m_grid_i == t->getPosI() - 2 && m_grid_j == t->getPosJ()) ||
		// right's right tile
		(m_grid_i == t->getPosI() + 2 && m_grid_j == t->getPosJ()) ||
		// top's top tile
		(m_grid_j == t->getPosJ() - 2 && m_grid_i == t->getPosI()) ||
		// buttom's buttom tile
		(m_grid_j == t->getPosJ() + 2 && m_grid_i == t->getPosI());

	// active player's standing tile (he can unflood or collect treasure)
	bool isOnTop = ((m_hasTreasure && !m_treasure->isCollected() && !p->getTreasures().find(m_treasure->getType())->second->isCollected()) 
		|| m_flooded) && this == t ;

	m_canPerformAction = 
		// explorer can move and/or shore up adjacent and diagonial tiles
		(((!m_hasPlayer && (isAdjacent || isDiagonial)) || isOnTop) && p->getPlayerRole() == EXPLORER) ||

		// diver can move and/or shore up adjacent tiles
		(((!m_hasPlayer && isAdjacent) || isOnTop) && p->getPlayerRole() == DIVER) ||

		// pilot can move and/or shore up two tiles away
		(((!m_hasPlayer && (isAdjacent || is2TilesAway)) || isOnTop) && p->getPlayerRole() == PILOT);
}