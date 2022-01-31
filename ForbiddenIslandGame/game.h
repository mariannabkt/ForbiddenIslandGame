#pragma once
#include <map>
#include <list>
#include <vector>
#include "defines.h"
#include "player.h"
#include "button.h"
#include "event.h"
#include "tile.h"
#include "tilesLayout.h"

/*
	A game entity has game objects and stores them into collections.
	Controls the app's operations and holds it's status to it's members.
*/
class Game 
{
	static Game* m_instance;
	
	int m_difficulty = 0;
	GAME_STATE m_state = INIT;
	GAME_STATE m_prev_state;

	HELP_PAGE m_cur_page = ONE;
	string m_cur_page_img = PAGE_ONE;

	int m_cur_player = 0;
	Player* m_active_player;

	map<PLAYER_ROLE, Player*> m_players = map<PLAYER_ROLE, Player*>();
	map<BUTTON_FUNC, Button*> m_buttons = map<BUTTON_FUNC, Button*>();
	list<Event*> m_events = list<Event*>();

	int m_cur_flood = 0;
	Tile* m_tiles[TILES_COUNT] = { 0 };
	TilesLayout* m_selected_layout;
	vector<TilesLayout*> m_layouts = vector<TilesLayout*>();

	Game();
	void updateButtons();
	void processEvents();
	void shuffleTiles();
	

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

	GAME_STATE getState() { return m_state; }
	void setState(GAME_STATE new_state);

	HELP_PAGE getPage() { return m_cur_page; }
	void setPage(HELP_PAGE new_page) { m_cur_page = new_page; }
	void setPageImage(string new_page_img) { m_cur_page_img = new_page_img; }

	int getCurPlayer() { return m_cur_player; }
	void changePlayer();

	Player* getActivePlayer() { return m_active_player; }
	void setActivePlayer(Player* pl) { m_active_player = pl; pl->setActive(true); }

	void addEvent(Event* event) { m_events.push_back(event); }
	
	map<PLAYER_ROLE, Player*>& getPlayers() { return m_players; }
	map<BUTTON_FUNC, Button*>& getButtons() { return m_buttons; }
	vector<TilesLayout*>& getLayouts() { return m_layouts; }
	list<Event*>& getEvents() { return m_events; }
	
	int getCurFlood() { return m_cur_flood; }
	void setCurFlood(int f) { m_cur_flood = f; }
	void floodTiles();
	Tile* (&getTiles())[24] { return m_tiles; }
	TilesLayout* gatLayout() { return m_selected_layout; }
	void setLayout(TilesLayout* l) { m_selected_layout = l; m_selected_layout->setSelected(true); }
	void rearrangeTileGrid();
};