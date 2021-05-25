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

	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	static Paddle* paddle;

	Paddle();

	// initialised in constructor initialisation list
	int x; // not const as paddle moves on x-axis
	const int Y;
	const int WIDTH; // may make this non-const because it's size could change with a powerup
	const int HEIGHT;
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

inline int Paddle::getX() { return x; };
inline int Paddle::getY() { return Y; };
inline int Paddle::getWidth() { return WIDTH; };
inline int Paddle::getHeight() { return HEIGHT; };