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
	canvas->setPenColour(fillColour, 1); // remove outline
	canvas->setBackColour(fillColour);
	canvas->drawRectangle(x, y, w, h, true);
}

void Block::initialiseProperties() {
	float randFloat = (float(rand()) / float((RAND_MAX)) * 1); // random float between 0-1

	if (randFloat <= 0.5f) {								// 50% chance it is weak
		health = 1;
		fillColour = EasyGraphics::GREEN;
		points = 5;
	}
	else if (randFloat > 0.5f && randFloat <= 0.85f) {		// 35% chance it is medium strength
		health = 2;
		fillColour = EasyGraphics::YELLOW;
		points = 10;
	}
	else {													// 15% chance it is strong
		health = 3;
		fillColour = EasyGraphics::RED;
		points = 20;
	}

	float powerupChance = (float(rand()) / float((RAND_MAX)) * 1); // random float between 0-1
	if (powerupChance < 0.05f) // 5% chance to have a powerup
		containsPowerup = true;
}

void Block::updateColour() {
	switch (health) {
	case 1:
		fillColour = EasyGraphics::GREEN;
		break;
	case 2:
		fillColour = EasyGraphics::YELLOW;
		break;
	}
}