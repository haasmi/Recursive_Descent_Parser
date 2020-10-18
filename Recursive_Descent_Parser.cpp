#include <iostream>
#include <fstream>
#include <string>
#include <vector>
constexpr auto EVENT = "event";
constexpr auto IN = "in";
constexpr auto INITIAL = "initial";
constexpr auto STATE = "state";
constexpr auto ON = "on";
constexpr auto GOTO = "goto";
constexpr auto COMMA = ",";
constexpr auto SEMICOLON = ";";
constexpr auto COLON = ":";

bool proof(std::vector<std::string> textl, int iti) {
	if (textl[iti] == EVENT) {
		return false;
	}
	else if (textl[iti] == IN) {
		return false;
	}
	else if (textl[iti] == INITIAL) {
		return false;
	}
	else if (textl[iti] == STATE) {
		return false;
	}
	else if (textl[iti] == ON) {
		return false;
	}
	else if (textl[iti] == GOTO) {
		return false;
	}
	else if (textl[iti] == COLON) {
		return false;
	}
	else if (textl[iti] == SEMICOLON) {
		return false;
	}
	else if (textl[iti] == COMMA) {
		return false;
	}
	else {
		return true;
	}
}

std::vector<std::string> scanner() {
	std::ifstream file;
	file.open("ParseText.txt.txt");
	std::string word;
	std::vector<std::string> text;
	while (file >> word) {
		text.push_back(word);
	}
	return text;
}

int id_list(std::vector<std::string> text, int iteratior) {
	if (proof(text, iteratior) == true && text[iteratior+1] == COLON && proof(text, iteratior + 2) == true){
		id_list(text, iteratior + 2);
	}
	if ((proof(text, iteratior) == true && text[iteratior]==SEMICOLON)) {
		return iteratior+1;
	}
	else {
		return -1;
	}
}

int event_declaration(std::vector<std::string> text, int iterator) {
	if (text[iterator] == EVENT) {
		iterator++;
		iterator=id_list(text, iterator);
		if (iterator > (-1)) {
			if (text[iterator] == SEMICOLON) {
				return iterator + 1;
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int state_lists(std::vector<std::string> text, int iterat) {
	if (text[iterat] == ON) {
		iterat++;
		iterat = id_list(text, iterat);
		if (iterat > -1) {
			if (text[iterat] == GOTO) {
				iterat++;
				if (proof(text, iterat) == true) {
					iterat++;
					if (text[iterat] == COLON) {
						iterat++;
						iterat = id_list(text, iterat);
						if (iterat > -1) {
							if (text[iterat] == SEMICOLON) {
								return iterat + 1;
							}
							else {
								return -1;
							}
						}
						else {
							return -1;
						}
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

bool question2(std::vector<std::string> text, int iterat) {
	if (text[iterat] == INITIAL) {
		return true;
	}
	else {
		return false;
	}
}

int state_transition(std::vector<std::string> text, int iterat) {
	if (text[iterat] == IN) {
		iterat++;
		bool quest = question2(text, iterat);
		if (quest == true) {
			iterat++;
		}
		if (text[iterat] == STATE) {
			iterat++;
			if (proof(text, iterat) == true) {
				iterat++;
				if (text[iterat] == COLON) {
					iterat++;
					iterat = state_lists(text, iterat);
					if (iterat > -1) {
						return iterat;
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

bool question1(std::vector<std::string> text, int iterat) {
	if (text.size() == iterat) {
		return true;
	}
	else {
		return false;
	}
}

int state_machine(std::vector<std::string> text, int iterat) {
	iterat=state_transition(text, iterat);
	bool finish = question1(text, iterat);
	if (finish == true) {
		return iterat;
	}
	else{
		state_machine(text, iterat);
	}
}

int prg(std::vector<std::string> text, int iterator) {
	int new_iterator = event_declaration(text, iterator);
	if (new_iterator > -1) {
		return state_machine(text, new_iterator);
	}
	else {
		return -1;
	}

}

int main() {
	std::vector<std::string> file = scanner();
	int size = file.size();
	int i = 0;
	int rec = prg(file, i);
	if (rec == size) {
		printf("text is part of the grammer\n");
	}
	else {
		printf("FAIL");
	}
	return 0;
}

