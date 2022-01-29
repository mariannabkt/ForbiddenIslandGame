#pragma once
#include "defines.h"
#include "clickable.h"
#include "sgg/graphics.h"

using namespace graphics;

class Button : public Clickable
{

	BUTTON_FUNC m_func;

	bool m_highlighted = false;
	bool m_active = false;

public:

	Button(BUTTON_FUNC b, float center_width_offset, float center_height_offset, float width, float height);
	
	void draw();
	void update();

	void enable() { m_active = true; }
	void disable() { m_active = false; }
	bool isActive() { return m_active; }

};