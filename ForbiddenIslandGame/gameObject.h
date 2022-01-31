#pragma once

/*
	Abstract class for Game entities that live as the program runs.
	These can be Players, Tiles, Buttons, Events, Actions, Treasures etc.
*/
class GameObject
{
protected:

	float m_posX;
	float m_posY;

public:

	GameObject(float x = 0.0f, float y = 0.0f);

	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }

	void setCords(float x, float y);

	virtual void draw() = 0;
	virtual void update() = 0;
};
