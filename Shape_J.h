#pragma once
#include "Shape.h"
class Shape_J :
	public Shape
{
public:
	Shape_J(Falling_shapes* const, Field* const);
	bool rotate() override;
};

