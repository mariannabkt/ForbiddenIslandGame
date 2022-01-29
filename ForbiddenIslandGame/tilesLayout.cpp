#include "tilesLayout.h"
#include "sgg\graphics.h"
#include "game.h"

using namespace graphics;


TilesLayout::TilesLayout(int* l) : m_layout(l), Clickable("", LAYOUT_IMG_SIZE, LAYOUT_IMG_SIZE)
{

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
		}
	}
	else
		setHighlight(false);
}

