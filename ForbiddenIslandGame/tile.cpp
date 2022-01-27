#include "tile.h"
#include "game.h"
#include "event.h"
#include "defines.h"

using namespace graphics;


/*__________________________________________________________________________

  >>>>> CREATE NEW TILE AND INITIALIZE IT'S MEMBERS BASED ON IT'S TYPE <<<<<
  __________________________________________________________________________
*/
Tile::Tile(string tile_name) : m_tile_img(tile_name)
{
	if (m_tile_img == XEFWTO) {
		m_type = LANDING;
	}
	else if (m_tile_img == KIPOS_KRA || m_tile_img == KIPOS_PSI)
	{
		m_treasure = AIR;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_tile_img == NAOS_FEGGARIOY || m_tile_img == NAOS_ILIOY)
	{
		m_treasure = EARTH;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_tile_img == PALATI_KOR || m_tile_img == PALATI_PAL)
	{
		m_treasure = WATER;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else if (m_tile_img == SPILIA_LAVAS || m_tile_img == SPILIA_SKIWN)
	{
		m_treasure = FIRE;
		m_type = TREASURE;
		m_hasTreasure = true;
	}
	else 
		m_type = BASIC;
}


/*_________________________________________________________

  >>>>> INIT NECESSARY MEMBERS FOR EVERY PLAY SESSION <<<<<
  _________________________________________________________
*/
void Tile::init()
{
	m_sunken = false;;
	m_flooded = false;;
	m_treasureTaken = false;
	m_hasPlayer = false;
}


/*_____________________

  >>>>> DRAW TILE <<<<<
  _____________________
*/
void Tile::draw()
{
	Brush tile;
	tile.outline_width = 3.0f;
	//tile.fill_opacity = 0.3f * !m_flooded;
	//SETCOLOR(tile.fill_color, 0.0f, 0.0f, 0.5f);
	tile.outline_opacity = 1.0f * m_canPerformAction;
	tile.texture = m_tile_img;
	drawRect(m_tile_posX, m_tile_posY, TILE_SIZE, TILE_SIZE, tile);
}


/*_______________________

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

	// highlight demo player
	if (contains(mx, my) && m_canPerformAction)
	{
		if (ms.button_left_released)
		{
			if (m_flooded)
			{
				m_flooded = false;
			}
			else
			{
				game->addEvent(new MotionEvent<Player*, Tile*>(p, this));
				p->setStandingTile(this);
				t->setTaken(false);
			}
		}
	}
	
}


/*____________________________________________

  >>>>> CHECK IF TILE IS INSIDE BOUNDS <<<<<
  ____________________________________________
*/
bool Tile::contains(float x, float y)
{
	return (x > m_tile_left && x < m_tile_right && y > m_tile_up && y < m_tile_down);
}


/*_______________________________________

  >>>>> SET TILE'S CORDS AND BOUNDS <<<<<
  _______________________________________
*/
void Tile::setCords(float x, float y)
{
	m_tile_posX = x; 
	m_tile_posY = y; 

	m_tile_left = m_tile_posX - TILE_SIZE / 2;
	m_tile_right = m_tile_posX + TILE_SIZE / 2;
	m_tile_up = m_tile_posY - TILE_SIZE / 2;
	m_tile_down = m_tile_posY + TILE_SIZE / 2;
}


/*__________________________________________________________________

  >>>>> CHECK IF ACTIVE PLAYER CAN PERFORM ACTION AT THIS TILE <<<<<
  __________________________________________________________________
*/
void Tile::checkCanPerfomrAction()
{
	Game* game = Game::getInstance();
	Player* p = game->getActivePlayer();
	Tile* t = p->getStandingTile();

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

	// active player's standing tile
	bool isOnTop = (m_flooded || (m_hasTreasure && !m_treasureTaken)) && this == t;

	m_canPerformAction =
		// explorer can move and/or shore up adjacent and diagonial tiles
		(((!m_hasPlayer && (isAdjacent || isDiagonial)) || isOnTop && p->getPlayerRole() == EXPLORER) ||

		// diver can move and/or shore up adjacent tiles
		((!m_hasPlayer && isAdjacent) || isOnTop && p->getPlayerRole() == DIVER) ||

		// pilot can move and/or shore up two tiles away
		((!m_hasPlayer && (isAdjacent || is2TilesAway)) || isOnTop && p->getPlayerRole() == PILOT));
}
