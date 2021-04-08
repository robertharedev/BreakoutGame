#include "Paddle.h"

Paddle* Paddle::paddle = nullptr; // static so must instantiate

Paddle::Paddle() {

}

Paddle::~Paddle() {

}

void Paddle::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::BLACK, 1);
	canvas->setBackColour(EasyGraphics::BLACK);
	canvas->drawRectangle(x, Y, WIDTH, HEIGHT, true);
}
