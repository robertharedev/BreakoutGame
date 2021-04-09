#pragma once

#include "EasyGraphics.h"

class Ball
{
public:
	Ball();
	~Ball();

	void draw(EasyGraphics* canvas) const;
	void setPosition(int x, int y); // move ball by an amount
	void CheckForBounce(RECT* rect);

	int getX() const;
	int getY() const;
	int getXSpeed() const;
	int getYSpeed() const;
	int getRadius() const;
	void reverseXSpeed();
	void reverseYSpeed();

private:
	int x, y, r, xSpeed, ySpeed;
};

inline void Ball::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

inline int Ball::getX() const { return x; }
inline int Ball::getY() const { return y; }
inline int Ball::getXSpeed() const { return xSpeed; }
inline int Ball::getYSpeed() const { return ySpeed; }
inline int Ball::getRadius() const { return r; }

inline void Ball::reverseXSpeed() { xSpeed *= -1; }
inline void Ball::reverseYSpeed() { ySpeed *= -1; }