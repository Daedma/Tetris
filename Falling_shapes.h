#pragma once
#include "Body.h"

class Falling_shapes//класс упавших фигур
{
	std::multimap<SHORT, SHORT> coords;
	std::deque<Body> shapes;
public:
	void add(const Body&);
	void rebuild();
	void wash();
	void draw();
	bool status_check();
	size_t get_y(SHORT y) { return coords.count(y); }
	auto get_x(SHORT y)->typename std::add_const<decltype(coords.equal_range(y))>::type
	{
		return coords.equal_range(y);
	}
	size_t clear_tier(size_t);
	void clear();
};

extern Falling_shapes fs;