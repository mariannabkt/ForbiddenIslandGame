#include "game.h"
#include "button.h"
#include "defines.h"
#include <sgg/graphics.h>

using namespace graphics;
using namespace std;

Game* Game::m_instance = nullptr;


/*______________________________________________

  >>>>> INITIALISATION FOR EACH GAME STATE <<<<<
  ______________________________________________
*/
void Game::init() 
{
	switch (m_state)
	{
	case INIT:

		preloadBitmaps(ASSET_PATH);

		m_buttons[EXIT] = new Button(EXIT);
		m_buttons[PLAY] = new Button(PLAY);
		m_buttons[HOW_TO] = new Button(HOW_TO);
		m_buttons[NEXT] = new Button(NEXT);
		m_buttons[PREV] = new Button(PREV);
		m_buttons[OK] = new Button(OK);
		break;

	case MAIN_MENU:

		stopMusic(1);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		m_buttons[PLAY]->enable();
		m_buttons[HOW_TO]->enable();
		break;

	case HELP:

		stopMusic(1);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		m_buttons[NEXT]->enable();
		m_buttons[PREV]->enable();
		break;

	case CHOOSE_PLAYER:

		stopMusic(1);
		playMusic(INTO_THE_WATER, 1.0f, true, 1000);

		m_demo_players[EXPLORER] = new DemoPlayer(EXPLORER);
		m_demo_players[DIVER] = new DemoPlayer(DIVER);
		m_demo_players[PILOT] = new DemoPlayer(PILOT);

		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		m_buttons[OK]->enable();
		break;

	case PLAYING:

		stopMusic(1);
		playMusic(FALLING_WATER, 1.0f, true, 1000);

		for (auto b : m_buttons)
			b.second->disable();
		m_buttons[EXIT]->enable();
		break;
	}
	//addEvent(new FadeFromBlackEvent);
}


/*______________________________________________

  >>>>> CALL DRAW FUNC FOR EACH GAME STATE <<<<<
  ______________________________________________
*/
void Game::draw()
{
	switch (m_state)
	{
	case INIT:
		drawINIT();
		break;
		
	case MAIN_MENU:
		drawMAIN();
		break;
		
	case HELP:
		drawHELP();
		break;
		
	case CHOOSE_PLAYER:
		drawCHOOSE();
		break;

	case PLAYING:
		drawPLAYING();
		break;
	}
}


/*______________________________________

  >>>>> DRAW SCREEN FOR STATE INIT <<<<<
  ______________________________________
*/
void Game::drawINIT()
{	
	Brush br;
	SETCOLOR(br.fill_color, 0.7f, 0.1f, 0.1f);
	graphics::setFont(SCRATCHED_FONT);
	graphics::drawText(CANVAS_WIDTH / 2 - 6.5, CANVAS_HEIGHT / 2, 2.0f, "  LOADING ASSETS", br);
}


/*___________________________________________

  >>>>> DRAW SCREEN FOR STATE MAIN MENU <<<<<
  ___________________________________________
*/
void Game::drawMAIN()
{
	Brush br;
	br.outline_opacity = 0.0f;
	
	br.texture = MAIN_BACKGROUND;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	
	m_buttons[EXIT]->drawButton(13.0f, -7.0f, 1.0f, 1.0f);
	m_buttons[PLAY]->drawButton(-8.0f, 4.5f, 5.0f, 2.0f);
	m_buttons[HOW_TO]->drawButton(-1.0f, 4.5f, 7.0f, 2.0f);
}


/*______________________________________

  >>>>> DRAW SCREEN FOR STATE HELP <<<<<
  ______________________________________
*/
void Game::drawHELP()
{
	Brush br;
	br.outline_opacity = 0.0f;

	switch (m_cur_page)
	{
	case ONE:
	
		br.texture = PAGE_ONE;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		break;
	
	case TWO:
	
		br.texture = PAGE_TWO;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		break;
	
	case THREE:
	
		br.texture = PAGE_THREE;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		break;
	
	case FOUR:
	
		br.texture = PAGE_FOUR;
		drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		break;
	}
	m_buttons[EXIT]->drawButton(13.0f, -7.0f, 1.0f, 1.0f); 
	m_buttons[NEXT]->drawButton(12.5f, 0.0f, 1.5f, 1.5f);
	m_buttons[PREV]->drawButton(-12.5f, 0.0f, 1.5f, 1.5f);
}

/*_____________________________________

  >>>>> DRAW CHOOSE PLAYER SCREEN <<<<<
  _____________________________________
*/
void Game::drawCHOOSE()
{
	Brush br;
	br.outline_opacity = 0.0f;

	br.texture = CHOOSE_PLAYER_BACKGROUND;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	string player;
	if (!getCurPlayer())
		player = "PLAYER 1";
	else
		player = "PLAYER 2";

	SETCOLOR(br.fill_color, 0.5f, 0.2f, 0.2f);
	graphics::setFont(IMMORTAL_FONT);
	graphics::drawText(CANVAS_WIDTH / 2 - 2.2f, CANVAS_HEIGHT / 2 - 3, 1.0f, player + to_string(m_players.size()), br);

	for (auto p : m_demo_players)
		p.second->draw();

	m_buttons[EXIT]->drawButton(13.0f, -7.0f, 1.0f, 1.0f);
	m_buttons[OK]->drawButton(11.0f, 6.0f, 1.0f, 1.0f);
}


/*_______________________________

  >>>>> DRAW PLAYING SCREEN <<<<<
  _______________________________
*/
void Game::drawPLAYING()
{
	Brush br;
	br.outline_opacity = 0.0f;

	br.texture = PLAYING_BACKGROUND;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	for (auto p : m_players)
		p->draw();

	m_buttons[EXIT]->drawButton(13.0f, -7.0f, 1.0f, 1.0f);
}


/*________________________________________

  >>>>> UPDATE SCREEN FOR EACH STATE <<<<<
  ________________________________________
*/
void Game::update() {

	switch (m_state)
	{
	case INIT:
		//sleep(3000);
		m_state = MAIN_MENU;
		init();
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
		for (auto player : m_demo_players)
			player.second->update();
		processEvents();
		break;

	case PLAYING:

		updateButtons();
		for (auto p : m_players)
			p->update();
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
	{
		if (button.second->isActive())
		button.second->updateButton();
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


/*________________________________________________

  >>>>> ADD AN EVENT AT THE LIST AND DRAW IT <<<<<
  ________________________________________________
*/
void Game::addEvent(Event* event)
{
	m_events.push_front(event);
	event->draw();
}


/*____________________________________________________________________

  >>>>> UPDATE EVENTS FROM THE LIST AND REMOVE THE INACTIVE ONES <<<<<
  ____________________________________________________________________
*/
void Game::processEvents()
{
	for (auto event : m_events)
		event->update();
	m_events.remove_if([](Event* e) { return !e->active(); });
}


/*____________________________________________

  >>>>> CLEAR ALL THE GAME'S COLLECTIONS <<<<<
  ____________________________________________
*/
void Game::clearCollections()
{
	for_each(m_players.begin(), m_players.end(), [](auto item)->void { delete item; });
	m_demo_players.clear();

	for_each(m_demo_players.begin(), m_demo_players.end(), [](auto item)->void{ delete item.second; });
	m_demo_players.clear();

	for_each(m_buttons.begin(), m_buttons.end(), [](auto item)->void{ delete item.second; });
	m_buttons.clear();

	for_each(m_events.begin(), m_events.end(), [](auto item)->void{ delete item; });
	m_events.clear();

	/*m_players.clear();
	delete & m_players;

	m_demo_players.clear();
	delete & m_demo_players;

	m_buttons.clear();
	delete& m_buttons;

	m_events.clear();
	delete & m_events;*/


	/*std::map<player_role, DemoPlayer*>::iterator itr = m_demo_players.begin();
	while (itr != m_demo_players.end()) {
		m_demo_players.get_allocator().destroy(itr._Ptr);
		m_demo_players.erase(itr++);  
	}*/

	/*for (auto button : m_buttons)
		delete button.second;
	m_buttons.clear(); 


	while (!m_events.empty()) {
		delete m_events.front();
		m_events.pop_front();
	}*/
}

Game::~Game() 
{
	clearCollections();
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
