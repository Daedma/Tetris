#pragma once
#include "Shape.h"
class Shape_O :
	public Shape
{
public:
	Shape_O(Falling_shapes* const, Field* const);
	bool rotate() override;
};

