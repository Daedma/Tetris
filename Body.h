#pragma once
#include "Macros_n_const.h"
#include <initializer_list>

class Falling_shapes;

class Body
{
	std::multimap<SHORT, SHORT> coordinates;
	WORD color;
public:
	Body(WORD, std::initializer_list<COORD>);
	const Body& set_coord(std::initializer_list<COORD> _lst);
	const Body& edit_coord(std::initializer_list<COORD> _lst);
	void draw();
	void draw(SHORT, SHORT);
	void clear();
	const Body& move(SHORT, SHORT);
	void clear_tier(const SHORT);
	size_t get_y(SHORT) const;
	size_t get_y() const;
	size_t size() const { return coordinates.size(); }
	const COORD operator[](size_t) const;
	bool valid_check(Falling_shapes*, SHORT) const;
	bool valid_check(Falling_shapes*, SHORT, SHORT) const;
};

