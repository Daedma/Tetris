#pragma once
#include "Shape.h"
class Shape_T :
	public Shape
{
public:
	Shape_T(Falling_shapes* const, Field* const);
	bool rotate() override;
};

