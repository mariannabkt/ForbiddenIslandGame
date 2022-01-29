#include "defines.h"
#include "game.h"
#include "button.h"
#include "tile.h"
#include "action.h"
#include <sgg/graphics.h>
#include <random>

using namespace graphics;
using namespace std;

Game* Game::m_instance = nullptr;


/*_________________________________________

  >>>>> INITIALIZE GAME'S COLLECTIONS <<<<<
  _________________________________________
*/
Game::Game()
{
	// init buttons
	m_buttons[EXIT]   = new Button(EXIT, 13.0f, -7.0f, 1.0f, 1.0f);
	m_buttons[HOME]	  = new Button(HOME, 11.7f, -7.0f, 1.0f, 1.0f);
	m_buttons[HELP]   = new Button(HELP, 10.4f, -7.0f, 1.0f, 1.0f);
	m_buttons[PLAY]   = new Button(PLAY, -9.0f, 4.5f, 5.0f, 2.0f);
	m_buttons[HOW_TO] = new Button(HOW_TO, -3.0f, 4.5f, 7.0f, 2.0f);
	m_buttons[ABOUT]  = new Button(ABOUT, 4.0f, 4.5f, 4.5f, 2.0f);
	m_buttons[NEXT]   = new Button(NEXT, 12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[PREV]   = new Button(PREV, -12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[OK]     = new Button(OK, 11.0f, 6.0f, 1.0f, 1.0f);
	m_buttons[EASY]   = new Button(EASY, -9.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[MEDIUM] = new Button(MEDIUM, -3.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[HARD]   = new Button(HARD, 3.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[LEGENDARY] = new Button(LEGENDARY, 9.0f, 2.0f, 4.0f, 2.0f);

	// init players
	m_players[EXPLORER] = new Player(EXPLORER);
	m_players[DIVER]    = new Player(DIVER);
	m_players[PILOT]    = new Player(PILOT);

	// fill tile names(image paths) array
	string tile_names[TILES_COUNT] = { LIMNI , DASOS, PARATIRITIRIO, LAGADI, VALTOS, AMMOLOFOI, ASTEROSKOPEIO,
		VRAXOS, GEFIRA, KIPOS_PSI, KIPOS_KRA, NAOS_ILIOY, NAOS_FEGGARIOY,PALATI_PAL, VRAXOI, PILI_APLISTIAS, 
		PILI_LITHIS, PALATI_KOR, SPILIA_LAVAS, SPILIA_SKIWN, PILI_AGNOIAS, PILI_PROSMONIS, XEFWTO, PILI_AXARISTIAS };

	// init grid tiles
	for (int i = 0; i < TILES_COUNT; ++i)
		m_tiles[i] = new Tile(tile_names[i]);
}


/*______________________________________________

  >>>>> INITIALIZATION FOR EACH GAME STATE <<<<<
  ______________________________________________
*/
void Game::setState(GAME_STATE new_state)
{
	m_prev_state = m_state;
	m_state = new_state;

	switch (m_state)
	{
	case LOADING:

		playMusic(ELEVATOR_MUSIC, 1.0f, true, 2000);

		// preload assets
		preloadBitmaps(BACKGROUNDS_FOLDER);
		preloadBitmaps(BUTTON_FOLDER);
		preloadBitmaps(PLAYERS_FOLDER);
		preloadBitmaps(PLAYING_FOLDER);
		preloadBitmaps(HELP_PAGES_FOLDER);
		preloadBitmaps(TREASURES_FOLDER);
		preloadBitmaps(TILES_FOLDER);
		break;

	case MAIN_MENU:

		stopMusic(1);
		playMusic(NATURAL_AMBIENCE, 1.0f, true, 1000);

		m_cur_player = 0;

		// init tiles for new play session
		for (int i = 0; i < TILES_COUNT; ++i)
			m_tiles[i]->init();

		// shuffle tiles for new play session
		shuffleTileGrid();

		// init players for new play session
		for (auto p : m_players)
			p.second->init();

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		m_buttons[PLAY]->enable();
		m_buttons[HOW_TO]->enable();
		m_buttons[ABOUT]->enable();
		break;

	case SHOW_HOW_TO:

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

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[OK]->enable();
		break;

	case CHOOSE_DIF:

		// player 1 plays first
		for (auto p : m_players) {
			if (p.second->getPlayerTurn() == 1) 
			{
				setActivePlayer(p.second);
				p.second->setIconCords(1.5f, 12.5f);
				p.second->getActions()->setCords(3.4f, 13.0f);
				p.second->getTreasures()[AIR]->setCords(1.5f, 14.5f);
				p.second->getTreasures()[FIRE]->setCords(3.1f, 14.6f);
				p.second->getTreasures()[EARTH]->setCords(4.5f, 14.6f);
				p.second->getTreasures()[WATER]->setCords(5.7f, 14.5f);
			} 
			else if (p.second->getPlayerTurn() == 2) 
			{
				p.second->setActive(false);
				p.second->setIconCords(22.5f, 12.5f);
				p.second->getActions()->setCords(24.4f, 13.0f);
				p.second->getTreasures()[AIR]->setCords(22.4f, 14.5f);
				p.second->getTreasures()[FIRE]->setCords(24.0f, 14.6f);
				p.second->getTreasures()[EARTH]->setCords(25.4f, 14.6f);
				p.second->getTreasures()[WATER]->setCords(26.7f, 14.5f);
			}
			else
				p.second->getStandingTile()->setTaken(false);
		}

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[EASY]->enable();
		m_buttons[MEDIUM]->enable();
		m_buttons[HARD]->enable();
		m_buttons[LEGENDARY]->enable();
		break;

	case PLAYING:

		stopMusic(1);
		playSound(START_PLAYING, 1, false);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[HELP]->enable();
		break;
	}
	// smooth transition event between states
	addEvent(new StateTransitionEvent());
}

void Game::changePlayer()
{
	switch (m_state)
	{
	case CHOOSE_PLAYER:
		m_cur_player == 0 ? ++m_cur_player : --m_cur_player;
		break;
	case PLAYING:
		
			m_active_player->setActive(false);
			for (auto p : m_players)
				if (!p.second->isActive() && m_active_player->isSelected())
					setActivePlayer(p.second);
			if (m_active_player->getPlayerTurn() == 2)
				m_active_player->setActive(false);
			for (auto p : m_players)
				if (p.second->getPlayerTurn() == 1)
					setActivePlayer(p.second);
		break;
	}
}


/*___________________________________________

  >>>>> DRAW SCREEN FOR EACH GAME STATE <<<<<
  ___________________________________________
*/
void Game::draw()
{
	Brush text;
	Brush object;
	Brush background;
	background.outline_opacity = 0.0f;
	
	switch (m_state)
	{
	case INIT:
		SETCOLOR(background.fill_color, 1.0f, 0.0f, 0.5f);
		setWindowBackground(background);
		setFont(SCRATCHED_FONT);

		SETCOLOR(text.fill_color, 0.7f, 0.1f, 0.1f);
		drawText(CANVAS_WIDTH / 2 - 6.5f, CANVAS_HEIGHT / 2, 2.0f, "LOADING ASSETS", text);
		drawText(CANVAS_WIDTH / 2 - 4.5f, CANVAS_HEIGHT / 2 + 1.0f, 1.0f, "THIS MAY TAKE A MINUTE", text);
		
		object.outline_opacity = 0.0f; 
		object.texture = ".\\assets\\loading spinner.png";
		setOrientation(getDeltaTime() / 1000.0f);
		drawDisk(CANVAS_WIDTH / 2 - 4.5f, CANVAS_HEIGHT / 2 + 3.0f, 2.0f, object);
		resetPose();
		break;
		
	case MAIN_MENU:
		background.texture = MAIN_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;
		
	case SHOW_HOW_TO:
		background.texture = m_cur_page_img;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;

	case CHOOSE_DIF:
		background.texture = CHOOSE_DIFFICULTY_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;
		
	case CHOOSE_PLAYER:
		background.texture = CHOOSE_PLAYER_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		setFont(IMMORTAL_FONT);
		SETCOLOR(text.fill_color, 0.5f, 0.2f, 0.0f);
		drawText(CANVAS_WIDTH / 2 - 2.3f, CANVAS_HEIGHT / 2 - 3, 1.0f, "PLAYER  " + to_string(getCurPlayer() + 1), text);

		for (auto p : m_players)
			p.second->draw();
		break;

	case PLAYING:
		background.texture = PLAYING_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		int t = 0;
		for (int i = 0; i < 6; ++i)
			for (int j = 0; j < 6; ++j)
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
		setState(LOADING);
		break;

	case LOADING:
		setState(MAIN_MENU);
		break;;

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

		for (int i = 0; i < TILES_COUNT; ++i)
			m_tiles[i]->update();
		break;

	default:
		updateButtons();
		processEvents();
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


/*___________________________________________

  >>>>> SHUFFLE TILE GRID AND SET CORDS <<<<<
  ___________________________________________
*/
void Game::shuffleTileGrid()
{
	// To obtain a time-based seed
	unsigned seed = 0;

	// Shuffling our array
	shuffle(m_tiles, m_tiles + 24, default_random_engine(seed));

	// based on the tile grid
	int t = 0;
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 6; ++j)
			if (Tile::getTilesGrid()[i][j])
			{
				// set cords for every grid tile
				m_tiles[t]->setGridPos(i, j);
				m_tiles[t]->setCords((i + 3.6f) * (TILE_SIZE + 0.2f), (j + 0.7f) * (TILE_SIZE + 0.2f));
				
				// set player's pawn cords
				for (auto p : m_players)
					p.second->isStartTile(m_tiles[t]);

				++t;
			}
}


/*___________________________________________

  >>>>> FLIP TO NEXT PAGE OF HELP STATE <<<<<
  ___________________________________________
*/
void Game::flipNextPage()
{
	playSound(FLIP_PAGE, 1, false);
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
		setState(m_prev_state);
		break;
	}
}


/*___________________________________________

  >>>>> FLIP TO PREV PAGE OF HELP STATE <<<<<
  ___________________________________________
*/
void Game::flipPrevPage()
{
	playSound(FLIP_PAGE, 1, false);
	switch (getPage())
	{
	case ONE:
		setState(m_prev_state);
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


/*_____________________________________________

  >>>>> DELETE ALL THE GAME'S COLLECTIONS <<<<<
  _____________________________________________
*/
Game::~Game() 
{
	for (auto demo : m_players)
		delete demo.second;
	m_players.clear();

	for (auto button : m_buttons)
		delete button.second;
	m_buttons.clear();	

	for (auto event : m_events)
		delete event;
	m_events.clear();

	for (int i = 0; i < TILES_COUNT; ++i)
		delete m_tiles[i];

	delete m_selected_layout;
	m_selected_layout = nullptr;
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