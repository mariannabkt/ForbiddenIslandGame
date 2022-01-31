#pragma once
#include "defines.h"
#include "treasure.h"
#include "player.h"
#include "tile.h"

class Event :public GameObject
{
protected:

	float m_duration = 2.0f;
	float m_delay = 0.0f;
	float m_elapsed_time = 0.0f;
	float m_elapsed_delay = 0.0f;

	bool m_active = true;

public:

	Event(float dur = 2.0f, float del = 0.0f, float x = 0.0f, float y = 0.0f) : GameObject(x,y), m_duration(dur), m_delay(del) {}
	virtual ~Event() {};

	virtual void draw() {};
	virtual void update() ;

	bool isActive() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();
};


class StateTransitionEvent : public Event 
{
public:
	void draw() override;
};

template <class T1, class T2>
class MotionEvent : public Event 
{
	T1 m_start;
	T2 m_stop;

public:
	MotionEvent(Player* p, Tile* t) : Event(1.0f, 0.0f), m_start(p), m_stop(t) {}
	MotionEvent(Treasure* a, Treasure* b) : Event(1.0f, 0.0f), m_start(a), m_stop(b) {}
	void update();
};

template<class T1, class T2>
inline void MotionEvent<T1, T2>::update()
{
	if (waiting())
		return;

	Event::update();

	float s = m_elapsed_time / m_duration;
	float x = m_start->getPosX() * (1.0f - s) + m_stop->getPosX() * s;
	float y = m_start->getPosY() * (1.0f - s) + m_stop->getPosY() * s;
	m_start->setCords(x, y);
}

class ZoomOutEvent : public Event
{
	Treasure* tr;

public:
	ZoomOutEvent(Treasure* t);
	void update();
};

class SmokeEvent : public Event 
{
	float m_orientation;
	float m_scale;
public:
	
	SmokeEvent(float x, float y);
	void draw() override;
};


