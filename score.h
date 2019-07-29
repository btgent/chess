#pragma once
class Score {
	float whiteScore;
	float blackScore;
public:
	Score(int ws=0, int bs=0);
	~Score();
	void printScore();
};



