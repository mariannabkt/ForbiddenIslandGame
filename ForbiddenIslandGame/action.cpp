#include "action.h"
#include "defines.h"
#include "game.h"
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
		game->changePlayer();
		game->floodTiles();
		m_remaining = 3;
	}
}
