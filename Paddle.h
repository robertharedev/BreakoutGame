#pragma once
#include "EasyGraphics.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	void draw(EasyGraphics* canvas) const;
	void moveLeft();
	void moveRight();

private:
	int x = 300;
	const int Y = 700;
	const int WIDTH = 150; // may make this non-const because it's size could change with a powerup
	const int HEIGHT = 10;
	int moveSpeed = 10;
};

inline void Paddle::moveLeft() {
	if (x > 0) // cant move left off screen
		x -= moveSpeed;
}

inline void Paddle::moveRight() {
	if (x < 800 - WIDTH) // cant move right off screen
		x += moveSpeed;
}