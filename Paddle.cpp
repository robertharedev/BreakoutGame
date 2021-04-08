#include "Paddle.h"

Paddle* Paddle::paddle = nullptr; // static so must instantiate

Paddle::Paddle() {

}

Paddle::~Paddle() {

}

void Paddle::draw(EasyGraphics* canvas) const {
	canvas->setBackColour(EasyGraphics::BLUE);
	canvas->drawRectangle(x, Y, WIDTH, HEIGHT, true);
}
