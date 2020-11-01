#include "Body.h"
#include "Falling_shapes.h"

Body::Body(WORD _col, std::initializer_list<COORD> _coord) :
	color(_col)
{
	for (std::initializer_list<COORD>::const_iterator i = _coord.begin(); i != _coord.end(); ++i)
		coordinates.insert(std::make_pair(i->Y, i->X));
}

const Body& Body::set_coord(std::initializer_list<COORD> _lst)
{
	coordinates.clear();
	for (std::initializer_list<COORD>::const_iterator i = _lst.begin(); i != _lst.end(); ++i)
		coordinates.insert(std::make_pair(i->Y, i->X));
	return *this;
}

const Body& Body::edit_coord(std::initializer_list<COORD> _lst)
{
	if (_lst.size() <= coordinates.size())
	{
		decltype(coordinates) tmp;
		auto itm = coordinates.cbegin();
		for (std::initializer_list<COORD>::const_iterator itl = _lst.begin(); itl != _lst.end(); ++itl, ++itm)
		{
			SHORT x = itl->X + itm->second;
			SHORT y = itl->Y + itm->first;
			auto pr = tmp.equal_range(y);
			auto where = std::find_if(pr.first, pr.second, [x](decltype(*pr.first) val) {return x <= val.second; });
			tmp.insert(where, std::make_pair(y, x));
		}
		coordinates = std::move(tmp);
	}
	return *this;
}

void Body::draw()
{
	SetConsoleTextAttribute(hConsole, color);
	for (auto i : coordinates)
	{
		if (i.first >= BEGIN_Y)
		{
			SetConsoleCursorPosition(hConsole, { i.second, i.first });
			std::cout << BLOCK;
		}
	}
}

void Body::draw(SHORT x, SHORT y)
{
	SHORT delta_x = x - coordinates.begin()->second;
	SHORT delta_y = y - coordinates.begin()->first;
	auto tmp = *this;
	tmp.move(delta_x, delta_y);
	tmp.draw();
}

void Body::clear()
{
	SetConsoleTextAttribute(hConsole, FIELD_COLOR);
	for (auto i : coordinates)
	{
		if (i.first >= BEGIN_Y && i.second >= BEGIN_X)
		{
			SetConsoleCursorPosition(hConsole, { i.second, i.first });
			std::cout << EMPTY;
		}
	}
}

const Body& Body::move(SHORT x, SHORT y)
{
	if (y != 0 || x != 0)
	{
		decltype(coordinates) tmp;
		for (auto it = coordinates.begin();it!=coordinates.end(); ++it)
			tmp.insert(std::make_pair(it->first + y, it->second + x));
		coordinates = std::move(tmp);
	}
	return *this;
}

size_t Body::get_y(SHORT y) const
{
	return coordinates.count(y);
}

size_t Body::get_y() const
{
	if (coordinates.empty())
		return 0;
	return coordinates.crbegin()->first;
}

void Body::clear_tier(const SHORT y)
{
	if (coordinates.count(y))
	{
		coordinates.erase(y);
		SHORT counter = y;
		auto range = coordinates.equal_range(--counter);
		while (range.first != coordinates.end())
		{
			while (range.first != range.second)
			{
				coordinates.insert(std::make_pair(range.first->first + 1, range.first->second));
				coordinates.erase(range.first);
				range = coordinates.equal_range(counter);
			}
			range = coordinates.equal_range(--counter);
		}
	}
}

const COORD Body::operator[](size_t ind) const
{
	auto it = coordinates.cbegin();
	for (auto i = 0; i != ind; ++i, ++it);
	return COORD({ it->second, it->first });
}

bool Body::valid_check(Falling_shapes* fsh, SHORT val) const
{
	for (auto it : coordinates)
	{
		if (fsh->get_y(it.first))
		{
			auto _x = fsh->get_x(it.first);
			if (std::find(_x.first, _x.second, it) != _x.second)
				return false;
		}
		if (it.first > val)
			return false;
	}
	return true;
}

bool Body::valid_check(Falling_shapes* fsh, SHORT val1, SHORT val2) const
{
	for (auto it : coordinates)
	{
		if (fsh->get_y(it.first))
		{
			auto _x = fsh->get_x(it.first);
			if (std::find(_x.first, _x.second, it) != _x.second)
				return false;
		}
		if (it.second < val1 || it.second > val2)
			return false;
	}
	return true;
}
