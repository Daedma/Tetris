#include "Field.h"
#include "Shape.h"
Field::side_panel::side_panel(SHORT _width, SHORT _height) :
	score(0), width(_width), height(_height) {}

Field::Field(SHORT _width, SHORT _height, SHORT panel_width) :
	width(_width), height(_height), panel(panel_width, height) {}

void Field::draw() const
{
	edit_console();
	SetConsoleTextAttribute(hConsole, FIELD_COLOR);
	SetConsoleCursorPosition(hConsole, { BEGIN_X - 1, BEGIN_Y - 1 });
	for (size_t i = 0; i != width + panel.width + 2; ++i)
		std::cout << char(FIELD_FRAME);
	for (SHORT i = 1; i != height + 1; ++i)
	{
		SetConsoleCursorPosition(hConsole, { BEGIN_X - 1, BEGIN_Y - 1 + i });
		std::cout << char(FIELD_FRAME);
		SetConsoleCursorPosition(hConsole, { width + 1, BEGIN_Y - 1 + i });
		std::cout << char(FIELD_FRAME);
		SetConsoleCursorPosition(hConsole, { width + panel.width + 1, BEGIN_Y + i - 1 });
		std::cout << char(FIELD_FRAME);
	}
	SetConsoleCursorPosition(hConsole, { FIELD_BEGIN_X - 1, height + 1 });
	for (size_t i = 0; i != width + panel.width + 2; ++i)
		std::cout << char(FIELD_FRAME);
	SetConsoleCursorPosition(hConsole, { width + panel.width / 2 - 4, BEGIN_Y + height / 10 });
	std::cout << "NEXT SHAPE:";
	SetConsoleCursorPosition(hConsole, { width + 2, BEGIN_Y + height / 5 });
	for (size_t i = 0; i != panel.width; ++i)
		std::cout << char(FIELD_FRAME);
	SetConsoleCursorPosition(hConsole, { width + 2, BEGIN_Y + height / 5 + 7 });
	for (size_t i = 0; i != panel.width; ++i)
		std::cout << char(FIELD_FRAME);
	SetConsoleCursorPosition(hConsole, { width + panel.width / 2 - 4, height - height / 4 });
	std::cout << "YOUR SCORE: ";
	draw_score();
}

void Field::draw_score()const
{
	SetConsoleCursorPosition(hConsole, { width + panel.width / 2 - 4, height - height / 5 });
	std::cout << panel.score;
}

void Field::augment_score(size_t add) const
{
	panel.score += add;
	draw_score();
}

void Field::draw_next_shape(Shape * sh) const
{
	for (SHORT y = BEGIN_Y + height / 5 + 1; y != BEGIN_Y + height / 5 + 7; ++y)
		for (SHORT x = width + 3; x != panel.width + width; ++x)
		{
			SetConsoleCursorPosition(hConsole, { x,y });
			std::cout << EMPTY;
		}
	sh->draw(width + 2 + panel.width / 3, BEGIN_Y + height / 5 + 2);
}

void Field::rainbow(WORD& palette) const
{
	SetConsoleTextAttribute(hConsole, ++palette);
	if (palette == FULL_PALETTE)
		palette = CLEAR_PALETTE;
}

void Field::clear(size_t speed) const
{
	SHORT x = (width + panel.width + BEGIN_X) / 2;
	SHORT y = height / 2;
	SHORT delta_x = 0;
	SHORT delta_y = 0;
	WORD palette = CLEAR_PALETTE;
	while (x >= FIELD_BEGIN_X && x <= width + panel.width + BEGIN_X || y <= height + BEGIN_Y && y >= FIELD_BEGIN_Y)
	{
		++delta_x;
		for (SHORT i = 0; i != delta_x; ++i)
		{
			if (x + i <= width + panel.width + BEGIN_X && x + i >= FIELD_BEGIN_X && y <= height + BEGIN_Y)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { (x + i), y });
				std::cout << ' ';
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}
		x += delta_x;
		++delta_y;
		for (SHORT i = 0; i != delta_y; ++i)
		{
			if (y - i <= height + BEGIN_Y && y - i >= FIELD_BEGIN_Y - 1 && x <= width + panel.width + BEGIN_X)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { x,(y - i) });
				std::cout << ' ';
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}
		y -= delta_y;
		++delta_x;
		for (SHORT i = 0; i != delta_x; ++i)
		{
			if (x - i <= width + panel.width + BEGIN_X && x - i >= FIELD_BEGIN_X && y >= FIELD_BEGIN_Y - 1)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { (x - i), y });
				std::cout << ' ';
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}
		x -= delta_x;
		++delta_y;
		for (SHORT i = 0; i != delta_y; ++i)
		{
			if (y + i <= height + BEGIN_Y && y + i >= FIELD_BEGIN_Y - 1 && x >= FIELD_BEGIN_X - 1)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { x,(y + i) });
				std::cout << ' ';
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}
		y += delta_y;
	}
	panel.score = 0;
}

void Field::edit_console() const
{
	SetConsoleTitle("Tetris\0");
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
	SetConsoleScreenBufferSize(hConsole, { width + panel.width + 1, height + 1});
	SMALL_RECT windowSize = { 0, 0, width + panel.width + 1, height + 1};
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}