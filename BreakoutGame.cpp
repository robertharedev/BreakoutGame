#include "BreakoutGame.h"

BreakoutGame::BreakoutGame() {
	setImmediateDrawMode(false);

	// create blocks and their random positions
	//blocks->push_back(new Block(100, 200, RED));
	blocks = Block::loadBlocks(L"blockPlacement.txt");
}

BreakoutGame::~BreakoutGame() {
	for (int i = 0; i < blocks->size(); i++)
		delete blocks->at(i);

	delete blocks;

	// delete paddle
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

	// draw ball

	EasyGraphics::onDraw();
}



// ########### I THINK THE PADDLE SHOULD HAVE THIS STUFF BUT IM KEEPING IT HERE FOR A BIT #######################

void BreakoutGame::onChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	/*
	if (nChar == 'a' || nChar == 'A') {
		paddle->setMovePaddleLeftID(101);
		paddle->setMovePaddleLeftID(SetTimer(getHWND(), paddle->getMovePaddleLeftID(), 30, null));
		lastTick = GetTickCount();
	}
	else if (nChar == 'd' || nChar == 'D') {
		paddle->setMovePaddleRightID(102);
		paddle->setMovePaddleRightID(SetTimer(getHWND(), paddle->getMovePaddleRightID(), 30, null));
		lastTick = GetTickCount();
	}*/
}

void BreakoutGame::onTimer(UINT nIDEvent) {
	/*DWORD now = GetTickCount();
	DWORD elapsed = now - lastTick;

	if (nIDEvent == paddle->getMovePaddleLeftID())
		x -= (moveSpeed * elapsed) / 1000;
	else if (nIDEvent == paddle->getMovePaddleRightID())
		x += (moveSpeed * elapsed) / 1000;

	lastTick = now;
	*/
	onDraw();
}