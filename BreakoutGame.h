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
	virtual void onTimer(UINT nIDEvent);

private:
	vector<Block*>* blocks; // Blocks
	Paddle* getPaddle() const;  // Paddle (Singleton)
	Ball* ball; // Ball
};
