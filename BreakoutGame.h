#pragma once
#include "EasyGraphics.h"
#include "Block.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

using namespace std;

class BreakoutGame : public EasyGraphics // inheritance
{
public:
	BreakoutGame();
	~BreakoutGame();

	int getLives();
	void setLives(int lives);

private:
	virtual void onCreate();
	virtual void onDraw();
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void onTimer(UINT nIDEvent);

	template<typename T> void addToScore(T points);

	void drawLives(EasyGraphics* canvas) const;
	void drawScore(EasyGraphics* canvas) const;
	void drawStartGameText(EasyGraphics* canvas) const;

	// billboard text that covers the screen
	void drawBillboardText(EasyGraphics* canvas, const wchar_t* text, int x, int y, int fontSize, int textColour) const;

	BreakoutGame* operator-(BreakoutGame& bg);

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

template<typename T>
void BreakoutGame::addToScore(T points) {
	score += points;
}

inline void BreakoutGame::removeLife() { lives--; }

inline int BreakoutGame::getLives() { return lives; }
inline void BreakoutGame::setLives(int lives) { this->lives = lives; }

