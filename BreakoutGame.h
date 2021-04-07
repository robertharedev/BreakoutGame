#pragma once
#include "EasyGraphics.h"
#include "Block.h"
//#include "Paddle.h"
//#include "Ball.h"
#include <vector>

using namespace std;

class BreakoutGame : public EasyGraphics
{
public:
	BreakoutGame();
	~BreakoutGame();

	virtual void onCreate();
	virtual void onDraw();
	virtual void onChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void onTimer(UINT nIDEvent);

private:
	vector<Block*>* blocks; // Blocks
	// Paddle (Singleton)
	// Ball
	// Leaderboard (Singleton)
};

