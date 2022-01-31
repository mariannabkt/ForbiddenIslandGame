#include "defines.h"
#include "game.h"
#include "button.h"
#include "tile.h"
#include "action.h"
#include <sgg/graphics.h>
#include <random>
#include <cmath>


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
	m_buttons[EXIT]   = new Button(EXIT, EXIT_BUTTON, 13.0f, -7.0f, 1.0f, 1.0f);
	m_buttons[HOME]	  = new Button(HOME, HOME_BUTTON, 11.7f, -7.0f, 1.0f, 1.0f);
	m_buttons[HELP]   = new Button(HELP, HELP_BUTTON, 10.4f, -7.0f, 1.0f, 1.0f);
	m_buttons[PLAY]   = new Button(PLAY, PLAY_BUTTON, -9.0f, 4.5f, 5.0f, 2.0f);
	m_buttons[HOW_TO] = new Button(HOW_TO, HOW_TO_BUTTON, -2.5f, 4.5f, 7.0f, 2.0f);
	m_buttons[ABOUT]  = new Button(ABOUT, ABOUT_BUTTON, 3.9f, 4.5f, 4.f, 2.0f);
	m_buttons[NEXT]   = new Button(NEXT, NEXT_BUTTON, 12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[PREV]   = new Button(PREV, PREV_BUTTON, -12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[OK]     = new Button(OK, OK_BUTTON, 11.0f, 6.0f, 1.0f, 1.0f);
	m_buttons[EASY]   = new Button(EASY, EASY_BUTTON, -9.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[MEDIUM] = new Button(MEDIUM, MEDIUM_BUTTON, -3.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[HARD]   = new Button(HARD, HARD_BUTTON, 3.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[LEGENDARY] = new Button(LEGENDARY, LEGENDARY_BUTTON, 9.0f, 2.0f, 4.0f, 2.0f);
	m_buttons[PLAY_AGAIN] = new Button(PLAY_AGAIN, RETRY_BUTTON, 0.0f, 4.0f, 5.0f, 2.0f);

	// init players
	m_players[EXPLORER] = new Player(EXPLORER);
	m_players[DIVER]    = new Player(DIVER);
	m_players[PILOT]    = new Player(PILOT);



	// fill tile layout names array
	string layout_names[8] = { SKULL_IMAGE, BAY_IMAGE, HARPOON_IMAGE, ATOLL_IMAGE, 
		SHIPWRECK_IMAGE, DAVY_IMAGE, MUTINY_IMAGE, PALM_IMAGE };

	// init tile layouts
	for (int i = 0; i < 8; ++i)
		m_layouts.push_back(new TilesLayout(layout_names[i]));
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
	case INIT:
	{
		// fill tile names array
		string tile_names[TILES_COUNT] = { LIMNI , DASOS, PARATIRITIRIO, LAGADI, VALTOS, AMMOLOFOI, ASTEROSKOPEIO,
			VRAXOS, GEFIRA, KIPOS_PSI, KIPOS_KRA, NAOS_ILIOY, NAOS_FEGGARIOY,PALATI_PAL, VRAXOI, PILI_APLISTIAS,
			PILI_LITHIS, PALATI_KOR, SPILIA_LAVAS, SPILIA_SKIWN, PILI_AGNOIAS, PILI_PROSMONIS, XEFWTO, PILI_AXARISTIAS };

		// init grid tiles
		for (int i = 0; i < TILES_COUNT; ++i)
			m_tiles[i] = new Tile(tile_names[i]);
		break;
	}
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
		preloadBitmaps(LAYOUTS_FOLDER);
		//preloadBitmaps(SEA_FRAMES_FOLDER);
		break;

	case MAIN_MENU:

		stopMusic(1);
		playMusic(NATURAL_AMBIENCE, 1.0f, true, 1000);

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

	case INFO:

		stopMusic(1);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		break;

	case CHOOSE_ISLAND:

		stopMusic(1);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		m_cur_flood_tile = 0;

		// init tiles for new play session
		for (int i = 0; i < TILES_COUNT; ++i)
			m_tiles[i]->init();

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		break;

	case CHOOSE_PLAYER:

		m_cur_player = 0;

		// init players for new play session(choose state first)
		for (auto p : m_players)
			p.second->init();

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[OK]->enable();
		break;

	case CHOOSE_DIF:

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

		m_result = 0;

		// shuffle tiles for random flooding
		shuffleTiles();

		// get ready
		for (auto p : m_players) 
			p.second->init();
		
		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[HELP]->enable();
		break;

	case RETRY:

		stopMusic(1);
		if (m_result)
			playSound(VICTORY_SOUND, 1, false);
		else
			playSound(GAME_OVER_SOUND, 1, false);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		// enable only necessary buttons for this state
		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[HOME]->enable();
		m_buttons[EXIT]->enable();
		m_buttons[PLAY_AGAIN]->enable();
		break;
	}
	// smooth transition event between states
	addEvent(new StateTransitionEvent());
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
	object.outline_opacity = 0.0f;
	background.outline_opacity = 0.0f;
	
	switch (m_state)
	{
	case INIT:
	{
		setFont(SCRATCHED_FONT);
		SETCOLOR(text.fill_color, 0.7f, 0.1f, 0.1f);
		drawText(CANVAS_WIDTH / 2 - 6.5f, CANVAS_HEIGHT / 2, 2.0f, "LOADING ASSETS", text);
		drawText(CANVAS_WIDTH / 2 - 4.5f, CANVAS_HEIGHT / 2 + 1.0f, 1.0f, "THIS MAY TAKE A MINUTE", text);

		object.texture = ".\\assets\\loading spinner.png";
		float x = getDeltaTime() / 1000.0f;
		setOrientation(log(x / (1 - x)));
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 3.0f, 3.0f, 3.0f, object);
		resetPose();
		break;
	}
	case MAIN_MENU:
		background.texture = MAIN_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;
		
	case SHOW_HOW_TO:
		background.texture = m_cur_page_img;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;

	case INFO:
		background.texture = ABOUT_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
		break;

	case CHOOSE_ISLAND:
		background.texture = CHOOSE_ISLAND_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		for (auto l : m_layouts)
			l->draw();
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
		drawText(CANVAS_WIDTH / 2 - 2.5f, CANVAS_HEIGHT / 2 - 3.0f, 1.0f, "PLAYER  " + to_string(getCurPlayer() + 1), text);

		for (auto p : m_players)
			p.second->draw();
		break;

	case PLAYING:
		background.texture = PLAYING_BACKGROUND;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);

		object.texture = WATER_LEVEL;
		drawRect(0.7, 3.0f, 2.0f, 6.0f, object);
		{
			Brush water;
			water.outline_opacity = 0.0f;
			SETCOLOR(water.fill_color, 0.0f, 0.0f, 0.5f);
			drawRect(0.7, 3.0f, 2.0f, m_flooded_tiles / 24, water);

			int t = 0;
			for (int i = 0; i < m_selected_layout->getRows(); ++i)
				for (int j = 0; j < m_selected_layout->getCols(); ++j)
					if (m_selected_layout->getLayout()[i][j])
						m_tiles[t++]->draw();
		}
		for (auto p : m_players)
			if (p.second->isSelected())
				p.second->draw();

		for (auto r : m_treasures)
			if (r.second->isCollected())
				r.second->draw();
		break;
	
	case RETRY:
		setFont(IMMORTAL_FONT);
		SETCOLOR(text.fill_color, 0.5f, 0.2f, 0.0f);
		object.texture = m_active_player->getIconImage();

		if (m_result) {
			background.texture = VICTORY_BACKGROUND;
			drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
			drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 - 2.5f, 7.0f, 4.0f, object);
			string s = "PLAYER  " + to_string(m_active_player->getPlayerTurn()) + "  " + m_active_player->getPlayerName();
			drawText(CANVAS_WIDTH / 2 - 4.0f, CANVAS_HEIGHT / 2 + 1.0f, 1.0f, s, text);
			drawText(CANVAS_WIDTH / 2 - 9.0f, CANVAS_HEIGHT / 2 + 2.0f, 1.0f, "YOU   MANAGED   TO   GET   AWAY", text);
		}
		else {
			background.texture = LOOSERS_BACKGROUND;
			drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, background);
			drawText(CANVAS_WIDTH / 2 - 10.0f, CANVAS_HEIGHT / 2, 0.8f, "FOOLS   LANDING   OR/AND   TREASURE   TILE", text);
			drawText(CANVAS_WIDTH / 2 - 10.0f, CANVAS_HEIGHT / 2 + 1.0f, 0.8f, "GOT   SUNK   WITHOUT   BEING   COLLECTED", text);
			drawText(CANVAS_WIDTH / 2 - 10.0f, CANVAS_HEIGHT / 2 + 2.0f, 0.8f, "AND   NOW   YOU   CAN'T   GET   AWAY", text);
		}
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
		break;

	case CHOOSE_ISLAND:
		updateButtons();
		processEvents();
		for (auto l : m_layouts)
			l->update();
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
		for (int i = 0; i < TILES_COUNT; ++i)
			m_tiles[i]->update();
		break;

	case RETRY:
		updateButtons();
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


/*_________________________

  >>>>> SHUFFLE TILES <<<<<
  _________________________
*/
void Game::shuffleTiles()
{
	unsigned seed = 0;
	shuffle(m_tiles, m_tiles + 24, default_random_engine(seed));
}


/*___________________________________________

  >>>>> SHUFFLE TILE GRID AND SET CORDS <<<<<
  ___________________________________________
*/
void Game::rearrangeTileGrid()
{
	shuffleTiles();

	// based on the tile grid
	int t = 0;
	for (int i = 0; i < m_selected_layout->getRows(); ++i)
		for (int j = 0; j < m_selected_layout->getCols(); ++j)
			if (m_selected_layout->getLayout()[i][j])
			{
				// set cords for every tile
				m_tiles[t]->setGridPos(i, j);
				float x = (i + m_selected_layout->getPosXoffset()) * (TILE_SIZE + 0.2f);
				float y = (j + m_selected_layout->getPosYoffset()) * (TILE_SIZE + 0.2f);
				m_tiles[t]->setCords(x, y);
				if (m_tiles[t]->hasTreasure())
					m_tiles[t]->getTreasure()->setCords(x, y);

				// set player's pawn cords
				for (auto p : m_players)
					p.second->isStartTile(m_tiles[t]);

				++t;
			}
}


/*_______________________________

  >>>>> FLOOD OR SINK TILES <<<<<
  _______________________________
*/
void Game::floodTiles()
{
	for (int i = 0; i < m_difficulty; ++i) 
	{
		if (m_cur_flood_tile >= TILES_COUNT)
			m_cur_flood_tile = 0;

		Tile* t = m_tiles[m_cur_flood_tile];

		if (t->getFlooded()) {
			t->sink();
			++m_flooded_tiles;
			t->canPerformAction(false);
			if (t->getImage() == XEFWTO || (t->hasTreasure() && !t->getTreasure()->isCollected()))
				setState(RETRY);
			addEvent(new SinkEvent(t));
		}
		else if (!t->getSunken()) {
			t->flood();
			for (int i = 0; i < 10; ++i)
				addEvent(new BubbleEvent(t));
		}
		++m_cur_flood_tile;
	}
}

/*_______________________________________________________________________

  >>>>> CHANGE PLAYER CHOOSING OR ACTIVE PLAYER BASED ON GAME STATE <<<<<
  _______________________________________________________________________
*/
void Game::changePlayer()
{
	m_cur_player == 0 ? ++m_cur_player : --m_cur_player;

	if (m_state == PLAYING) {
		for (auto p : m_players)
			if ((!m_cur_player && p.second->getPlayerTurn() == 2) ||
				(m_cur_player && p.second->getPlayerTurn() == 1))
			{
				m_active_player->setActive(false);
				setActivePlayer(p.second);
			}
	}
}


/*___________________________________________

  >>>>> FLIP TO NEXT PAGE OF HELP STATE <<<<<
  ___________________________________________
*/
void Game::flipNextPage()
{
	playSound(FLIP_PAGE, 1, false);
	switch (m_cur_page)
	{
	case ONE:
		m_cur_page = TWO;
		m_cur_page_img = PAGE_TWO;
		break;

	case TWO:
		m_cur_page = THREE;
		m_cur_page_img = PAGE_THREE;
		break;

	case THREE:
		m_cur_page = FOUR;
		m_cur_page_img = PAGE_FOUR;
		break;

	case FOUR:
		m_cur_page = ONE;
		m_cur_page_img = PAGE_ONE;
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
	switch (m_cur_page)
	{
	case ONE:
		setState(m_prev_state);
		break;

	case TWO:
		m_cur_page = ONE;
		m_cur_page_img = PAGE_ONE;
		break;

	case THREE:
		m_cur_page = TWO;
		m_cur_page_img = PAGE_TWO;
		break;

	case FOUR:
		m_cur_page = THREE;
		m_cur_page_img = PAGE_THREE;
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