#include "tilesLayout.h"
#include "sgg\graphics.h"
#include "game.h"

using namespace graphics;


TilesLayout::TilesLayout(string img) : Clickable(img, LAYOUT_IMG_SIZE, LAYOUT_IMG_SIZE)
{
	if (m_img == SKULL_IMAGE)
	{
		m_posX = -8.0f;
		m_posY = -2.0f;
		m_rows = 6;
		m_cols = 6;
		memcpy(m_layout, SKULL_ISLAND, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == BAY_IMAGE)
	{
		m_posX = -4.0f;
		m_posY = -2.0f;
		m_rows = 6;
		m_cols = 8;
		memcpy(m_layout, BAY_OF_GULLS, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == HARPOON_IMAGE)
	{
		m_posX = 4.0f;
		m_posY = -2.0f;
		m_rows = 6;
		m_cols = 6;
		memcpy(m_layout, HARPOON_HIDEOUT, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == ATOLL_IMAGE)
	{
		m_posX = 8.0f;
		m_posY = -2.0f;
		m_rows = 7;
		m_cols = 7;
		memcpy(m_layout, ATOLL_OF_DECISIONS, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == SHIPWRECK_IMAGE)
	{
		m_posX = -8.0f;
		m_posY = 4.0f;
		m_rows = 4;
		m_cols = 8;
		memcpy(m_layout, SHIPWRECK_BAY, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == DAVY_IMAGE)
	{
		m_posX = -4.0f;
		m_posY = 4.0f;
		m_rows = 6;
		m_cols = 9;
		memcpy(m_layout, DAVY_JONES, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == MUTINY_IMAGE)
	{
		m_posX = 4.0f;
		m_posY = 4.0f;
		m_rows = 6;
		m_cols = 7;
		memcpy(m_layout, MUTINY_TOWERS, m_rows * m_cols * sizeof(int));
	}
	else if (m_img == PALM_IMAGE)
	{
		m_posX = 8.0f;
		m_posY = 4.0f;
		m_rows = 6;
		m_cols = 5;
		memcpy(m_layout, PALM_SPINGS, m_rows * m_cols * sizeof(int));
	}
}

void TilesLayout::draw()
{
	m_br.outline_width = 3.0f;
	m_br.outline_opacity = 1.0f * m_highlighted || m_selected;
	m_br.texture = m_img;
	drawRect(m_posX, m_posY, m_width, m_height, m_br);
}


void TilesLayout::update()
{
	Game* game = Game::getInstance();

	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// highlight tile layout image
	if (contains(mx, my) && !isSelected())
	{
		setHighlight(true);
		
		// set selected for the play session
		if (ms.button_left_released)
		{
			game->setLayout(this);

			// disable other tile layouts
			for (auto l : game->getLayouts())
				if (l->isSelected())
					setSelected(false);

			game->setState(CHOOSE_PLAYER);
		}
		
	}
	else
		setHighlight(false);
}

