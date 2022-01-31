#include "sgg/graphics.h"
#include "button.h"
#include "game.h"

using namespace graphics;

/*_______________________________________

  >>>>> CREATE NEW CLICKABLE BUTTON <<<<<
  _______________________________________
*/
Button::Button(BUTTON_FUNC b, string img, float center_width_offset, float center_height_offset, float width, float height) 
	: m_func(b), Clickable(img, width, height, CANVAS_WIDTH / 2 + center_width_offset, CANVAS_HEIGHT / 2 + center_height_offset)
{
}


/*_______________________

  >>>>> DRAW BUTTON <<<<<
  _______________________
*/
void Button::draw()
{
	m_br.outline_opacity = 0.0f;
	m_br.fill_opacity = 1.0f * m_highlighted + 0.88f;
	m_br.texture = m_img;
	drawRect(m_posX, m_posY, m_width, m_height, m_br);
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

	// if mouse is on top of button
	if (contains(mx, my))
	{
		// highlight button
		if (!m_highlighted) {
			playSound(TOUCH_SOUND, 1, false);
			m_highlighted = true;
			lift();
		}

		// and if clicked
		if (ms.button_left_released)
		{
			// do something based on it's function
			switch (m_func)
			{
			case PLAY:
				playSound(BUTTON_CLICK2, 1, false);
				game->setState(CHOOSE_ISLAND);
				break;

			case HOW_TO:
				playSound(BUTTON_CLICK2, 1, false);
				game->setState(SHOW_HOW_TO);
				break;

			case ABOUT:
				playSound(BUTTON_CLICK2, 1, false);
				game->setState(INFO);
				break;

			case HOME:
				playSound(BUTTON_CLICK1, 1, false);
				game->setState(MAIN_MENU);
				break;

			case EXIT:
				stopMessageLoop();
				break;

			case HELP:
				playSound(BUTTON_CLICK1, 1, false);
				game->setState(SHOW_HOW_TO);
				break;

			case PLAY_AGAIN:
				playSound(BUTTON_CLICK2, 1, false);
				game->setState(CHOOSE_ISLAND);
				break;

			case NEXT:
				game->flipNextPage();
				break;

			case PREV:
				game->flipPrevPage();
				break;

			case OK:
				playSound(BUTTON_CLICK1, 1, false);
				for (auto dp : game->getPlayers())
					if (dp.second == game->getActivePlayer())
					{
						dp.second->setSelected(true);
						dp.second->setPlayerTurn(game->getCurPlayer() + 1);
					}
				if (game->getCurPlayer()) 
					game->setState(CHOOSE_DIF);
				else
					game->changePlayer();
				break;

			default:
				playSound(BUTTON_CLICK1, 1, false);
				game->setDifficulty(m_func);
				game->setState(PLAYING);
			}
		}
	}
	else {
		m_highlighted = false;
		if (m_lifted)
			unlift();
	}
}
