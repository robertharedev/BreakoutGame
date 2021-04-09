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

	virtual void onCreate();
	virtual void onDraw();
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void onTimer(UINT nIDEvent);

	void drawLives(EasyGraphics* canvas) const;
	void drawScore(EasyGraphics* canvas) const;
	void drawStartGameText(EasyGraphics* canvas) const;
	void removeLife();
	void checkIfBallOutOfPlay(Ball* ball, RECT* rect, int timerID);

private:
	int lives;
	int score;

	vector<Block*>* blocks; // Blocks
	Paddle* getPaddle() const;  // Paddle (Singleton)
	Ball* ball; // Ball

	int moveBall;
	DWORD lastTick;

	bool showStartGameText;
};

inline void BreakoutGame::removeLife() { lives--; }