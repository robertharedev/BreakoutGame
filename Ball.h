#pragma once
#include "Paddle.h"

class Ball
{
public:
	Ball();
	~Ball();

	void draw(EasyGraphics* canvas) const;
	void setPosition(int x, int y); // move ball by an amount
	void CheckForBounce(RECT* rect, Paddle* paddle);

	void reverseXSpeed();
	void reverseYSpeed();
	void resetSpeed();
	void increaseSpeed();

	int getX() const;
	int getY() const;
	float getXSpeed() const;
	float getYSpeed() const;
	int getRadius() const;

private:
	int x, y, r;
	float xSpeed, ySpeed;
};

inline void Ball::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

inline void Ball::increaseSpeed() {
	xSpeed *= 1.0005f;
	ySpeed *= 1.0005f;
}

inline int Ball::getX() const { return x; }
inline int Ball::getY() const { return y; }
inline float Ball::getXSpeed() const { return xSpeed; }
inline float Ball::getYSpeed() const { return ySpeed; }
inline int Ball::getRadius() const { return r; }

inline void Ball::reverseXSpeed() { xSpeed *= -1.0f; }
inline void Ball::reverseYSpeed() { ySpeed *= -1.0f; }