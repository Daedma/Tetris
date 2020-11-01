#pragma once
#include "Shape.h"
class Shape_Z :
	public Shape
{
public:
	Shape_Z(Falling_shapes* const, Field* const);
	bool rotate() override;
};

