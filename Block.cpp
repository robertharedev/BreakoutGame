#include "Block.h"
#include <fstream>

Block::Block(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
	// give block a health/colour/powerup/points
	initialiseProperties();
}

Block::~Block() {
	
}

vector<Block*>* Block::loadBlocks(const wchar_t* filename, HWND hwnd) {
	vector<Block*>* blocks = new vector<Block*>();
	// set block width/height based on size of canvas
	RECT rect;
	GetClientRect(hwnd, &rect);
	int columns = 12;
	int rows = 8;
	int blockWidth = rect.right / (columns + 2);
	int blockHeight = rect.bottom / (rows + 2) / 4;

	// read through txt file and create a block with the correct x, y
	ifstream fin(filename, ios::in);
	if (!fin.fail()) {
		int x, y;

		fin >> x >> y;
		while (!fin.eof()) {
			// Create block
			blocks->push_back(new Block(x, y, blockWidth, blockHeight));

			// read in the next line
			fin >> x >> y;
		}

		fin.close();
	}

	return blocks;
}

void Block::drawBlocks(EasyGraphics* canvas, vector<Block*>* blocks) {
	// draw blocks based on their x * width and y * height
	vector<Block*>::iterator it(blocks->begin());
	while (it != blocks->end()) {
		Block* block = *(it);
		block->draw(canvas, block->x * block->w, block->y * block->h);
		it++;
	}
}

void Block::draw(EasyGraphics* canvas, int x, int y) const {
	// colour block based on health
	canvas->setBackColour(fillColour);
	canvas->drawRectangle(x, y, w, h, true);
}

void Block::initialiseProperties() {
	this->health = rand() % 3 + 1; // random health between 1-3

	// set colour based on health
	switch (health)
	{
	case 1:
		fillColour = EasyGraphics::GREEN;
		points = 5;
		break;
	case 2:
		fillColour = EasyGraphics::YELLOW;
		points = 10;
		break;
	case 3:
		fillColour = EasyGraphics::RED;
		points = 20;
		break;
	}

	float powerupChance = (float(rand()) / float((RAND_MAX)) * 1); // random float between 0-1
	if (powerupChance < 0.1f) // 10% chance to have a powerup
		containsPowerup = true;
}