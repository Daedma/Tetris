#include "Tetris.h"

std::mutex mtx1;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static Falling_shapes fs;

enum class Shapes
{
	T, O, I, S, J, L, Z
};

size_t shape_gen()
{
	static std::default_random_engine e(static_cast<int>(std::time(0)));
	static std::uniform_int_distribution<> d(0, 6);
	return d(e);
}

Shape* rand_shape(Field* const fld, Falling_shapes* const falls)
{
	size_t sh = shape_gen();
	switch (sh)
	{
	case 0:
		return new Shape_T(falls, fld);
		break;
	case 1:
		return new Shape_O(falls, fld);
		break;
	case 2:
		return new Shape_I(falls, fld);
		break;
	case 3:
		return new Shape_S(falls, fld);
		break;
	case 4:
		return new Shape_J(falls, fld);
		break;
	case 5:
		return new Shape_L(falls, fld);
		break;
	case 6:
		return new Shape_Z(falls, fld);
		break;
	default:
		break;
	}
	return nullptr;
}

void game()
{
	Field fld(10, 20, 15);
	fld.draw();
	std::shared_ptr<Shape> shp(rand_shape(&fld));
	while (true)
	{
		std::shared_ptr<Shape> next_shp(rand_shape(&fld));
		fld.draw_next_shape(next_shp.get());
		bool flag = true;
		while (flag)
		{
			shp->clear();
			if (_kbhit())
			{
				switch (_getch())
				{
				case KEY_ARROW_DOWN:
					flag = shp->move(Courses::DOWN);
					break;
				case KEY_ARROW_RIGHT:
					flag = shp->move(Courses::RIGHT);
					break;
				case KEY_ARROW_LEFT:
					flag = shp->move(Courses::LEFT);
					break;
				case SPACE:
					shp->rotate();
				default:
					break;
				}
			}
			if(flag)
				flag = shp->fall();
			shp->draw();
			Sleep(INITIAL_SPEED);
		}
		fld.augment_score(fs.clear_tier(fld.get_width()));
		fs.wash();
		fs.draw();
		shp = next_shp;
		if (!fs.status_check())
			shp->game_over();
	}
}

void render(std::shared_ptr<Shape> shape, Field* const field)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		mtx1.lock();
		shape->clear();
		shape->draw();
		mtx1.unlock();
	}
}

void faller(std::shared_ptr<Shape> shape, bool& flag)
{
	while (flag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(INITIAL_SPEED/shape->get_speed())));
		mtx1.lock();
		shape->clear();
		flag = shape->fall();
		shape->draw();
		mtx1.unlock();
	}
}

void logic(std::shared_ptr<Shape> shp)
{
	if (_kbhit())
	{
		mtx1.lock();
		switch (_getch())
		{
		case KEY_ARROW_DOWN:
			shp->move(Courses::DOWN);
			break;
		case KEY_ARROW_RIGHT:
			shp->move(Courses::RIGHT);
			break;
		case KEY_ARROW_LEFT:
			shp->move(Courses::LEFT);
			break;
		case SPACE:
			shp->rotate();
		default:
			break;
		}
		mtx1.unlock();
	}
}

void multi_game()
{
	Field fld(10, 20, 15);
	fld.draw();
	std::shared_ptr<Shape> shp(rand_shape(&fld));
	while (true)
	{
		bool flag = true;
		std::shared_ptr<Shape> next_shp(rand_shape(&fld));
		fld.draw_next_shape(next_shp.get());
		std::thread drop(faller, shp, std::ref(flag));
		while (flag)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case KEY_ARROW_DOWN:
					mtx1.lock();
					shp->clear();
					flag = shp->move(Courses::DOWN);
					shp->draw();
					mtx1.unlock();
					break;
				case KEY_ARROW_RIGHT:
					mtx1.lock();
					shp->clear();
					shp->move(Courses::RIGHT);
					shp->draw();
					mtx1.unlock();
					break;
				case KEY_ARROW_LEFT:
					mtx1.lock();
					shp->clear();
					shp->move(Courses::LEFT);
					shp->draw();
					mtx1.unlock();
					break;
				case SPACE:
					mtx1.lock();
					shp->clear();
					shp->rotate();
					shp->draw();
					mtx1.unlock();
				default:
					break;
				}
			}
		}
		drop.join();
		shp = next_shp;
		fs.wash();
		auto score = fs.clear_tier(fld.get_width());
		fld.augment_score(score);
		shp->augment_speed(sqrt(score) * SPEED_MULTIPIER);
		fs.draw();
		if (!fs.status_check())
			shp->game_over();
	}
}