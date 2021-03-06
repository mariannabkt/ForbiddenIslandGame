#pragma once
#include "defines.h"
#include "clickable.h"

/*
	A button entity can be clicked and lead to different game states.
*/
class Button : public Clickable
{
	BUTTON_FUNC m_func;

	bool m_highlighted = false;
	bool m_active = false;
	bool m_lifted = false;

public:

	Button(BUTTON_FUNC b, string img, float center_width_offset, float center_height_offset, float width, float height);
	
	void draw();
	void update();

	void enable() { m_active = true; }
	void disable() { m_active = false; }
	bool isActive() { return m_active; }
	void lift() { m_posY -= 0.1; m_lifted = true; }
	void unlift() { m_posY += 0.1; m_lifted = false; }
};