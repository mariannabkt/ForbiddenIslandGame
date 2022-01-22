#include "button.h"
#include "game.h"


Button::Button(button_func b) : m_func(b)
{
	switch (m_func)
	{
	case PLAY:
		m_image_path = PLAY_BUTTON;
		break;
	case HOW_TO:
		m_image_path = HOW_TO_PLAY_BUTTON;
		break;
	case EXIT:
		m_image_path = EXIT_BUTTON;
		break;
	case NEXT:
		m_image_path = NEXT_BUTTON;
		break;
	case PREV:
		m_image_path = PREV_BUTTON;
		break;
	case OK:
		m_image_path = OK_BUTTON;
		break;
	}
}

void Button::drawButton(float center_width_offset, float center_height_offset, float width, float height)
{
	m_button_left = CANVAS_WIDTH / 2 + center_width_offset - width / 2;
	m_button_right = CANVAS_WIDTH / 2 + center_width_offset + width / 2;
	m_button_up = CANVAS_HEIGHT / 2 + center_height_offset - height / 2;
	m_button_down = CANVAS_HEIGHT / 2 + center_height_offset + height / 2;

	button.outline_opacity = 0.0f;
	button.fill_opacity = 1.0f * m_highlighted + 0.85f;
	button.texture = m_image_path;
	drawRect(CANVAS_WIDTH / 2 + center_width_offset, CANVAS_HEIGHT / 2 + center_height_offset, width, height, button);
}

void Button::updateButton()
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
				game->setState(CHOOSE_PLAYER);
				game->init();
				break;

			case HOW_TO:
				game->setState(HELP);
				game->init();
				break;

			case EXIT:
				stopMessageLoop();
				break;

			case NEXT:
				
				switch (game->getPage())
				{
				case ONE:
					game->setPage(TWO);
					break;
				case TWO:
					game->setPage(THREE);
					break;
				case THREE:
					game->setPage(FOUR);
					break;
				case FOUR:
					game->setPage(ONE);
					game->setState(MAIN_MENU);
					game->init();
					break;

				}
				break;

			case PREV:
				
				switch (game->getPage())
				{
				case ONE:
					game->setState(MAIN_MENU);
					game->init();
					break;
				case TWO:
					game->setPage(ONE);
					break;
				case THREE:
					game->setPage(TWO);
					break;
				case FOUR:
					game->setPage(THREE);
					break;
				}
				break;

			case OK:

				if (!game->getCurPlayer())
				{
					for (auto dp : game->getDemoPlayers())
						if (dp.second == game->getActivePlayer())
						{
							dp.second->setSelected(true);
							game->getPlayers().push_back(dp.second);
							break;
						}
					game->changePlayer();
				}
				else if (game->getCurPlayer())
				{ 
					for (auto dp : game->getDemoPlayers())
						if (dp.second == game->getActivePlayer())
						{
							dp.second->setSelected(true);
							game->getPlayers().push_back(dp.second);
						}
					DemoPlayer::setDefault();
					game->changePlayer();
					game->setState(PLAYING);
					game->init();
				}

				break;
			}
		}
	}
	else 
		setHighlight(false);
}


bool Button::contains(float x, float y)
{
	return (x > m_button_left && x < m_button_right && y > m_button_up && y < m_button_down);
}
