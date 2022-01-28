#include "tilesLayout.h"
#include "sgg\graphics.h"
#include "game.h"

using namespace graphics;


TilesLayout::TilesLayout(int* l) : m_layout(l) 
{

}

void TilesLayout::draw()
{
	Brush br;
	br.outline_width = 3.0f;
	br.outline_opacity = 1.0f * m_highlighted || m_selected;
	br.texture = m_layout_img;
	drawRect(m_img_posX, m_img_posY, LAYOUT_IMG_SIZE, LAYOUT_IMG_SIZE, br);
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


/*__________________________________________________________

  >>>>> CHECK IF MOUSE IS INSIDE LAYOUT'S IMAGE BOUNDS <<<<<
  __________________________________________________________
*/
bool TilesLayout::contains(float x, float y)
{
	return (x > m_img_left && x < m_img_right && y > m_img_up && y < m_img_down);
}