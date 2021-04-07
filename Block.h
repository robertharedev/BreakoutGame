#pragma once
#include "EasyGraphics.h"

using namespace std;

class Block
{
public:
	Block(int x, int y);
	~Block();

	static vector<Block*>* loadBlocks(const wchar_t* filename); // load block patterns from text file
	static void drawBlocks(EasyGraphics* canvas, vector<Block*>* blocks);
	void draw(EasyGraphics* canvas, int x, int y) const; // derived blocks draw themselves
	int getWidth() const;
	int getHeight() const;

private:
	int x, y, penColour, fillColour, health, points;
	const int WIDTH = 100;
	const int HEIGHT = 50;
	bool containsPowerup;
	bool isDestroyed = false;

	void initialiseProperties();
};

inline int Block::getWidth() const { return WIDTH; }
inline int Block::getHeight() const { return HEIGHT; }