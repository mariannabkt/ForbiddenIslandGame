#pragma once
#include "defines.h"
#include "player.h"
#include "tile.h"

class Event
{
protected:

	float m_event_posX;
	float m_event_posY;

	float m_duration;
	float m_elapsed_time;

	bool m_active = true;

public:

	Event(float x = 0.0f, float y = 0.0f, float dur = 2.0f) : m_event_posX(x), m_event_posY(y), m_duration(dur){}
	virtual ~Event() {};

	virtual void draw() {};
	virtual void update() ;

	bool isActive() { return m_active; }
	void disable() { m_active = false; }

};


class StateTransitionEvent : public Event 
{
public:
	void draw() override;
};

template <class T1, class T2>
class PlayerMotionEvent : public Event 
{
	T1 m_start;
	T2 m_stop;

public:
	PlayerMotionEvent(Player* p, Tile* t) : Event(0.0f, 0.0f, 1.0f), m_start(p), m_stop(t) {}
	PlayerMotionEvent(Treasure* a, Treasure* b) : Event(0.0f, 0.0f, 1.0f), m_start(a), m_stop(b) {}
	void update();
};

template<typename T1, typename T2>
inline void PlayerMotionEvent<T1, T2>::update()
{
	Event::update();

	float s = m_elapsed_time / m_duration;
	float x = m_start->getPosX() * (1.0f - s) + m_stop->getPosX() * s;
	float y = m_start->getPosY() * (1.0f - s) + m_stop->getPosY() * s;
	m_start->setCords(x, y);
}


class SmokeEvent : public Event 
{
	float m_orientation;
	float m_scale;
public:
	void draw() override;
	SmokeEvent(float x, float y);
};


