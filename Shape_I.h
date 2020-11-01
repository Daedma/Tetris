#pragma once
#include "Shape.h"
class Shape_I :
	public Shape
{
public:
	Shape_I(Falling_shapes* const, Field* const);
	bool rotate() override;
};

