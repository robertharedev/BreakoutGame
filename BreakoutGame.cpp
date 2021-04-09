#include "BreakoutGame.h"
#include <string>

BreakoutGame::BreakoutGame() : lives(3), score(0), showStartGameText(true) {
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
	clearScreen(BLACK);

	// draw blocks
	Block::drawBlocks(this, blocks);
	// draw paddle
	Paddle::getPaddle()->draw(this);
	// draw ball
	ball->draw(this);
	// draw lives
	drawLives(this);
	// draw start game text
	if (showStartGameText) drawStartGameText(this);

	EasyGraphics::onDraw();
}

void BreakoutGame::onMouseMove(UINT nFlags, int x, int y) {
	Paddle::getPaddle()->setPosition(x);
}

void BreakoutGame::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_SPACE) { // if space is pressed
		// start ball timer so it can move
		moveBall = 101;
		moveBall = SetTimer(getHWND(), moveBall, 5, NULL);
		lastTick = GetTickCount64();

		// remove "start game" text
		showStartGameText = false;
	}
}

void BreakoutGame::onTimer(UINT nIDEvent) {
	// timer for animating ball's constant movement
	if (nIDEvent == moveBall) {
		DWORD now = GetTickCount64();
		DWORD elapsed = now - lastTick;

		// move ball
		int x = ball->getX() + ball->getXSpeed();
		int y = ball->getY() + ball->getYSpeed();
		ball->setPosition(x, y);

		// check if it needs to bounce (edge of screen)
		RECT rect;
		GetClientRect(getHWND(), &rect);
		ball->CheckForBounce(&rect);

		// check through all blocks and if the ball x, y is within the block, remove health and bounce it
		vector<Block*>::iterator it(blocks->begin());
		while (it != blocks->end()) {
			// collision detection
			// variables for readability
			Block* block = *(it);
			int ballX = ball->getX();
			int ballY = ball->getY();
			int ballRad = ball->getRadius();

			int blockX = block->getX() * block->getWidth();
			int blockY = block->getY() * block->getHeight();

			// check which side of the block the ball hit so it can bounce in the correct direction
			if ((ballX < blockX &&					// LEFT OR RIGHT
				ballX + ballRad > blockX &&
				ballY > blockY && ballY < blockY + block->getHeight()) ||
				(ballX > blockX + block->getWidth() &&
				ballX - ballRad < blockX + block->getWidth() &&
				ballY > blockY &&
				ballY < blockY + block->getHeight()))
			{
				ball->reverseXSpeed();
				score += block->getPoints();
			}
			else if ((ballY < blockY &&				// TOP OR BOTTOM
				ballY + ballRad > blockY &&
				ballX > blockX &&
				ballX < blockX + block->getWidth()) ||
				(ballY > blockY + block->getHeight() &&
				ballY - ballRad < blockY + block->getHeight() &&
				ballX < blockX + block->getWidth()))
			{
				ball->reverseYSpeed();
				block->removeHealth();
				score += block->getPoints();
			}

			it++;
		}

		lastTick = now;
		onDraw();
	}
}

void BreakoutGame::drawLives(EasyGraphics* canvas) {
	canvas->setTextColour(WHITE);
	canvas->setFont(20, L""); // Increase font size

	// draw lives on screen
	wstring livesText = L"Lives: " + to_wstring(lives);
	const wchar_t* wlivesText = livesText.c_str();
	canvas->drawText(wlivesText, 50, 720);
}

void BreakoutGame::drawStartGameText(EasyGraphics* canvas) {
	canvas->drawText(L"Press [SPACE] to start", 250, 500);
}