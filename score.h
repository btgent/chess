
class Score {
	float whiteScore;
	float blackScore;
public:
	Score(int ws=0, int bs=0);
	void drawAdd();
	void whiteAdd();
	void blackAdd();
	~Score();
	void printScore();
};



