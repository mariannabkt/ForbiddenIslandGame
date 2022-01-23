#include "game.h"
#include "defines.h"
#include "demoPlayer.h"
#include "sgg/graphics.h"

using namespace graphics;


void DemoPlayer::drawBackLight(float x, float y)
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
	drawDisk(x, y, DEMO_PLAYER_SIZE + 0.1f, back);
}

void DemoPlayer::drawDemoPlayer()
{
	Game* game = Game::getInstance();

	DemoPlayer* explorer = game->getDemoPlayers()[EXPLORER];
	DemoPlayer* diver = game->getDemoPlayers()[DIVER];
	DemoPlayer* pilot = game->getDemoPlayers()[PILOT];

	explorer->setCords(CANVAS_WIDTH / 2 - 7.0f, CANVAS_HEIGHT / 2 + 4.0f);
	diver->setCords(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 4.0f);
	pilot->setCords(CANVAS_WIDTH / 2 + 7.0f, CANVAS_HEIGHT / 2 + 4.0f);

	//   --- DRAW PLAYER'S BACK LIGHT ---
	explorer->drawBackLight(m_posDemo_x, m_posDemo_y);
	diver->drawBackLight(m_posDemo_x, m_posDemo_y);
	pilot->drawBackLight(m_posDemo_x, m_posDemo_y);

	//   --- DRAW PLAYER'S ICON ---
	explorer->drawIcon(m_posDemo_x, m_posDemo_y, 7.0f, 4.0f);
	diver->drawIcon(m_posDemo_x, m_posDemo_y, 7.0f, 4.0f);
	pilot->drawIcon(m_posDemo_x, m_posDemo_y, 7.0f, 4.0f);
}

void DemoPlayer::updateDemoPlayer()
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

			// disable other players
			for (auto dp : game->getDemoPlayers())
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

void DemoPlayer::setDefault()
{
	Game* game = Game::getInstance();
	for (auto dp : game->getDemoPlayers())
	{
		dp.second->setActive(false);
		dp.second->setSelected(false);
	}
}


