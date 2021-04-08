#pragma once
#include "EasyGraphics.h"

class Paddle
{
public:
	static Paddle* getPaddle();
	~Paddle();

	void draw(EasyGraphics* canvas) const;
	void setPosition(int x);
	static void deletePaddle();

private:
	static Paddle* paddle;

	Paddle();

	int x;
	const int Y = 700;
	const int WIDTH = 150; // may make this non-const because it's size could change with a powerup
	const int HEIGHT = 10;
};

inline Paddle* Paddle::getPaddle() {
	if (!paddle)
		paddle = new Paddle();

	return paddle;
}

inline void Paddle::deletePaddle() { delete paddle; }

inline void Paddle::setPosition(int x) {
	this->x = x - (WIDTH / 2);
}
