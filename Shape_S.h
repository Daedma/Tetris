#pragma once
#include "Shape.h"
class Shape_S :
	public Shape
{
public:
	Shape_S(Falling_shapes* const, Field* const);
	bool rotate() override;
};

