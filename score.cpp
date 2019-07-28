#include "score.h"
#include "iostream"


Score::Score(int ws, int bs) :whiteScore{ ws }, blackScore{ bs } {}

Score::~Score() {}

void Score::printScore() {
	std::cout << "Final Score:" << std::endl;
	std::cout << "White: " << whiteScore << std::endl;
	std::cout << "Black: " << blackScore << std::endl;
}

