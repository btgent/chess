#include "score.h"
#include "iostream"


Score::Score(float ws, float bs) :whiteScore{ ws }, blackScore{ bs } {}

Score::~Score() {}

void Score::drawAdd() {
	whiteScore += 0.5;
	blackScore += 0.5;
}

void Score::whiteAdd() {
	whiteScore += 1;
}

void Score::blackAdd() {
	blackScore += 1;
}

void Score::printScore() {
	std::cout << "Final Score:" << std::endl;
	std::cout << "White: " << whiteScore << std::endl;
	std::cout << "Black: " << blackScore << std::endl;
}

