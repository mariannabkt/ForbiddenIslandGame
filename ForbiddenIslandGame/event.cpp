#include "event.h"
#include "sgg/graphics.h"
#include "player.h"

using namespace graphics;

/*____________________________

  >>>>> CREATE NEW EVENT <<<<<
  ____________________________
*/
Event::Event(float dur, float del, float x, float y) : GameObject(x, y), m_duration(dur), m_delay(del)
{ }


bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}


/*________________________

  >>>>> UPDATE EVENT <<<<<
  ________________________
*/
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


/*______________________________________

  >>>>> DRAW FADE FROM BLACK EVENT <<<<<
  ______________________________________
*/
void StateTransitionEvent::draw() 
{
	Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	br.fill_opacity = 1.0f - (m_elapsed_time / m_duration);
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

/*_____________________________________

  >>>>> CREATE NEW ZOOM OUT EVENT <<<<<
  _____________________________________
*/
ZoomOutEvent::ZoomOutEvent(Treasure* t) : Event(3.0f, 0.0f), m_treas(t)
{ }


void ZoomOutEvent::update()
{
	Event::update();

	if (waiting())
		return;

	float s = m_elapsed_time / m_duration;
	float w = m_treas->getWidth() * s;
	float h = m_treas->getHeight() * s;
	m_treas->setDimensions(w, h);
}


/*___________________________________

  >>>>> CREATE NEW BUBBLE EVENT <<<<<
  ___________________________________
*/
BubbleEvent::BubbleEvent(Tile* t) : Event(3.0f, 0.0f, t->getPosX(), t->getPosY())
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 4.0f;
	m_posX = t->getLeft() + RAND0TO1() * TILE_SIZE;
	m_posY = t->getUp() + RAND0TO1() * TILE_SIZE;
	m_size = RAND0TO1() * BUBBLE_SIZE;
}


void BubbleEvent::draw() {
	Brush br;
	float s = m_elapsed_time / m_duration;
	br.texture = BUBBLE_IMAGE;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.5f;
	setScale(m_scale + s, m_scale + s);
	setOrientation(m_orientation + s * 20.0f);
	m_posY -= (1.0f - s) * 0.1f;
	drawRect(m_posX, m_posY, m_size, m_size, br);
	resetPose();
}