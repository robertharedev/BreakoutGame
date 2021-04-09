#pragma once
#include "EasyGraphics.h"
#include "Block.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

using namespace std;

class BreakoutGame : public EasyGraphics
{
public:
	BreakoutGame();
	~BreakoutGame();

private:
	virtual void onCreate();
	virtual void onDraw();
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void onTimer(UINT nIDEvent);

	void drawLives(EasyGraphics* canvas) const;
	void drawScore(EasyGraphics* canvas) const;
	void drawStartGameText(EasyGraphics* canvas) const;
	void drawGameOver(EasyGraphics* canvas) const;
	void drawGameWonScreen(EasyGraphics* canvas) const;

	void checkIfBallOutOfPlay(RECT* rect);
	void removeLife();
	void resetGame();

	void deleteBlocks();

	int lives;
	int score;
	int maxScore;

	vector<Block*>* blocks; // Blocks
	Paddle* getPaddle() const;  // Paddle (Singleton)
	Ball* ball; // Ball

	int moveBall;
	DWORD lastTick;

	bool showStartGameText;
	bool gameOver;
	bool gameWon;
};

inline void BreakoutGame::removeLife() { lives--; }