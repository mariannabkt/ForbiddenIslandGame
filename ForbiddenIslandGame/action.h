#ifndef A_H
#define A_H

class Player;

class Action
{
	float m_action_posX = 0.0f;
	float m_action_posY = 0.0f;

	int m_remaining = 3;
	bool m_done = false;

	Player* m_player_performing;

public:

	Action(Player* p) : m_player_performing(p) {}

	void draw();
	void update();

	void setCords(float x, float y) { m_action_posX = x; m_action_posY = y; }
};
#endif