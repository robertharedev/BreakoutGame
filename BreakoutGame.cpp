#include "BreakoutGame.h"

BreakoutGame::BreakoutGame() {
	setImmediateDrawMode(false);

	// create blocks from text file
	blocks = Block::loadBlocks(L"blockPlacement.txt");
	paddle = new Paddle();
}

BreakoutGame::~BreakoutGame() {
	for (int i = 0; i < blocks->size(); i++)
		delete blocks->at(i);

	delete blocks;
	delete paddle; // delete paddle
	// delete ball/s (may be many balls)
}

void BreakoutGame::onCreate() {
	EasyGraphics::onCreate();

	::SetWindowText(getHWND(), L"Breakout Game");
}

void BreakoutGame::onDraw() {
	clearScreen(DARK_GREY);
	setPenColour(BLACK, 1);

	// draw blocks
	Block::drawBlocks(this, blocks);
	// draw paddle
	paddle->draw(this);
	// draw ball

	EasyGraphics::onDraw();
}



// ########### I THINK THE PADDLE SHOULD HAVE THIS STUFF BUT IM KEEPING IT HERE FOR A BIT #######################

void BreakoutGame::onChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == 'a' || nChar == 'A')
		paddle->moveLeft();
	else if (nChar == 'd' || nChar == 'D')
		paddle->moveRight();

	onDraw();
}

void BreakoutGame::onTimer(UINT nIDEvent) {
	// timer for animating ball's contant movement


	onDraw();
}