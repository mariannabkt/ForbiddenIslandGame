#pragma once

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
