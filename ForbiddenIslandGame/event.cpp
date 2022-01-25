#include "event.h"
#include "sgg/graphics.h"
#include "player.h"

using namespace graphics;

void Event::update()
{
	if (!m_active)
		return;
	if (waiting())
	{
		m_elapsed_delay += getDeltaTime() / 1000.0f;
		return;
	}
	m_elapsed_time += getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}
}

Event::Event(float x, float y, float dur, float del)
	:m_event_posX(x), m_event_posY(y), m_duration(dur), m_delay(del)
{
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}


void FadeFromBlackEvent::draw() 
{
	if (waiting()) 
		return;
	
	Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	float s = m_elapsed_time / m_duration;
	br.fill_opacity = 1.0f - s;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void PlayerMotionEvent::update() {
	Event::update();
	if (!m_player) {
		m_active = false;
		return;
	}
	if (waiting()) {
		return;
	}
	/*float s = m_elapsed_time / m_duration;
	float x = m_start_x * (1.0f - s) + m_stop_x * s;
	float y = m_start_y * (1.0f - s) + m_stop_y * s;
	m_player->setPosX(x);
	m_player->setPosY(y);*/
}



PlayerMotionEvent::PlayerMotionEvent(float start_x, float start_y, float end_x, float end_y, Player* p)
	: Event(0.0f, 0.0f, 1.0f, 0.0f), m_start_x(start_x), m_stop_x(end_x), m_start_y(start_y), m_stop_y(end_y),
	m_player(p)
{

}

void SmokeEvent::draw() {
	Brush br;
	float s = m_elapsed_time / m_duration;
	//br.texture = ASSET_PATH + string();
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f - s;
	setScale(m_scale + s, m_scale + s);
	setOrientation(m_orientation + s * 20.0f);
	//drawRect(m_pos_x, m_pos_y, PLAYER_SIZE, PLAYER_SIZE, br);
	resetPose();
}



SmokeEvent::SmokeEvent(float x, float y)
	:Event(x, y, 2.0f, 0.0f)
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 4.0f;
}