#ifndef A_H
#define A_H
#include "game.h"
class Player;

class Action : public GameObject
{


	int m_remaining = 3;
	bool m_done = false;

	Player* m_player_performing;

public:

	Action(Player* p) : m_player_performing(p) {}

	void draw();
	void update();

	void init() { m_remaining = 3; }

};
#endif