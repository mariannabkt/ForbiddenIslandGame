#include "tilesLayout.h"
#include "sgg\graphics.h"
#include "game.h"
#include <algorithm>

using namespace graphics;

/*____________________________________________

  >>>>> CREATE NEW LAYOUT BASED ON IMAGE <<<<<
  ____________________________________________
*/
TilesLayout::TilesLayout(string img) : Clickable(img, LAYOUT_IMG_SIZE, LAYOUT_IMG_SIZE)
{
	if (m_img == SKULL_IMAGE)
	{
		setCords(CANVAS_WIDTH / 2 - 9.0f, CANVAS_HEIGHT / 2 - 1.0f);
		m_posX_offset = 3.3f;
		m_posY_offset = 1.0f;
		initArray(m_rows = 6, m_cols = 5);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++) 
				m_layout[i][j] = SKULL_ISLAND[i][j];
	}
	else if (m_img == BAY_IMAGE)
	{
		m_posX_offset = 2.3f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 - 3.0f, CANVAS_HEIGHT / 2 - 1.0f);
		initArray(m_rows = 8, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = BAY_OF_GULLS[i][j];
	}
	else if (m_img == HARPOON_IMAGE)
	{
		m_posX_offset = 3.2f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 + 3.0f, CANVAS_HEIGHT / 2 - 1.0f);
		initArray(m_rows = 6, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = HARPOON_HIDEOUT[i][j];
	}
	else if (m_img == ATOLL_IMAGE)
	{
		m_posX_offset = 3.0f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 + 9.0f, CANVAS_HEIGHT / 2 - 1.0f);
		initArray(m_rows = 7, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = ATOLL_OF_DECISIONS[i][j];
	}
	else if (m_img == SHIPWRECK_IMAGE)
	{
		m_posX_offset = 2.5f;
		m_posY_offset = 0.85f;
		setCords(CANVAS_WIDTH / 2 - 9.0f, CANVAS_HEIGHT / 2 + 4.0f);
		initArray(m_rows = 8, m_cols = 4);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = SHIPWRECK_BAY[i][j];
	}
	else if (m_img == DAVY_IMAGE)
	{
		m_posX_offset = 1.3f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 - 3.0f, CANVAS_HEIGHT / 2 + 4.0f);
		initArray(m_rows = 9, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = DAVY_JONES[i][j];
	}
	else if (m_img == MUTINY_IMAGE)
	{
		m_posX_offset = 3.4f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 + 3.0f, CANVAS_HEIGHT / 2 + 4.0f);
		initArray(m_rows = 6, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = MUTINY_TOWERS[i][j];
	}
	else if (m_img == PALM_IMAGE)
	{
		m_posX_offset = 2.9f;
		m_posY_offset = 0.7f;
		setCords(CANVAS_WIDTH / 2 + 9.0f, CANVAS_HEIGHT / 2 + 4.0f);
		initArray(m_rows = 7, m_cols = 6);
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
				m_layout[i][j] = PALM_SPINGS[i][j];
	}
}


/*__________________________________________________________

  >>>>> DRAW TILE LAYOUT IMAGE SO PLAYER CAN CHOOSE IT <<<<<
  __________________________________________________________
*/
void TilesLayout::draw()
{
	m_br.outline_width = 3.0f;
	float h = 1.0f * m_highlighted;
	SETCOLOR(m_br.outline_color, h, h, h);
	m_br.texture = m_img;
	drawRect(m_posX, m_posY, m_width, m_height, m_br);
}


/*_________________________________

  >>>>> UPDATE LAYOUT  BUTTON <<<<<
  _________________________________
*/
void TilesLayout::update()
{
	Game* game = Game::getInstance();

	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// highlight tile layout image
	if (contains(mx, my) && !m_selected)
	{
		m_highlighted = true;
		
		// set selected for the play session
		if (ms.button_left_released)
		{
			game->setLayout(this);
			game->rearrangeTileGrid();

			// disable other tile layouts
			for (auto l : game->getLayouts())
				if (l->m_selected)
					m_selected = false;

			game->setState(CHOOSE_PLAYER);
		}
		
	}
	else
		m_highlighted = false;
}


/*_____________________________

  >>>>> INIT LAYOUT ARRAY <<<<<
  _____________________________
*/
void TilesLayout::initArray(int x, int y)
{
	m_layout = new int* [x];
	for (int i = 0; i < x; i++)
		m_layout[i] = new int[y];
}