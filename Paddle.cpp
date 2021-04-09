#include "Paddle.h"

Paddle* Paddle::paddle = nullptr; // static so must instantiate

Paddle::Paddle() {

}

Paddle::~Paddle() {

}

void Paddle::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::WHITE, 1);
	canvas->setBackColour(EasyGraphics::WHITE);
	canvas->drawRectangle(x, Y, WIDTH, HEIGHT, true);
}
