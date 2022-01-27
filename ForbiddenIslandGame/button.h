#pragma once
#include "defines.h"
#include "sgg/graphics.h"

using namespace graphics;

class Button 
{
	Brush m_button_br;
	string m_button_img;
	button_func m_func;

	float m_button_posX;
	float m_button_posY;
	float m_button_width;
	float m_button_height;
	
	float m_button_left;
	float m_button_right;
	float m_button_up;
	float m_button_down;

	bool m_highlighted = false;
	bool m_active = false;

public:

	Button(button_func b, float center_width_offset, float center_height_offset, float width, float height);
	
	void draw();
	void update();

	void enable() { m_active = true; }
	void disable() { m_active = false; }
	bool isActive() { return m_active; }

	bool contains(float x, float y);
};