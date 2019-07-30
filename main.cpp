#include <iostream>
#include <string>
#include <score.h>
#include <board.h>

using namespace std;

int main() {
	string s;
	while (cin >> s) {
		if (s == "game") {
			Score *scoreb = new Score(); //create a scoreBoard with white:0, Black:0
			string p1, p2;
			if (cin >> p1) { //player1 setup
				if (p1 == "human") {

				}
				else if (p1 == "computer1") {
					Computer1(Colour::White);
				}
				else if (p1 == "computer2") {
					Computer2(Colour::White);
				}
				else if (p1 == "computer3") {
					Computer3(Colour::White);
				}
				else { //invalid input for player

				}
			}
			if (cin >> p2) {   //player2 setup
				if (p1 == "human") {

				}
				else if (p1 == "computer1") {
					Computer1(Colour::Black);
				}
				else if (p1 == "computer2") {
					Computer2(Colour::Black);
				}
				else if (p1 == "computer3") {
					Computer3(Colour::Black);
				}
				else { //invalid input for player

				}
			}
		}
		else if (s == "resign") {
			scoreb->drawAdd();
			//clear the board
		}
		else if (s == "move") {
			
			myb->move();
		}
		else if (s == "setup") {
			Board * myb; //create an empty board
			string op;
			while (cin >> op) {
				if (op == "+") {  //place piece case

				}
				else if (op == "-") { //remove piece case

				}
				else if (op == "=") { //turn colour case

				}
				else if (op == "done") {
					break;
				}
			}
			//check king and pawn
		}
	}
	scoreb->printScore();
	delete scoreb;
}