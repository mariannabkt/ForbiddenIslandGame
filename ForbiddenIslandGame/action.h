#pragma once
#include "gameObject.h"


/*
	An action entity is performed by players on tiles.
*/
class Action : public GameObject
{
	int m_remaining = 3;

	class Player* m_player_performing;

public:

	Action(Player* p) : m_player_performing(p) {}

	void draw();
	void update();

	void init() { m_remaining = 3; }

};