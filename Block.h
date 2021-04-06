#pragma once
#include "EasyGraphics.h"

using namespace std;

class Block
{
public:
	Block();
	~Block();

	void draw(EasyGraphics* canvas, int x, int y) const; // derived blocks draw themselves
	static vector<Block*>* generateBlocks(); // randomly generate block patterns
	int getWidth() const;
	int getHeight() const;

private:
	int x, y, penColour, health;
	const int WIDTH = 100;
	const int HEIGHT = 50;
	bool containsPowerup;
	bool beenHit = false;

	void initialiseHealth();
};

inline int Block::getWidth() const { return WIDTH; }
inline int Block::getHeight() const { return HEIGHT; }

inline void Block::initialiseHealth() { this->health = rand() % 3 + 1; }