#include "Ball.h"

Ball::Ball() : x(400), y(600), r(10) {
	resetSpeed();
}

Ball::~Ball() {

}

void Ball::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::WHITE, 1); // remove outline
	canvas->setBackColour(EasyGraphics::WHITE);
	canvas->drawCircle(x, y, r, true);
}

void Ball::CheckForBounce(RECT* rect, Paddle* paddle) {
	// wall and ceiling collision
	if (x + r >= rect->right) {
		setPosition(rect->right - r, y);
		xSpeed *= -1;
	}
	if (x - r <= rect->left) {
		setPosition(rect->left + r, y);
		xSpeed *= -1;
	}
	if (y - r <= rect->top) {
		setPosition(x, rect->top + r);
		ySpeed *= -1;
	}

	// paddle collision
	int px = paddle->getX();
	int py = paddle->getY();
	int pw = paddle->getWidth();
	int ph = paddle->getHeight();

	// if it hits paddle
	// I don't check if the ball is under the paddle because at high speed, the ball flies through the paddle
	if (y + r >= py && x >= px && x <= px + pw) { 
		ySpeed *= -1; // bounce the ball up

		// set x speed depending on where the ball hit the paddle
		if (x < px + pw / 5) // far left portion
			xSpeed = -6;
		else if (x >= px + pw / 5 && x < px + (pw / 5 * 2)) // bit left portion
			xSpeed = -3;
		else if (x >= px + (pw / 5 * 3) && x < px + (pw / 5 * 4)) // bit right portion
			xSpeed = 3;
		else if (x >= px + (pw / 5 * 4) && x < px + pw) // far right portion
			xSpeed = 6;
	}

}

void Ball::resetSpeed() {
	xSpeed = rand() % 9 - 4; // between -4 and 4 inclusive
	ySpeed = -8;
}