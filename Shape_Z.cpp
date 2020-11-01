#include "Shape_Z.h"

Shape_Z::Shape_Z(Falling_shapes* const fs_ptr, Field* const f_ptr) :
	Shape(Z_COLOR, fs_ptr, f_ptr, { COORD{f_ptr->get_width() / 2 - 1, BEGIN_Y - 2}, COORD{ f_ptr->get_width() / 2, BEGIN_Y - 2},
		COORD{ f_ptr->get_width() / 2, BEGIN_Y - 1 }, COORD{ f_ptr->get_width() / 2 + 1, BEGIN_Y - 1 } }) {}

bool Shape_Z::rotate()
{
	auto tmp = body;
	switch (pos)
	{
	case Position::POS1:
		tmp.edit_coord({ COORD{2,0}, COORD{1,1}, COORD{0,0}, COORD{-1,1} });
		pos = Position::POS2;
		break;
	case Position::POS2:
		tmp.edit_coord({ COORD{0,2}, COORD{0,0}, COORD{-1,1}, COORD{-1,-1} });
		pos = Position::POS3;
		break;
	case Position::POS3:
		tmp.edit_coord({ COORD{2,0}, COORD{1,1}, COORD{0,0}, COORD{-1,1} });
		pos = Position::POS4;
		break;
	case Position::POS4:
		tmp.edit_coord({ COORD{0,2}, COORD{0,0}, COORD{-1,1}, COORD{-1,-1} });
		pos = Position::POS1;
		break;
	default:
		break;
	}
	if (tmp.valid_check(sh, field->get_height()) && tmp.valid_check(sh, BEGIN_X, field->get_width()))
	{
		body = std::move(tmp);
		return true;
	}
	else if (tmp.valid_check(sh, field->get_height()))
	{
		if (tmp.valid_check(sh, BEGIN_X - 1, field->get_width()))
		{
			tmp.move(1, 0);
			body = std::move(tmp);
			return true;
		}
		else if (tmp.valid_check(sh, BEGIN_X, field->get_width() + 1))
		{
			tmp.move(-1, 0);
			body = std::move(tmp);
			return true;
		}
	}
	else
	{
		if (tmp.valid_check(sh, field->get_height() + 1))
		{
			tmp.move(0, -1);
			body = std::move(tmp);
			return true;
		}
	}
	pos = pos == Position::POS1 ? Position::POS4 : static_cast<Position>(static_cast<size_t>(pos) - 1);
	return false;
}