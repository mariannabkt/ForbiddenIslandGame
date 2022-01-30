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

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

void StateTransitionEvent::draw() 
{
	Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	br.fill_opacity = 1.0f - (m_elapsed_time / m_duration);
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}



SmokeEvent::SmokeEvent(float x, float y) : Event(2.0f, 0.0f, x, y)
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 4.0f;
}

void SmokeEvent::draw() {
	Brush br;
	float s = m_elapsed_time / m_duration;
	//br.texture = ASSET_PATH + string();
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f - s;
	setScale(m_scale + s, m_scale + s);
	setOrientation(m_orientation + s * 20.0f);
	drawRect(m_posX, m_posY, PLAYER_SIZE, PLAYER_SIZE, br);
	resetPose();
}

ZoomOutEvent::ZoomOutEvent(Treasure* t) : Event(5.0f , 0.0f), tr(t)
{
}

void ZoomOutEvent::update()
{
	Event::update();

	float s = m_elapsed_time / m_duration;
	float w = tr->getWidth() * s;
	float h = tr->getHeight() * s;
	tr->setDimensions(w, h);
}
