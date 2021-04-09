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
	if (x + r > rect->right || x - r < rect->left)
		xSpeed *= -1;
	if (y - r < rect->top)
		ySpeed *= -1;

	// paddle collision
	int px = paddle->getX();
	int py = paddle->getY();
	int pw = paddle->getWidth();
	int ph = paddle->getHeight();

	// if it hits paddle
	if (y + r >= py && y + r <= py + ph && x >= px && x <= px + pw) {
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
		else { // if ball hits paddle in the middle, increase ball speed
			ySpeed *= 1.2;
			xSpeed *= 1.2; // increase ball speed by 40%
		}
	}

}

void Ball::resetSpeed() {
	xSpeed = rand() % 9 - 4; // between -4 and 4 inclusive
	ySpeed = -(rand() % 4 + 3); // between 3 and 6 negative so the ball moves up initially
}