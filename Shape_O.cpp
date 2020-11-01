#include "Shape_O.h"

Shape_O::Shape_O(Falling_shapes* const fs_ptr, Field* const f_ptr) :
	Shape(O_COLOR, fs_ptr, f_ptr, { COORD{f_ptr->get_width() / 2, BEGIN_Y - 2}, COORD{ f_ptr->get_width() / 2 + 1, BEGIN_Y - 2},
		COORD{ f_ptr->get_width() / 2 + 1, BEGIN_Y - 1}, COORD{ f_ptr->get_width() / 2 , BEGIN_Y - 1 } }) {}

bool Shape_O::rotate()
{
	return true;
}