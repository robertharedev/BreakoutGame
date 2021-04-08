#include "BreakoutGame.h"

BreakoutGame::BreakoutGame() {
	setImmediateDrawMode(false);
}

BreakoutGame::~BreakoutGame() {
	for (int i = 0; i < blocks->size(); i++)
		delete blocks->at(i);

	delete blocks;
	Paddle::deletePaddle();
	// delete ball/s (may be many balls)
}

void BreakoutGame::onCreate() {
	EasyGraphics::onCreate();

	::SetWindowText(getHWND(), L"Breakout Game");

	// create blocks from text file
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