#include <iostream>
#include <sstream>
#include <memory>
#include "graphicdisplay.h"
#include "board.h"
#include "piece.h"
#include "textdisplay.h"
#include "score.h"

using namespace std;

void char_to_type(char c, Type &type, Colour &colour) {
	switch (c) {
	case 'P':
		type = Type::Pawn;
		colour = Colour::White;
		break;
	case 'N':
		type = Type::Knight;
		colour = Colour::White;
		break;
	case 'B':
		type = Type::Bishop;
		colour = Colour::White;
		break;
	case 'R':
		type = Type::Rook;
		colour = Colour::White;
		break;
	case 'Q':
		type = Type::Queen;
		colour = Colour::White;
		break;
	case 'K':
		type = Type::King;
		colour = Colour::White;
		break;
	case 'p':
		type = Type::Pawn;
		colour = Colour::Black;
		break;
	case 'n':
		type = Type::Knight;
		colour = Colour::Black;
		break;
	case 'b':
		type = Type::Bishop;
		colour = Colour::Black;
		break;
	case 'r':
		type = Type::Rook;
		colour = Colour::Black;
		break;
	case 'q':
		type = Type::Queen;
		colour = Colour::Black;
		break;
	case 'k':
		type = Type::King;
		colour = Colour::Black;
		break;
	default:
		throw "invalid input";
	}
}

int main() {
	unique_ptr<Board> bp;
	unique_ptr<TextDisplay> td;
	unique_ptr<GraphicDisplay> gd;
	Score scoreboard;
	string str;
	bool gameInPlay = false;
	Type type;
	Colour colour;
	while (getline(cin, str)) {
		stringstream ss{ str };
		if (!(ss >> str)) continue;
		if (str == "game") {
			if (gameInPlay) continue;
			bp.reset(nullptr);
			gd.reset(nullptr);
			td.reset(nullptr);
			continue;  // put Computer options here
		}
		else if (str == "setup") {
			if (gameInPlay) continue;
			int size;
			if (ss >> size) {
				bp = make_unique<Board>(true, size);
				td = make_unique<TextDisplay>(size);
				gd = make_unique<GraphicDisplay>();
				td->drawBoard(*bp);
				gd->drawBoard(*bp);
				continue;
			}
			ss.clear();
			if (ss >> str) {
				if (str == "default") {
					bp = make_unique<Board>();
					td = make_unique<TextDisplay>(8);
					gd = make_unique<GraphicDisplay>();
					td->drawBoard(*bp);
					gd->drawBoard(*bp);
					gameInPlay = true;
					continue;
				}
			}
			bp = make_unique<Board>(true);
			td = make_unique<TextDisplay>(8);
			gd = make_unique<GraphicDisplay>();
			td->drawBoard(*bp);
			gd->drawBoard(*bp);
			continue;
		} //setup
		if (bp.get() == nullptr) {
      cerr << "no game in play right now" << endl;
      continue;
    }
		if (str == "+") {
			char p, c; int i;
			if (!(ss >> p >> c >> i)) continue;
			try {
				char_to_type(p, type, colour);
				Coord coord{ i - 1, c - 'a' };
				bp->place(coord, colour, type);
				td->drawBoard(*bp);
				gd->drawBoard(*bp);
				cin >> c;
			}
			catch (const string &s) {
				cerr << s << endl;
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			cin >> c;
			continue;
		} // +
		else if (str == "-") {
			char c; int i;
			if (!(ss >> c >> i)) continue;
			try {
				Coord coord{ i - 1, c - 'a' };
				bp->remove(coord);
				td->drawBoard(*bp);
				gd->drawBoard(*bp);
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			continue;
		} // -
		else if (str == "=") {
			if (!(ss >> str)) continue;
			try {
				if (str == "white") {
					bp->changeStartTurn(Colour::White);
				}
				else if (str == "black") {
					bp->changeStartTurn(Colour::Black);
				}
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			continue;
		} // =
		else if (str == "done") {
			try {
				bp->exitSetup();
				gameInPlay = true;
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
      continue;
		} // done
		else if (str == "move") {
			char c1, c2, p;
			int i1, i2;
			if (!(ss >> c1 >> i1 >> c2 >> i2)) continue;
			if (ss >> p) {
				try {
					bp->move(i1 - 1, c1 - 'a', i2 - 1, c2 - 'a', Type::Queen);
				}
				catch (const runtime_error &r) {
					cerr << r.what() << endl;
				}
			}
			else {
				try {
					bp->move(i1 - 1, c1 - 'a', i2 - 1, c2 - 'a');
				}
				catch (const runtime_error &r) {
					cerr << r.what() << endl;
				}
			}
			td->drawBoard(*bp);
			gd->drawBoard(*bp);
			try {
				if (bp->checkmate(bp->getTurn())) {
					switch (bp->getTurn()) {
					case Colour::White:
						scoreboard.blackAdd();
            cout << "Black wins this round" << endl;
            break;
					case Colour::Black:
						scoreboard.whiteAdd();
            cout << "White wins this round" << endl;
					}
					gameInPlay = false;
					bp.reset(nullptr);
				}
				else if (bp->stalemate(bp->getTurn())) {
					gameInPlay = false;
					scoreboard.drawAdd();
					bp.reset(nullptr);
				}
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			continue;
		}  //move
		else if (str == "undo") {
			try {
				bp->undo();
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			td->drawBoard(*bp);
			gd->drawBoard(*bp);
			continue;
		}  //move
		else if (str == "resign") {
			if (!gameInPlay) {
				cerr << "game hasn't even started yet!";
        continue;
			}
			try {
				switch (bp->getTurn()) {
					case Colour::White:
						scoreboard.blackAdd();
            cout << "Black wins this round" << endl;
						break;
					case Colour::Black:
						scoreboard.whiteAdd();
            cout << "White wins this round" << endl;
						break;
				}
			}
			catch (const runtime_error &r) {
				cerr << r.what() << endl;
			}
			bp.reset(nullptr);
			gameInPlay = false;
			continue;
		}
	} //while loop
	scoreboard.printScore();
}
