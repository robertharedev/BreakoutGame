#pragma once
#include "EasyGraphics.h"
#include "Block.h"
#include <vector>

using namespace std;

class BreakoutGame : public EasyGraphics
{
public:
	BreakoutGame();
	~BreakoutGame();

protected:
	virtual void onCreate();
	virtual void onDraw();
	virtual void onMouseMove(UINT nFlags, int x, int y);

private:
	vector<Block*>* blocks;
	//Paddle
	//Ball
};

