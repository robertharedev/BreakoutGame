#include "Paddle.h"

Paddle* Paddle::paddle = nullptr; // static so must instantiate

Paddle::Paddle() : Y(700), WIDTH(150), HEIGHT(10) {

}

Paddle::~Paddle() {

}

void Paddle::draw(EasyGraphics* canvas) const {
	canvas->setPenColour(EasyGraphics::WHITE, 1);
	canvas->setBackColour(EasyGraphics::WHITE);
	canvas->drawRectangle(x, Y, WIDTH, HEIGHT, true);
}
