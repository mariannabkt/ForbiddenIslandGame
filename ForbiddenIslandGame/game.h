#pragma once
#include <map>
#include <list>
#include "defines.h"
#include "player.h"
#include "button.h"
#include "event.h"
#include "tile.h"

class Game 
{
	static Game* m_instance;
	
	int m_difficulty = 0;
	game_state m_state = INIT;

	help_page m_cur_page = ONE;
	string m_cur_page_img = PAGE_ONE;

	int m_cur_player = 0;
	Player* m_active_player;

	map<player_role, Player*> m_players = map<player_role, Player*>();
	map<button_func, Button*> m_buttons = map<button_func, Button*>();
	list<Event*> m_events = list<Event*>();
	Tile* m_tiles[24] = { 0 };

	Game();
	void updateButtons();
	void processEvents();
	void shuffleTileGrid();

public:

	~Game();

	void draw();
	void update();

	void flipNextPage();
	void flipPrevPage();

	static Game* getInstance();
	static void releaseInstance();

	int getDifficulty() { return m_difficulty; }
	void setDifficulty(int d) { m_difficulty = d; }

	game_state getState() { return m_state; }
	void setState(game_state new_state);

	help_page getPage() { return m_cur_page; }
	void setPage(help_page new_page) { m_cur_page = new_page; }
	void setPageImage(string new_page_img) { m_cur_page_img = new_page_img; }

	int getCurPlayer() { return m_cur_player; }
	void changePlayer() { m_cur_player == 0 ? ++m_cur_player : --m_cur_player; }

	Player* getActivePlayer() { return m_active_player; }
	void setActivePlayer(Player* pl) { m_active_player = pl; pl->setActive(true); }

	void addEvent(Event* event) { m_events.push_back(event); }
	
	map<player_role, Player*>& getPlayers() { return m_players; }
	map<button_func, Button*>& getButtons() { return m_buttons; }
	list<Event*>& getEvents() { return m_events; }
	Tile* (&getTiles())[24] { return m_tiles; }
};