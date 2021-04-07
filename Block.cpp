#include "Block.h"
#include <fstream>

Block::Block(int x, int y) : x(x), y(y) {
	// give block a random health between 1-3 inclusive
	initialiseHealth();
	
	if (health == 3)
		this->containsPowerup = true;
}

Block::~Block() {
	
}

vector<Block*>* Block::loadBlocks(const wchar_t* filename) {
	vector<Block*>* blocks = new vector<Block*>();

	// read through txt file and create a block with the correct x, y
	ifstream fin(filename, ios::in);
	if (!fin.fail()) {
		int x, y;

		fin >> x >> y;
		while (!fin.eof()) {
			// Create block
			blocks->push_back(new Block(x, y));

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
		block->draw(canvas, block->x * block->getWidth(), block->y * block->getHeight());
		it++;
	}

	/*int x = 0;
	int y = 0;
	for (int i = 0; i < blocks->size(); i++) {
		blocks->at(i)->draw(canvas, x, y);
		x += blocks->at(i)->getWidth();
		if (x == 800) {
			x = 0;
			y += blocks->at(i)->getHeight();
		}
	}*/
}

void Block::draw(EasyGraphics* canvas, int x, int y) const {
	// colour block based on health
	if (health == 1) canvas->setBackColour(EasyGraphics::GREEN);
	else if (health == 2) canvas->setBackColour(EasyGraphics::YELLOW);
	else canvas->setBackColour(EasyGraphics::RED);

	canvas->drawRectangle(x, y, WIDTH, HEIGHT, true);
}

