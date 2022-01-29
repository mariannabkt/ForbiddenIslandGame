#include "action.h"
#include "defines.h"
#include "player.h"
#include "sgg/graphics.h"

using namespace graphics;


/*___________________________________________
*
* >>>>> DRAW REMAINING PLAYER'S ACTIONS <<<<<
* ___________________________________________
*/
void Action::draw()
{
	Brush act1;
	act1.texture = ACTION_ONE;
	act1.outline_opacity = 0.0f;
	act1.fill_opacity = 0.6f + 1 * (m_player_performing->isActive() && m_remaining > 0);
	drawRect(m_posX, m_posY, 1.0f, 1.0f, act1);

	Brush act2;
	act2.texture = ACTION_TWO;
	act2.outline_opacity = 0.0f;
	act2.fill_opacity = 0.6f + 1 * (m_player_performing->isActive() && m_remaining > 1);
	drawRect(m_posX + 1.2f, m_posY, 1.0f, 1.0f, act2);

	Brush act3;
	act3.texture = ACTION_THREE;
	act3.outline_opacity = 0.0f;
	act3.fill_opacity = 0.6f + 1 * (m_player_performing->isActive() && m_remaining == 3);
	drawRect(m_posX + 2.4f, m_posY, 1.0f, 1.0f, act3);
}

void Action::update()
{
	Game* game = Game::getInstance();

	--m_remaining;
	if (m_remaining == 0) {
		
			if (m_player_performing->getPlayerTurn() == 1 && m_player_performing == game->getActivePlayer())
				for (auto p : game->getPlayers())
					if (p.second->getPlayerTurn() == 2)
					{
						game->setActivePlayer(p.second);
						game->floodTiles();
					}
			if (m_player_performing->getPlayerTurn() == 2 && m_player_performing == game->getActivePlayer())
				for (auto p : game->getPlayers())
					if (p.second->getPlayerTurn() == 1)
					{
						game->setActivePlayer(p.second);
						game->floodTiles();
					}
		m_player_performing->setActive(false);
		m_remaining = 3;
	}
}
