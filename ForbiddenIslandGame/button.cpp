#include "button.h"
#include "game.h"

using namespace graphics;


/*_______________________________________________________________________________

  >>>>> CREATE NEW BUTTON AND INITIALIZE IT'S FIELDS BASED ON IT'S FUNCTION <<<<<
  _______________________________________________________________________________
*/
Button::Button(button_func b, float center_width_offset, float center_height_offset, float width, float height) 
	: m_func(b), m_button_posX(center_width_offset), m_button_posY(center_height_offset), 
	  m_button_width(width), m_button_height(height)
{
	switch (m_func)
	{
	case PLAY:
		m_button_img = PLAY_BUTTON;
		break;
	case HOW_TO:
		m_button_img = HOW_TO_PLAY_BUTTON;
		break;
	case HOME:
		m_button_img = HOME_BUTTON;
		break;
	case EXIT:
		m_button_img = EXIT_BUTTON;
		break;
	case NEXT:
		m_button_img = NEXT_BUTTON;
		break;
	case PREV:
		m_button_img = PREV_BUTTON;
		break;
	case OK:
		m_button_img = OK_BUTTON;
		break;
	}
	m_button_left  = CANVAS_WIDTH / 2 + center_width_offset - width / 2;
	m_button_right = CANVAS_WIDTH / 2 + center_width_offset + width / 2;
	m_button_up    = CANVAS_HEIGHT / 2 + center_height_offset - height / 2;
	m_button_down  = CANVAS_HEIGHT / 2 + center_height_offset + height / 2;
}


/*_______________________

  >>>>> DRAW BUTTON <<<<<
  _______________________
*/
void Button::draw()
{
	m_button_br.outline_opacity = 0.0f;
	m_button_br.fill_opacity = 1.0f * m_highlighted + 0.88f;
	m_button_br.texture = m_button_img;
	drawRect(CANVAS_WIDTH / 2 + m_button_posX, CANVAS_HEIGHT / 2 + m_button_posY, m_button_width, m_button_height, m_button_br);
}


/*_________________________

  >>>>> UPDATE BUTTON <<<<<
  _________________________
*/
void Button::update()
{
	Game* game = Game::getInstance();

	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	if (contains(mx, my))
	{
		// highlight button
		setHighlight(true);

		if (ms.button_left_released)
		{
			switch (m_func)
			{
			case PLAY:
				playSound(NOTIFICATION, 1, false);
				game->setState(CHOOSE_PLAYER);
				break;

			case HOW_TO:
				playSound(NOTIFICATION, 1, false);
				game->setState(HELP);
				break;

			case HOME:
				playSound(NOTIFICATION, 1, false);
				game->setState(MAIN_MENU);
				break;

			case EXIT:
				stopMessageLoop();
				break;

			case NEXT:
				game->flipNextPage();
				break;

			case PREV:
				game->flipPrevPage();
				break;

			case OK:
				playSound(NOTIFICATION, 1, false);
				for (auto dp : game->getPlayers())
					if (dp.second == game->getActivePlayer())
					{
						dp.second->setSelected(true);
						dp.second->setPlayersTurn(game->getCurPlayer() + 1);
						dp.second->getStartTile()->setTaken(true);
					}
				if (game->getCurPlayer()) 
					game->setState(PLAYING);
				game->changePlayer();
				break;
			}
		}
	}
	else 
		setHighlight(false);
}


/*____________________________________________

  >>>>> CHECK IF BUTTON IS INSIDE BOUNDS <<<<<
  ____________________________________________
*/
bool Button::contains(float x, float y)
{
	return (x > m_button_left && x < m_button_right && y > m_button_up && y < m_button_down);
}