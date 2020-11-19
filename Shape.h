#pragma once
#include "Macros_n_const.h"
#include "Field.h"
#include "Body.h"
#include "Falling_shapes.h"

enum class Position
{
	POS1, //��������� ���������
	POS2, //90 ��������
	POS3, //180 ��������
	POS4  //270 ��������
};

enum class Courses //����������� ��������
{
	RIGHT, LEFT, DOWN, NONE
};

class Field;

class Shape //����������� ����� �����
{
	static double speed; 
protected:
	Falling_shapes* const sh;
	Body body;
	Position pos;
	Field* const field;
public:
	Shape(WORD, Falling_shapes* const, Field* const, std::initializer_list<COORD>);
	virtual ~Shape() { sh->add(body); }
	Shape(const Shape&) = default;
	Shape& operator=(const Shape&);
	Shape(Shape&&) noexcept;
	Shape& operator=(Shape&&) noexcept;
	void draw() { body.draw(); }
	void draw(SHORT x, SHORT y) { body.draw(x, y); }
	void clear() { body.clear(); }
	virtual bool rotate() = 0;
	bool fall();
	bool move(Courses);
	bool game_over();
	const double get_speed() const { return speed; }
	void augment_speed(double val = 0.1) { speed += val; }
};
