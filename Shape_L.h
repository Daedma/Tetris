#pragma once
#include "Shape.h"
class Shape_L :
	public Shape
{
public:
	Shape_L(Falling_shapes* const, Field* const);
	bool rotate() override;
};

