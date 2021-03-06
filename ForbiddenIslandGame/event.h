#pragma once
#include "defines.h"
#include "treasure.h"
#include "player.h"
#include "tile.h"

/*
	An event entity handles graphic animations.
*/
class Event : public GameObject
{
protected:

	float m_duration = 2.0f;
	float m_elapsed_time = 0.0f;

	bool m_active = true;

public:

	Event(float dur = 2.0f, float x = 0.0f, float y = 0.0f);
	virtual ~Event() {};

	virtual void draw() {};
	virtual void update() ;

	bool isActive() { return m_active; }
	void disable() { m_active = false; }
};


/*
	Smooth fade from black transition events between states.
*/
class StateTransitionEvent : public Event 
{
public:
	void draw();
};


/*
	Smooth movement animations.
*/
template <class T1, class T2>
class MotionEvent : public Event 
{
	T1 m_start;
	T2 m_stop;

public:
	MotionEvent(T1 a, T2 b) : Event(2.0f), m_start(a), m_stop(b) {}
	void update();
};

template<class T1, class T2>
inline void MotionEvent<T1, T2>::update()
{
	Event::update();

	float s = m_elapsed_time / m_duration;
	float x = m_start->getPosX() * (1.0f - s) + m_stop->getPosX() * s;
	float y = m_start->getPosY() * (1.0f - s) + m_stop->getPosY() * s;
	m_start->setCords(x, y);
}


/*
	Bubble animation.
*/
class BubbleEvent : public Event 
{
	Tile* m_tile;
	float m_orientation;
	float m_scale;
	float m_size;

public:
	BubbleEvent(Tile* t);
	void draw();
};


/*
	Smooth fade from whirlpool for sunken tile.
*/
class SinkEvent : public Event
{
public:
	SinkEvent(Tile* s);
	void draw();
};