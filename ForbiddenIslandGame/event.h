#pragma once
#include "defines.h"

class Event
{
protected:

	float m_event_posX;
	float m_event_posY;

	float m_duration;
	float m_delay;

	float m_elapsed_time;
	float m_elapsed_delay;

	bool m_active = true;

public:

	Event(float x = 0.0f, float y = 0.0f, float dur = 2.0f, float del = 0.0f);
	virtual ~Event() {};

	virtual void draw() {};
	virtual void update() ;

	bool active() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();

};

class SoundEvent : public Event {
public:
	void draw() override;
};

class FadeFromBlackEvent : public Event {
public:
	void draw() override;
};

class PlayerMotionEvent : public Event {
	class Player* m_player;
	float m_start_x;
	float m_stop_x;
	float m_start_y;
	float m_stop_y;
public:
	void update() override;
	PlayerMotionEvent(float start_x, float start_y, float end_x, float end_y, class Player* p);
};

