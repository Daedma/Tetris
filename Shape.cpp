#include "Shape.h"

double Shape::speed = 0.4;

Shape::Shape(WORD color, Falling_shapes* const falling_shapes_ptr, Field* const field_ptr, std::initializer_list<COORD> _lst) :
	sh(falling_shapes_ptr), body(color, _lst), field(field_ptr), pos(Position::POS1) {}

Shape& Shape::operator=(const Shape& rhs)
{
	sh->add(body);
	body = rhs.body;
	pos = rhs.pos;
	return *this;
}

Shape::Shape(Shape&& rhs) noexcept:
	sh(rhs.sh), body(rhs.body), pos(rhs.pos), field(rhs.field)
{
	sh->add(body);
}

Shape& Shape::operator=(Shape&& rhs) noexcept
{
	sh->add(body);
	body = rhs.body;
	pos = rhs.pos;
	return *this;
}

bool Shape::fall()
{
	auto tmp = body;
	tmp.move(0, 1);
	if (tmp.valid_check(sh, field->get_height()))
	{
		body = std::move(tmp);
		return true;
	}
	return false;
}

bool Shape::move(Courses crs)
{
	auto tmp = body;
	switch (crs)
	{
	case Courses::RIGHT:
		tmp.move(1, 0);
		break;
	case Courses::LEFT:
		tmp.move(-1, 0);
		break;
	case Courses::DOWN:
		tmp.move(0, 1);
		break;
	default:
		break;
	}
	if(crs==Courses::DOWN)
	{
		if (tmp.valid_check(sh, field->get_height()))
		{
			body = std::move(tmp);
			return true;
		}
	}
	else if (tmp.valid_check(sh, FIELD_BEGIN_X, field->get_width()))
	{
		body = std::move(tmp);
		return true;
	}
	return false;
}

bool Shape::game_over()
{
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 10, field->get_height() / 2 - 3 });
	for (size_t i = 0; i != 20; ++i)
		std::cout << char(FIELD_FRAME);
	for (SHORT a = 2; a != -2; --a)
	{
		SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 10, field->get_height() / 2 - a });
		std::cout << char(FIELD_FRAME);
		for (size_t i = 0; i != 18; ++i)
		{
			std::cout << EMPTY;
		}
		std::cout << char(FIELD_FRAME);
	}
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 10, field->get_height() / 2 + 2 });
	for (size_t i = 0; i != 20; ++i)
		std::cout << char(FIELD_FRAME);
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 5, field->get_height() / 2 - 2 });
		SetConsoleTextAttribute(hConsole, 0b0100'1111);
		std::cout << "GAME OVER";
		SetConsoleTextAttribute(hConsole, 0b0000'0111);
		SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 6, field->get_height() / 2 - 1 });
		std::cout << "your score: " << (field->get_score());
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 5, field->get_height() / 2 });
	std::cout << "Restart?";
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 8, field->get_height() / 2 + 1 });
	SetConsoleTextAttribute(hConsole, 0b0010'1111);
	std::cout << "YES";
	SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 + 5, field->get_height() / 2 + 1 });
	SetConsoleTextAttribute(hConsole, 0b0100'1111);
	std::cout << "NO";
	bool Waiting = true;
	while (Waiting)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case(KEY_ARROW_LEFT):
				SetConsoleTextAttribute(hConsole, FIELD_COLOR);
				system("cls");
				Waiting = false;
				speed = 1;
				clear();
				field->reset();
				field->draw();
				sh->wash();
				sh->clear();
				break;
			case(KEY_ARROW_RIGHT):
				field->clear(1);
				SetConsoleCursorPosition(hConsole, { (field->get_width() + BEGIN_X + field->get_p_width()) / 2 - 1, field->get_height() / 2 });
				SetConsoleTextAttribute(hConsole, 0b1111'1000);
				std::cout << "Bye!";
				Sleep(2500);
				exit(0);
			}
		}
	}
	return false;
}

