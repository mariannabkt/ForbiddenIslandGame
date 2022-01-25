#include "tile.h"
#include "game.h"
#include "defines.h"

using namespace graphics;

/*_________________________________________________________________________

  >>>>> CREATE NEW TILE AND INITIALIZE IT'S FIELDS BASED ON IT'S TYPE <<<<<
  _________________________________________________________________________
*/
Tile::Tile(string tile_name) : m_tile_img(tile_name) 
{
	if (m_tile_img == XEFWTO)
		m_type = LANDING;
	else if (m_tile_img == KIPOS_KRA || m_tile_img == KIPOS_PSI)
	{
		m_type = AIR;
		m_hasTreasure = true;
	}
	else if (m_tile_img == NAOS_FEGGARIOY || m_tile_img == NAOS_ILIOY)
	{
		m_type = EARTH;
		m_hasTreasure = true;
	}
	else if (m_tile_img == PALATI_KOR || m_tile_img == PALATI_PAL)
	{
		m_type = WATER;
		m_hasTreasure = true;
	}
	else if (m_tile_img == SPILIA_LAVAS || m_tile_img == SPILIA_SKIWN)
	{
		m_type = FIRE;
		m_hasTreasure = true;
	}
	else 
		m_type = BASIC;
}


/*________________________________________________________

  >>>>> INIT NECESSARY FIELDS FOR EVERY PLAY SESSION <<<<<
  ________________________________________________________
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
	tile.fill_opacity = 1.0f * !m_sunken;
	tile.outline_opacity = 1.0f * m_canPerformAction;
	tile.texture = m_tile_img;
	drawRect(m_tile_posX, m_tile_posY, TILE_SIZE, TILE_SIZE, tile);

	Brush water;
	if (m_flooded)
	{
		SETCOLOR(water.fill_color, 0.0f, 0.0f, 0.5f);
		drawRect(m_tile_posX, m_tile_posY, TILE_SIZE, TILE_SIZE, water);
	}
}


/*_______________________

  >>>>> UPDATE TILE <<<<<
  _______________________
*/
void Tile::update()
{
	Game* game = Game::getInstance();
	Player* p = game->getActivePlayer();
	Tile* t = game->getActivePlayer()->getStandingTile();

	switch (p->getPlayerRole())
	{
	case EXPLORER:
		if (((!m_hasPlayer && this != t) &&

			(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ()) ||

			(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ()) ||

			(m_grid_i == t->getPosI() && m_grid_j == t->getPosJ() - 1) ||

			(m_grid_i == t->getPosI() && m_grid_j == t->getPosJ() + 1) ||

			(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ() - 1) ||

			(m_grid_i == t->getPosI() - 1 && m_grid_j == t->getPosJ() + 1) ||

			(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ() - 1) ||

			(m_grid_i == t->getPosI() + 1 && m_grid_j == t->getPosJ() + 1)) ||

			(m_grid_i == t->getPosI() && m_grid_j == t->getPosJ() 
				&& (m_flooded || (m_hasTreasure && !m_treasureTaken))))
			setCanPerformAction(true);
		break;

	case DIVER:
		if (((!m_hasPlayer && this != t) &&
									  
			             (m_grid_i == t->getPosI() - 1
				       && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI() + 1
				       && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() - 1) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() + 1)) ||

			(m_grid_i == t->getPosI() && m_grid_j == t->getPosJ()
				&& (m_flooded || (m_hasTreasure && !m_treasureTaken))))
			setCanPerformAction(true);
		break;

	case PILOT:
		if (((!m_hasPlayer && this != t) &&
									  
			             (m_grid_i == t->getPosI() - 1
				       && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI() + 1
			       	   && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() - 1) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() + 1) ||
									  
			             (m_grid_i == t->getPosI() - 2
				       && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI() + 2
				       && m_grid_j == t->getPosJ()) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() - 2) ||
									  
			             (m_grid_i == t->getPosI()
				       && m_grid_j == t->getPosJ() + 2)) ||

			(m_grid_i == t->getPosI() && m_grid_j == t->getPosJ()
				&& (m_flooded || (m_hasTreasure && !m_treasureTaken))))
			setCanPerformAction(true);
		break;
	}

	// obtain mouse state
	MouseState ms;
	graphics::getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// highlight demo player
	if (contains(mx, my))
	{
		if (ms.button_left_released)
		{

		}
	}
	
}


/*____________________________________________

  >>>>> CHECK IF TILE IS INSIDE BOUNDS <<<<<
  ____________________________________________
*/
bool Tile::contains(float x, float y)
{
	return (distance(x, y, m_tile_posX, m_tile_posY) < TILE_SIZE);
}