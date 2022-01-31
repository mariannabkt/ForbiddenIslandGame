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
	
	int m_difficulty = 0;	// repreasents how many tiles will flood every turn
	int m_result = 0;		// 1 is victory else 0

	GAME_STATE m_state = INIT;
	GAME_STATE m_prev_state;

	HELP_PAGE m_cur_page = ONE;
	string m_cur_page_img = PAGE_ONE;

	int m_cur_player = 0;
	Player* m_active_player;

	map<PLAYER_ROLE, Player*> m_players = map<PLAYER_ROLE, Player*>();
	map<BUTTON_FUNC, Button*> m_buttons = map<BUTTON_FUNC, Button*>();
	map<string, Treasure*> m_treasures = map<string, Treasure*>();
	list<Event*> m_events = list<Event*>();

	int m_cur_flood_tile = 0;	// tile to be flooded or sunken next
	int m_flooded_tiles = 0;	// flooaded or sunken tiles
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

	static Game* getInstance();
	static void releaseInstance();

	void setDifficulty(int d) { m_difficulty = d; }
	void setResult(int r) { m_result = r; }

	GAME_STATE getState() const { return m_state; }
	void setState(GAME_STATE new_state);

	void flipNextPage();
	void flipPrevPage();

	int getCurPlayer() const { return m_cur_player; }
	void changePlayer();

	Player* getActivePlayer() const { return m_active_player; }
	void setActivePlayer(Player* pl) { m_active_player = pl; pl->setActive(true); }

	void addEvent(Event* event) { m_events.push_back(event); }
	
	map<PLAYER_ROLE, Player*>& getPlayers() { return m_players; }
	map<BUTTON_FUNC, Button*>& getButtons() { return m_buttons; }
	vector<TilesLayout*>& getLayouts() { return m_layouts; }
	map<string, Treasure*>& getTreasures() { return m_treasures; }
	list<Event*>& getEvents() { return m_events; }
	
	void setLayout(TilesLayout* l) { m_selected_layout = l; m_selected_layout->setSelected(true); }

	void floodTiles();
	void rearrangeTileGrid();
};