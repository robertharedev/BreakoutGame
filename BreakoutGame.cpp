#include "BreakoutGame.h"

BreakoutGame::BreakoutGame() {
	setImmediateDrawMode(false);

	// create blocks and their random positions
	//blocks->push_back(new Block(100, 200, RED));
	blocks = Block::generateBlocks();
}

BreakoutGame::~BreakoutGame() {
	for (int i = 0; i < blocks->size(); i++)
		delete blocks->at(i);

	delete blocks;
}

void BreakoutGame::onCreate() {
	EasyGraphics::onCreate();

	::SetWindowText(getHWND(), L"Breakout Game");
}

void BreakoutGame::onDraw() {
	clearScreen(DARK_GREY);
	setPenColour(BLACK, 1);

	// draw blocks
	int x = 0;
	int y = 0;
	for (int i = 0; i < 64; i++) {
		blocks->at(i)->draw(this, x, y);
		x += 100;
		if (x == 800) {
			x = 0;
			y += 50;
		}
	}
	// draw ball
	// draw paddle

	EasyGraphics::onDraw();
}

void BreakoutGame::onMouseMove(UINT nFlags, int x, int y) {

}