#pragma once
#include "Ball.h"

using namespace std;

class Block
{
public:
	Block(int x, int y, int w, int h);
	~Block();

	static vector<Block*>* loadBlocks(const wchar_t* filename, HWND hwnd); // load block patterns from text file
	static void drawBlocks(EasyGraphics* canvas, vector<Block*>* blocks);
	void draw(EasyGraphics* canvas, int x, int y) const; // derived blocks draw themselves

	void removeHealth(); // remove health when hit
	void destroy();

	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
	int getPoints() const;
	int getHealth() const;

	bool isDestroyed() const;
	int calcHit(Ball* ball) const;

private:
	int x, y, w, h, penColour, fillColour, health, points;
	bool containsPowerup;
	bool destroyed = false;

	void initialiseProperties();
	void updateProperties(); // change colour/points
};

inline void Block::removeHealth() {
	health--;
	updateProperties();
}

inline void Block::destroy() { destroyed = true; }

inline int Block::getWidth() const { return w; }
inline int Block::getHeight() const { return h; }
inline int Block::getX() const { return x; }
inline int Block::getY() const { return y; }

inline int Block::getPoints() const { return points; }
inline int Block::getHealth() const { return health; }

inline bool Block::isDestroyed() const { return destroyed; }