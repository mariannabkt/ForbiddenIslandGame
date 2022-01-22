#pragma once
#include <set>
#include <map>
#include <list>
#include <vector>
#include "defines.h"
#include "player.h"
#include "demoPlayer.h"
#include "button.h"
#include "event.h"
#include "tile.h"

class Game 
{
	static Game* m_instance;
	
	game_state m_state = INIT;
	help_page m_cur_page = ONE;
	int m_cur_player = 0;
	Player* m_active_player;

	vector<Player*> m_players = vector<Player*>();
	map<player_role, DemoPlayer*> m_demo_players = map<player_role, DemoPlayer*>();
	map<button_func, Button*> m_buttons = map<button_func, Button*>();
	list<Event*> m_events = list<Event*>();
	vector<Tile*> m_tiles = vector<Tile*>();

	Game() {}
	void drawINIT();
	void drawMAIN();
	void drawHELP();
	void drawCHOOSE();
	void drawPLAYING();
	void updateButtons();
	void processEvents();
	void clearCollections();

public:

	~Game();

	void init();
	void draw();
	void update();

	static Game* getInstance();
	static void releaseInstance();

	void addEvent(Event* event);
	
	game_state getState() { return m_state; }
	help_page getPage() { return m_cur_page; }
	int getCurPlayer() { return m_cur_player; }
	Player* getActivePlayer() { return m_active_player; }

	void setState(game_state new_state) { m_state = new_state; }
	void setPage(help_page new_page) { m_cur_page = new_page; }
	void setActivePlayer(Player* pl) { m_active_player = pl; }
	void changePlayer() { m_cur_player == 0 ? m_cur_player++ : m_cur_player--; }

	vector<Player*>& getPlayers() { return m_players; }
	map<player_role, DemoPlayer*>& getDemoPlayers() { return m_demo_players; }
	map<button_func, Button*>& getButtons() { return m_buttons; }
	list<Event*>& getEvents() { return m_events; }
	vector<Tile*>& getTiles() { return m_tiles; }
};