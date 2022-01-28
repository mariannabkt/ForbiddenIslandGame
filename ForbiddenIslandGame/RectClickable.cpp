#include "RectClickable.h"

RectClickable::RectClickable(string img, float x, float y, float w, float h) 
	: m_img(img), m_width(w), m_height(h)
{
	setCords(x, y);
}


/*_______________________________________

  >>>>> SET TILE'S CORDS AND BOUNDS <<<<<
  _______________________________________
*/
void RectClickable::setCords(float x, float y)
{
	m_posX = x;
	m_posY = y;

	m_left = m_posX - m_width / 2;
	m_right = m_posX + m_width / 2;
	m_up = m_posY - m_height / 2;
	m_down = m_posY + m_height / 2;
}


/*___________________________________________

  >>>>> CHECK IF MOUSE IS INSIDE BOUNDS <<<<<
  ___________________________________________
*/
bool RectClickable::contains(float x, float y)
{
	return (x > m_left && x < m_right&& y > m_up && y < m_down);
}