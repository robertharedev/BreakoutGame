#include "Ball.h"

Ball::Ball() : x(200), y(600), r(10), xSpeed(3), ySpeed(-3) {

}

Ball::~Ball() {

}

void Ball::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::WHITE, 1); // remove outline
	canvas->setBackColour(EasyGraphics::WHITE);
	canvas->drawCircle(x, y, r, true);
}

void Ball::CheckForBounce(RECT* rect) {
	if (x + r > rect->right || x - r < rect->left)
		xSpeed *= -1;
	if (y - r < rect->top)
		ySpeed *= -1;
}