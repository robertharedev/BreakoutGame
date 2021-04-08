#include "Ball.h"

Ball::Ball() : x(200), y(600), r(10) {

}

Ball::~Ball() {

}

void Ball::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::WHITE, 1); // remove outline
	canvas->setBackColour(EasyGraphics::WHITE);
	canvas->drawCircle(x, y, r, true);
}