#include "Block.h"

Block::Block() {
	// give block a random health between 1-3 inclusive
	initialiseHealth();
	
	if (health == 3)
		this->containsPowerup = true;
}

Block::~Block() {
	
}

void Block::draw(EasyGraphics* canvas, int x, int y) const {
	// colour block based on health
	if (health == 1) canvas->setBackColour(EasyGraphics::GREEN);
	else if (health == 2) canvas->setBackColour(EasyGraphics::YELLOW);
	else canvas->setBackColour(EasyGraphics::RED);

	canvas->drawRectangle(x, y, WIDTH, HEIGHT, true);
}

vector<Block*>* Block::generateBlocks() {
	vector<Block*>* blocks = new vector<Block*>();
	//int numOfBlocks = rand() % 20 + 44; // random number of blocks between 44-64 inclusive
	for (int i = 0; i < 64; i++) {
		blocks->push_back(new Block());
	}
	return blocks;
}
