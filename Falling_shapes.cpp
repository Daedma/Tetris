#include "Falling_shapes.h"

void Falling_shapes::add(const Body& _body)
{
	shapes.push_back(_body);
	for (size_t i = 0; i != _body.size(); ++i)
		coords.insert(std::make_pair(_body[i].Y, _body[i].X));
}

void Falling_shapes::rebuild()
{
	coords.clear();
	for (auto _body : shapes)
		for (size_t i = 0; i != _body.size(); ++i)
			coords.insert(std::make_pair(_body[i].Y, _body[i].X));
}

void Falling_shapes::wash()
{
	SetConsoleTextAttribute(hConsole, FIELD_COLOR);
	for (auto i : shapes)
		i.clear();
}

void Falling_shapes::draw()
{
	for (auto it : shapes)
		it.draw();
}

bool Falling_shapes::status_check()
{
	return !coords.count(FIELD_BEGIN_Y);
}

size_t Falling_shapes::clear_tier(size_t width)
{
	size_t count = 0;
	for (auto it = coords.begin(); it != coords.end();)
	{
		if (coords.count(it->first) == width)
		{
			for (auto sh = shapes.begin(); sh != shapes.end(); ++sh)
			{
				size_t sz = sh->size();
				sh->clear_tier(it->first);
				if (sz == sh->size() && static_cast<int>(sh->get_y()) < it->first)
					sh->move(0, 1);
			}
			++count;
			it = coords.upper_bound(it->first);
		}
		if (it != coords.end())
			++it;
	}
	rebuild();
	return static_cast<size_t>(pow(count, 2));
}

void Falling_shapes::clear()
{
	shapes.clear();
	coords.clear();
}
