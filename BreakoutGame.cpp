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

	::SetWindowText(getHWND(), L"Robert Hare OOP4CS: Breakout Game");

	// create blocks from text file 
	// this is done after the window is created so the blocks are the correct width/height
	blocks = Block::loadBlocks(L"blockPlacement.txt", getHWND());
}

void BreakoutGame::onDraw() {
	clearScreen(BLACK);

	Block::drawBlocks(this, blocks);
	Paddle::getPaddle()->draw(this);
	ball->draw(this);
	drawLives(this);
	drawScore(this);

	if (showStartGameText) drawStartGameText(this);
	

	EasyGraphics::onDraw();
}

void BreakoutGame::onMouseMove(UINT nFlags, int x, int y) {
	Paddle::getPaddle()->setPosition(x);
}

void BreakoutGame::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//DWORD now = GetTickCount64();
	//DWORD elapsed = now - lastTick;

	// start ball timer so it can move
	if (nChar == VK_SPACE) { // if space is pressed

		moveBall = 101;
		moveBall = SetTimer(getHWND(), moveBall, 5, NULL);
		lastTick = GetTickCount64();

		// remove "start game" text
		showStartGameText = false;
	}

	//lastTick = now;
}

void BreakoutGame::onTimer(UINT nIDEvent) {
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
		
		checkIfBallOutOfPlay(ball, &rect, moveBall);

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

void BreakoutGame::checkIfBallOutOfPlay(Ball* ball, RECT* rect, int timerID) {
	if (ball->getY() > rect->bottom) {
		delete ball;
		ball = new Ball();

		lives--;
		KillTimer(getHWND(), timerID);
		showStartGameText = true;
	}
}