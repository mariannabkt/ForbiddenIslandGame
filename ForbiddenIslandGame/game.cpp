#include "defines.h"
#include "game.h"
#include "button.h"
#include "tile.h"
#include <sgg/graphics.h>

using namespace graphics;
using namespace std;

Game* Game::m_instance = nullptr;


/*_________________________________________

  >>>>> INITIALIZE GAME'S COLLECTIONS <<<<<
  _________________________________________
*/
Game::Game()
{
	// init button list
	m_buttons[EXIT]   = new Button(EXIT, 13.0f, -7.0f, 1.0f, 1.0f);
	m_buttons[HOME]	  = new Button(HOME, 11.7f, -7.0f, 1.0f, 1.0f);
	m_buttons[PLAY]   = new Button(PLAY, -8.0f, 4.5f, 5.0f, 2.0f);
	m_buttons[HOW_TO] = new Button(HOW_TO, -1.0f, 4.5f, 7.0f, 2.0f);
	m_buttons[NEXT]   = new Button(NEXT, 12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[PREV]   = new Button(PREV, -12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[OK]     = new Button(OK, 11.0f, 6.0f, 1.0f, 1.0f);

	// init player list
	m_players[EXPLORER] = new Player(EXPLORER);
	m_players[DIVER]    = new Player(DIVER);
	m_players[PILOT]    = new Player(PILOT);

	// fill tile names(image paths) array
	string tile_names[20] = { LIMNI , DASOS, PARATIRITIRIO, LAGADI, VALTOS, AMMOLOFOI, ASTEROSKOPEIO,
		VRAXOS, GEFIRA, KIPOS_PSI, KIPOS_KRA, NAOS_ILIOY, NAOS_FEGGARIOY,PALATI_PAL,
		PALATI_KOR, SPILIA_LAVAS, SPILIA_SKIWN, PILI_AGNOIAS, PILI_PROSMONIS, XEFWTO };

	// init grid tiles
	for (int i = 0; i < 20; ++i)
		m_tiles[i] = new Tile(tile_names[i]);

	// based on the playing grid
	int t = 0;
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 4; ++j)
			if (Tile::getTilesGrid()[i][j])
			{
				// set cords for every grid tile
				m_tiles[t]->setCords((i + 3.5f) * (TILE_SIZE + 0.2f), (j + 1.0f) * (TILE_SIZE + 0.8f));

				// set player's pawn cords
				for (auto p : m_players)
					p.second->isStartTile(m_tiles[t]);
				++t;
			}
	// preload assets
	preloadBitmaps(ASSET_PATH);
	/*preloadBitmaps(BACKGROUNDS_FOLDER);
	preloadBitmaps(BUTTON_FOLDER);
	preloadBitmaps(PLAYERS_FOLDER);
	preloadBitmaps(PLAYING_FOLDER);
	preloadBitmaps(HELP_PAGES_FOLDER);
	preloadBitmaps(TREASURES_FOLDER);
	preloadBitmaps(TILES_FOLDER);*/
}


/*______________________________________________

  >>>>> INITIALIZATION FOR EACH GAME STATE <<<<<
  ______________________________________________
*/
void Game::setState(game_state new_state)
{
	m_state = new_state;

	switch (m_state)
	{
	case MAIN_MENU:

		stopMusic(1);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		// init players for new play session
		for (auto p : m_players)
			p.second->init();

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		m_buttons[PLAY]->enable();
		m_buttons[HOW_TO]->enable();
		break;

	case HELP:

		stopMusic(1);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[NEXT]->enable();
		m_buttons[PREV]->enable();
		break;

	case CHOOSE_PLAYER:

		stopMusic(1);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		// init tiles for new play session
		for (auto t : m_tiles)
			t->init();

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[OK]->enable();
		break;

	case PLAYING:

		stopMusic(1);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		for (auto p : m_players)
			(p.second->getPlayersTurn() == 1) ? p.second->setActive(true) : p.second->setActive(false);

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		break;
	}
	addEvent(new FadeFromBlackEvent());
}


/*___________________________________________

  >>>>> DRAW SCREEN FOR EACH GAME STATE <<<<<
  ___________________________________________
*/
void Game::draw()
{
	Brush text;
	Brush background;
	background.outline_opacity = 0.0f;
	
	switch (m_state)
	{
	case INIT:
		setFont(SCRATCHED_FONT);
		SETCOLOR(text.fill_color, 0.7f, 0.1f, 0.1f);
		drawText(CANVAS_WIDTH / 2 - 6.5, CANVAS_HEIGHT / 2 + 1.0f, 2.0f, "LOADING ASSETS", text);
		break;
		
	case MAIN_MENU:
		background.texture = MAIN_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;
		
	case HELP:
		background.texture = m_cur_page_img;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;
		
	case CHOOSE_PLAYER:
		background.texture = CHOOSE_PLAYER_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		setFont(IMMORTAL_FONT);
		SETCOLOR(text.fill_color, 0.5f, 0.2f, 0.2f);
		drawText(CANVAS_WIDTH / 2 - 2.2f, CANVAS_HEIGHT / 2 - 3, 1.0f, "PLAYER " + to_string(getCurPlayer() + 1), text);

		for (auto p : m_players)
			p.second->draw();
		break;

	case PLAYING:
		background.texture = PLAYING_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		Brush wl;
		wl.outline_opacity = 0.0f;
		wl.texture = WATER_LEVEL;
		drawRect(CANVAS_WIDTH / 2 + 11.5f, CANVAS_HEIGHT / 2 + 4.7f, 4.5f, 5.5f, wl);

		int t = 0;
		for (int i = 0; i < 6; ++i)
			for (int j = 0; j < 4; ++j)
				if (Tile::getTilesGrid()[i][j])
					m_tiles[t++]->draw();

		for (auto p : m_players)
			if (p.second->isSelected())
				p.second->draw();
		break;
	}

	for (auto b : m_buttons)
		if (b.second->isActive())
			b.second->draw();

	for (auto e : m_events)
		if (e->isActive())
			e->draw();
}


/*________________________________________

  >>>>> UPDATE SCREEN FOR EACH STATE <<<<<
  ________________________________________
*/
void Game::update() 
{
	switch (m_state)
	{
	case INIT:
		setState(MAIN_MENU);
		break;
	
	case MAIN_MENU:
		updateButtons();
		processEvents();
		break;

	case HELP:
		updateButtons();
		processEvents();
		break;

	case CHOOSE_PLAYER:
		updateButtons();
		processEvents();
		for (auto player : m_players)
			player.second->update();
		break;

	case PLAYING:
		updateButtons();
		processEvents();
		for (auto p : m_players)
			if (p.second->isSelected())
				p.second->update();

		for (auto t : m_tiles)
			t->update();
		break;
	}
}


/*_________________________________

  >>>>> UPDATE ACTIVE BUTTONS <<<<<
  _________________________________
*/
void Game::updateButtons()
{
	for (auto button : m_buttons)
		if (button.second->isActive())
			button.second->update();
}

/*_________________________________
 |								   |
 |  >>>>> GET GAME INSTANCE <<<<<  |
 |---------------------------------|
 | If there's not a game instance, |
 | create one and return it and if |
 | a game already exists then just |
 | return the existing instance.   |
 |_________________________________|
*/
Game* Game::getInstance() 
{
	if (!m_instance) 
		m_instance = new Game();
	return m_instance;
}


/*__________________________________

  >>>>> RELEASE GAME INSTANCE <<<<<
  __________________________________
*/
void Game::releaseInstance()
{
	if (m_instance) 
		delete m_instance;
	m_instance = nullptr;
}


/*___________________________________________

  >>>>> FLIP TO NEXT PAGE OF HELP STATE <<<<<
  ___________________________________________
*/
void Game::flipNextPage()
{
	switch (getPage())
	{
	case ONE:
		setPage(TWO);
		setPageImage(PAGE_TWO);
		break;

	case TWO:
		setPage(THREE);
		setPageImage(PAGE_THREE);
		break;

	case THREE:
		setPage(FOUR);
		setPageImage(PAGE_FOUR);
		break;

	case FOUR:
		setPage(ONE);
		setPageImage(PAGE_ONE);
		setState(MAIN_MENU);
		break;
	}
}


/*___________________________________________

  >>>>> FLIP TO PREV PAGE OF HELP STATE <<<<<
  ___________________________________________
*/
void Game::flipPrevPage()
{
	switch (getPage())
	{
	case ONE:
		setState(MAIN_MENU);
		break;

	case TWO:
		setPage(ONE);
		setPageImage(PAGE_ONE);
		break;

	case THREE:
		setPage(TWO);
		setPageImage(PAGE_TWO);
		break;

	case FOUR:
		setPage(THREE);
		setPageImage(PAGE_THREE);
		break;
	}
}


/*____________________________________________________________________

  >>>>> UPDATE EVENTS FROM THE LIST AND REMOVE THE INACTIVE ONES <<<<<
  ____________________________________________________________________
*/
void Game::processEvents()
{
	for (auto event : m_events)
		event->update();
	m_events.remove_if([](Event* e) { return !e->isActive(); });
}


/*_____________________________________________

  >>>>> DELETE ALL THE GAME'S COLLECTIONS <<<<<
  _____________________________________________
*/
Game::~Game() 
{
	while (!m_events.empty()) {
		delete m_events.back();
		m_events.pop_back();
	}

	for (int i = 0; i < 20; ++i)
		delete m_tiles[i];

	for (auto demo : m_players)
		delete demo.second;
	m_players.clear();

	for (auto button : m_buttons)
		delete button.second;
	m_buttons.clear();	
}


/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			Player* p = new Player();
			m_players.push_front(p);

			p->setPosX(CANVAS_WIDTH * (i + 0.5f) / 4.0f);
			p->setPosY(CANVAS_HEIGHT * (j + 0.5f) / 2.0f);
		}
	}
*/

/*
	Brush sq;
	sq.outline_opacity = 0.3f;
	sq.fill_opacity = 0.0f;
	for (int i = 0; i < CANVAS_WIDTH / PLAYER_SIZE; i++) {
		for (int j = 0; j < CANVAS_HEIGHT / PLAYER_SIZE; j++) {
			drawRect((i + 0.5f) * PLAYER_SIZE, (j + 0.5f) * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE, sq);
		}
	}
*/

/*m_players.clear();
	delete & m_players;

	m_demo_players.clear();
	delete & m_demo_players;

	m_buttons.clear();
	delete& m_buttons;

	m_events.clear();
	delete & m_events;*/


	/*for_each(m_players.begin(), m_players.end(), [](auto item)->void { delete item; });
	m_demo_players.clear();

	for_each(m_events.begin(), m_events.end(), [](auto item)->void{ delete item; });
	m_events.clear();

	for_each(m_demo_players.begin(), m_demo_players.end(), [](auto item)->void { delete item.second; });
	m_demo_players.clear();

	for_each(m_buttons.begin(), m_buttons.end(), [](auto item)->void { delete item.second; });
	m_buttons.clear();*/


	/*std::map<player_role, DemoPlayer*>::iterator itr = m_demo_players.begin();
	while (itr != m_demo_players.end()) {
		m_demo_players.erase(itr++);
	}

	std::map<button_func, Button*>::iterator it = m_buttons.begin();
	while (it != m_buttons.end()) {
		m_buttons.erase(it++);
	}*/