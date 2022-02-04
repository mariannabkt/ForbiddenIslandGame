#include "event.h"
#include "sgg/graphics.h"
#include "player.h"

using namespace graphics;

/*____________________________

  >>>>> CREATE NEW EVENT <<<<<
  ____________________________
*/
Event::Event(float dur, float x, float y) : GameObject(x, y), m_duration(dur)
{ }


/*________________________

  >>>>> UPDATE EVENT <<<<<
  ________________________
*/
void Event::update()
{
	if (!m_active)
		return;

	m_elapsed_time += getDeltaTime() / 1000.0f;

	if (m_elapsed_time > m_duration)
		m_active = false;
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


/*___________________________________

  >>>>> CREATE NEW BUBBLE EVENT <<<<<
  ___________________________________
*/
BubbleEvent::BubbleEvent(Tile* t) : Event(3.0f, t->getPosX(), t->getPosY())
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 4.0f;
	m_posX = t->getLeft() + RAND0TO1() * TILE_SIZE;
	m_posY = t->getUp() + RAND0TO1() * TILE_SIZE;
	m_size = RAND0TO1() * BUBBLE_SIZE;
}


/*_______________________________________________

  >>>>> DRAW BUBBLES WHEN TILES IS FLOODING <<<<<
  _______________________________________________
*/
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


/*_________________________________

  >>>>> CREATE NEW SINK EVENT <<<<<
  _________________________________
*/
SinkEvent::SinkEvent(Tile* s) : Event(3.0f, s->getPosX(), s->getPosY())
{
}


/*______________________________________

  >>>>> DRAW FADE FROM BLACK EVENT <<<<<
  ______________________________________
*/
void SinkEvent::draw()
{
	Brush br;
	br.outline_opacity = 0.0f;
	br.texture = WHIRLPOOL;
	br.fill_opacity = 1.0f - (m_elapsed_time / m_duration);
	drawRect(m_posX, m_posY, TILE_SIZE, TILE_SIZE, br);
}
