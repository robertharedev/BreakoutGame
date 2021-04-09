#include "BreakoutGame.h"
#include <string>
#include <algorithm>

using namespace std;

BreakoutGame::BreakoutGame() : lives(3), score(0), maxScore(0), showStartGameText(true), gameOver(false), gameWon(false) {
	setImmediateDrawMode(false);

	ball = new Ball();
}

BreakoutGame::~BreakoutGame() {
	deleteBlocks();

	Paddle::deletePaddle(); // Paddle deletes itself
	delete ball; // delete ball/s (may be many balls)
}

void BreakoutGame::onCreate() {
	EasyGraphics::onCreate();

	::SetWindowText(getHWND(), L"Robert Hare OOP4CS: Breakout Game");

	// create blocks from text file 
	// this is done after the window is created so the blocks are the correct width/height
	blocks = Block::loadBlocks(L"blockPlacement.txt", getHWND());
}

void BreakoutGame::onDraw() {
	clearScreen(BLACK);

	if (!gameOver) {
		Block::drawBlocks(this, blocks);
		Paddle::getPaddle()->draw(this);
		ball->draw(this);
		drawLives(this);
		drawScore(this);

		// draw start game text on screen reset
		if (showStartGameText)
			drawStartGameText(this);
	}
	else if (gameWon && gameOver) { // win game condition
		drawGameWonScreen(this);
	}
	else drawGameOver(this);

	// sets gameWon to true
	if (Block::getDestroyedBlockCount() == blocks->size()) {
		gameWon = true;
		gameOver = true;
	}

	EasyGraphics::onDraw();
}

void BreakoutGame::onMouseMove(UINT nFlags, int x, int y) {
	Paddle::getPaddle()->setPosition(x);
}

void BreakoutGame::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// start ball timer so it can move
	if (nChar == VK_SPACE) { // if space is pressed

		moveBall = 101;
		moveBall = SetTimer(getHWND(), moveBall, 1, NULL);
		lastTick = GetTickCount64();

		// remove "start game" text
		showStartGameText = false;
	}
}

void BreakoutGame::onTimer(UINT nIDEvent) {

	//DWORD now = GetTickCount64();
	//DWORD elapsed = now - lastTick;

	// timer for animating ball's constant movement
	if (nIDEvent == moveBall) {
		// move ball
		int x = ball->getX() + ball->getXSpeed();
		int y = ball->getY() + ball->getYSpeed();
		ball->setPosition(x, y);

		// check if it needs to bounce (edge of screen or paddle)
		RECT rect;
		GetClientRect(getHWND(), &rect);
		ball->CheckForBounce(&rect, Paddle::getPaddle());
		
		checkIfBallOutOfPlay(&rect);

		// slowly increase ball speed;
		ball->increaseSpeed();

		// check through all blocks and if the ball x, y is within the block, remove health and bounce it
		vector<Block*>::iterator it(blocks->begin());
		while (it != blocks->end()) {
			Block* block = *(it); // variable for readability

			// collision detection
			// check if any block is hit by ball
			// only check for hit if block isn't destroyed
			if (!block->isDestroyed()) {
				int side = block->calcHit(ball);
				if (side) { // if block has been hit by ball
					// check which side of the block the ball hit so it can bounce in the correct direction
					if (side == 1) {
						ball->reverseYSpeed();
					}
					if (side == 2) {
						ball->reverseXSpeed();
					}

					score += block->getPoints();
					block->removeHealth();
				}
			}

			it++;
		}

		//lastTick = now;

		onDraw();
	}
}

void BreakoutGame::drawStartGameText(EasyGraphics* canvas) const {
	canvas->setTextColour(WHITE);
	canvas->drawText(L"Press [SPACE] to start", 250, 500);
}

void BreakoutGame::drawLives(EasyGraphics* canvas) const {
	canvas->setTextColour(DARK_GREY);
	canvas->setFont(20, L""); // Increase font size

	// draw lives on screen
	wstring livesText = L"Lives: " + to_wstring(lives);
	const wchar_t* wlivesText = livesText.c_str();
	canvas->drawText(wlivesText, 50, 350);
}

void BreakoutGame::drawScore(EasyGraphics* canvas) const {
	canvas->setTextColour(DARK_GREY);
	canvas->setFont(20, L""); // Increase font size

	// draw lives on screen
	wstring livesText = L"Score: " + to_wstring(score);
	const wchar_t* wlivesText = livesText.c_str();
	canvas->drawText(wlivesText, 50, 380);
}

void BreakoutGame::checkIfBallOutOfPlay(RECT* rect) {
	if (ball->getY() >= rect->bottom) {
		// reset the game and remove lives
		lives--;
		resetGame();
	}

	if (lives == 0) // check for game over
		gameOver = true;
}

void BreakoutGame::drawGameOver(EasyGraphics* canvas) const {
	canvas->setTextColour(WHITE);
	canvas->setFont(70, L"");
	canvas->drawText(L"GAME OVER", 100, 300);
}

void BreakoutGame::drawGameWonScreen(EasyGraphics* canvas) const {
	canvas->setTextColour(WHITE);
	canvas->setFont(90, L"");
	canvas->drawText(L"YOU WIN!", 100, 300);
}

void BreakoutGame::resetGame() {
	ball->resetSpeed();
	killTimer(moveBall);
	ball->setPosition(400, 600);
	showStartGameText = true;
}

void deleteBlock(Block* block) {
	delete block;
}

void BreakoutGame::deleteBlocks() {
	for_each(blocks->begin(), blocks->end(), deleteBlock);
	delete blocks;
}
