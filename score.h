
class Score {
	float whiteScore;
	float blackScore;
public:
	Score(float ws=0, float bs=0);
	void drawAdd();
	void whiteAdd();
	void blackAdd();
	~Score();
	void printScore();
};



