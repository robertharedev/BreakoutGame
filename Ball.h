#pragma once

#include "EasyGraphics.h"

class Ball
{
public:
	Ball();
	~Ball();

	void draw(EasyGraphics* canvas) const;

private:
	int x, y, r;
};

