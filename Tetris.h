#pragma once
#include "Shape_I.h"
#include "Shape_J.h"
#include "Shape_L.h"
#include "Shape_O.h"
#include "Shape_S.h"
#include "Shape_T.h"
#include "Shape_Z.h"

size_t shape_gen();
Shape* rand_shape(Field* const, Falling_shapes* const = &fs);
void game();
void multi_game();
void render(std::shared_ptr<Shape>, Field* const);
void faller(std::shared_ptr<Shape>, bool&);
void logic(std::shared_ptr<Shape>);

extern std::mutex mtx1;