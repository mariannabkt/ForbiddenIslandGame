#include "gameObject.h"


GameObject::GameObject(float x, float y) : m_posX(x), m_posY(y)
{
}


void GameObject::setCords(float x, float y)
{
	m_posX = x;
	m_posY = y;
}