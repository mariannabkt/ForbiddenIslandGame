#include "game.h"
#include "defines.h"
#include "demoPlayer.h"
#include "sgg/graphics.h"

using namespace graphics;


void DemoPlayer::drawBackLight(float center_width_offset, float center_height_offset)
{
	Brush back;
	back.outline_opacity = 0.0f;

	if (isHighlighted() && !isActive())
		back.fill_opacity = 0.3f;
	else
		back.fill_opacity = 0.0f;

	if (isActive() || isSelected())
	{
		SETCOLOR(back.fill_color, m_color[0], m_color[1], m_color[2]);
		back.fill_opacity = 0.5f;
	}
	drawDisk(CANVAS_WIDTH / 2 + center_width_offset, CANVAS_HEIGHT / 2 + center_height_offset, DEMO_PLAYER_SIZE + 0.1f, back);
}

void DemoPlayer::draw()
{
	Game* game = Game::getInstance();

	DemoPlayer* explorer = game->getDemoPlayerMap().find(EXPLORER)->second;
	DemoPlayer* diver = game->getDemoPlayerMap().find(DIVER)->second;
	DemoPlayer* pilot = game->getDemoPlayerMap().find(PILOT)->second;

	//   --- DRAW PLAYER'S BACK LIGHT ---
	explorer->drawBackLight(-7.0f, 4.0f);
	diver->drawBackLight(0.0f, 4.0f);
	pilot->drawBackLight(7.0f, 4.0f);

	//   --- DRAW PLAYER'S ICON ---
	explorer->drawIcon(-7.0f, 4.0f, 7.0f, 4.0f);
	diver->drawIcon(0.0f, 4.0f, 7.0f, 4.0f);
	pilot->drawIcon(7.0f, 4.0f, 7.0f, 4.0f);
}

void DemoPlayer::update()
{
	Game* game = Game::getInstance();

	// obtain mouse state
	MouseState ms;
	getMouseState(ms);

	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	// highlight demo player
	if (contains(mx, my) && !isSelected())
	{
		setHighlight(true);

		// activate player
		if (ms.button_left_released)
		{
			setActive(true);
			game->setActivePlayer(this);

			// push selected demo player in the player list
			if (game->getPlayerList()->empty() || (game->getCurPlayer() && game->getPlayerList()->size() == 1))
				game->getPlayerList()->push_back(this);
			else
				game->getPlayerList()->emplace_back(this);

			// disable other players
			for (auto dp : game->getDemoPlayerMap())
			{
				if (dp.second != game->getActivePlayer())
					dp.second->setActive(false);
			}
		}
	}
	else
		setHighlight(false);
}

bool DemoPlayer::contains(float x, float y)
{
	return (distance(x, y, m_player_posX, m_player_posY) < DEMO_PLAYER_SIZE);
}
