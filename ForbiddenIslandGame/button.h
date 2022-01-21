#pragma once
#include "defines.h"
#include "sgg/graphics.h"

using namespace graphics;

class Button
{
protected:

	Brush button;
	string m_image_path;
	button_func m_func;
	
	float m_button_left;
	float m_button_right;
	float m_button_up;
	float m_button_down;

	bool m_highlighted = false;
	bool m_active = false;

public:

	Button(button_func b);
	
	void drawButton(float center_width_offset, float center_height_offset, float width, float height);
	void updateButton();

	void enable() { m_active = true; }
	void disable() { m_active = false; }
	bool isActive() { return m_active; }

	void setHighlight(bool h) { m_highlighted = h; }

	bool contains(float x, float y);
};