#include "button.h"
#include "game.h"

using namespace graphics;

/*_______________________________________________________________________________

  >>>>> CREATE NEW BUTTON AND INITIALIZE IT'S MEMBERS BASED ON IT'S FUNCTION <<<<<
  _______________________________________________________________________________
*/
Button::Button(BUTTON_FUNC b, float center_width_offset, float center_height_offset, float width, float height) 
	: m_func(b), Clickable("", width, height, CANVAS_WIDTH / 2 + center_width_offset, CANVAS_HEIGHT / 2 + center_height_offset)
{
	switch (m_func)
	{
	case PLAY:
		m_img = PLAY_BUTTON;
		break;
	case HOW_TO:
		m_img = HOW_TO_PLAY_BUTTON;
		break;
	case ABOUT:
		m_img = ABOUT_BUTTON;
		break;
	case HELP:
		m_img = HELP_BUTTON;
		break;
	case HOME:
		m_img = HOME_BUTTON;
		break;
	case EXIT:
		m_img = EXIT_BUTTON;
		break;
	case NEXT:
		m_img = NEXT_BUTTON;
		break;
	case PREV:
		m_img = PREV_BUTTON;
		break;
	case OK:
		m_img = OK_BUTTON;
		break;
	case EASY:
		m_img = EASY_BUTTON;
		break;
	case MEDIUM:
		m_img = MEDIUM_BUTTON;
		break;
	case HARD:
		m_img = HARD_BUTTON;
		break;
	case LEGENDARY:
		m_img = LEGENDARY_BUTTON;
		break;
	}
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

	if (contains(mx, my))
	{
		// highlight button
		m_highlighted = true;

		if (ms.button_left_released)
		{
			switch (m_func)
			{
			case PLAY:
				playSound(BUTTON_CLICK, 1, false);
				game->setState(CHOOSE_ISLAND);
				break;

			case HOW_TO:
				playSound(BUTTON_CLICK, 1, false);
				game->setState(SHOW_HOW_TO);
				break;

			case ABOUT:
				playSound(BUTTON_CLICK, 1, false);
				//game->setState(SHOW_HOW_TO);
				break;

			case HELP:
				playSound(BUTTON_CLICK, 1, false);
				game->setState(SHOW_HOW_TO);
				break;

			case HOME:
				playSound(BUTTON_CLICK, 1, false);
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
				playSound(BUTTON_CLICK, 1, false);
				for (auto dp : game->getPlayers())
					if (dp.second == game->getActivePlayer())
					{
						dp.second->setSelected(true);
						dp.second->setPlayerTurn(game->getCurPlayer() + 1);
					}
				if (game->getCurPlayer()) 
					game->setState(CHOOSE_DIF);
				game->changePlayer();
				break;

			default:
				playSound(BUTTON_CLICK, 1, false);
				game->setDifficulty(m_func);
				game->setState(PLAYING);
			}
		}
	}
	else 
		m_highlighted = false;
}
