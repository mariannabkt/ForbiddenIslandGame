#include "clickable.h"

/*_________________________________

  >>>>> CREATE NEW CLICKABLES <<<<<
  _________________________________
*/
Clickable::Clickable(string img, float w, float h, float x, float y) 
	: m_img(img), m_width(w), m_height(h)
{
	Clickable::setCords(x, y);
}


/*________________________________

  >>>>> SET CORDS AND BOUNDS <<<<<
  ________________________________
*/
void Clickable::setCords(float x, float y)
{
	GameObject::setCords(x, y);

	m_left = m_posX - m_width / 2;
	m_right = m_posX + m_width / 2;
	m_up = m_posY - m_height / 2;
	m_down = m_posY + m_height / 2;
}


/*___________________________________________

  >>>>> CHECK IF MOUSE IS INSIDE BOUNDS <<<<<
  ___________________________________________
*/
bool Clickable::contains(float x, float y)
{
	return (x > m_left && x < m_right && y > m_up && y < m_down);
}