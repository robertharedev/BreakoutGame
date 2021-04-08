#include "BreakoutGame.h"

BreakoutGame::BreakoutGame() {
	setImmediateDrawMode(false);

	ball = new Ball();
}

BreakoutGame::~BreakoutGame() {
	for (int i = 0; i < blocks->size(); i++)
		delete blocks->at(i);

	delete blocks;
	Paddle::deletePaddle(); // Paddle deletes itself
	delete ball; // delete ball/s (may be many balls)
}

void BreakoutGame::onCreate() {
	EasyGraphics::onCreate();

	::SetWindowText(getHWND(), L"Breakout Game");

	// create blocks from text file 
	// this is done after the window is created so the blocks are the correct width/height
	blocks = Block::loadBlocks(L"blockPlacement.txt", getHWND());
}

void BreakoutGame::onDraw() {
	clearScreen(DARK_GREY);
	setPenColour(BLACK, 1);

	// draw blocks
	Block::drawBlocks(this, blocks);
	// draw paddle
	Paddle::getPaddle()->draw(this);
	// draw ball
	ball->draw(this);

	EasyGraphics::onDraw();
}



// ########### I THINK THE PADDLE SHOULD HAVE THIS STUFF BUT IM KEEPING IT HERE FOR A BIT #######################

void BreakoutGame::onMouseMove(UINT nFlags, int x, int y) {
	Paddle::getPaddle()->setPosition(x);

	onDraw();
}

void BreakoutGame::onTimer(UINT nIDEvent) {
	// timer for animating ball's contant movement


	onDraw();
}