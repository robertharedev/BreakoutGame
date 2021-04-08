#include "Paddle.h"

Paddle::Paddle() {

}

Paddle::~Paddle() {

}

void Paddle::draw(EasyGraphics* canvas) const {
	canvas->setBackColour(EasyGraphics::RED);
	canvas->drawRectangle(x, Y, WIDTH, HEIGHT, true);
}
