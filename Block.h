#pragma once
#include "EasyGraphics.h"

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

	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
	int getPoints() const;

private:
	int x, y, w, h, penColour, fillColour, health, points;
	bool containsPowerup;
	bool isDestroyed = false;

	void initialiseProperties();
	void updateColour(); // change colour or remove from vector when hit
};

inline void Block::removeHealth() {
	health--;
	updateColour();
}

inline int Block::getWidth() const { return w; }
inline int Block::getHeight() const { return h; }
inline int Block::getX() const { return x; }
inline int Block::getY() const { return y; }

inline int Block::getPoints() const { return points; }