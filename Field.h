#pragma once
#include "Macros_n_const.h"

class Shape;

class Field //класс поля
{
	struct side_panel
	{
		side_panel(SHORT, SHORT);
		SHORT height, width;
		size_t score;
	};
	void edit_console() const;
	void draw_score()const;
	void rainbow(WORD&) const;
public:
	Field(SHORT = 50, SHORT = 25, SHORT = 10);
	const SHORT get_height() const { return height; }
	const SHORT get_width() const { return width; }
	const SHORT get_p_width() const { return panel.width; }
	void clear(size_t) const;
	void draw() const;
	void augment_score(size_t add) const;
	void draw_next_shape(Shape * sh) const;
	size_t get_score() const { return panel.score; }
	void reset() const { panel.score = 0; }
private:
	const SHORT height, width;
	mutable side_panel panel;
};