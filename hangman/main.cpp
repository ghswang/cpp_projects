//
// main.cpp
//

#include <iostream> //std::cout, std::cin
#include <set> // std::set
#include <cctype> // isalpha(), tolower()
#include <cstdlib> // rand(), srand()
#include <ctime> // time()
#include <sstream> // std::istringstream

#include "Word.h"

using namespace std;

void greeting(const string& guess);
void drawHang(const int& wrongGuesses, const string& guess, const set<char>& guesses);
bool isValidLetter(const string& input);
bool isQuit(const string& input);
void getGuesses(char& letter, const int& wrongGuesses, const string& guess, const set<char>& guesses);
bool isInWord(const char& letter, const string& word, const set<char>& guesses);
bool isWon(const string& word, const string& guess);
void updateGuess(const string& word, const char& letter, string& guess);
void printGuesses(const set<char>& guesses);
void print(const string& word);

void greeting(const string& guess, const set<char>& guesses) {
	cout << "\nWelcome to Hangman!" << endl << endl;
	cout << "   _______" << endl; // TOP part of gallows
	cout << "  |\t  |" << "\tWord: " << guess << "\t\t";
	printGuesses(guesses);
	cout << "   \t  |" << endl; // NO head segment
	cout << "    \t  |" << endl; // NO upper body segment
	cout << "    \t  |" << endl; // NO lower body segment
	cout << "    \t  |" << endl; // BOTTOM part of gallows
	cout << "      *********" << endl << endl;
	cout << "Try to guess the five-letter word before it's too late!" << endl << endl;
}

void drawHang(const int& wrongGuesses, const string& guess, const set<char>& guesses) {
	cout << "   _______" << endl; // TOP part of gallows
	cout << "  |\t  |" << "\tWord: " << guess << "\t\t";
	printGuesses(guesses);

	if (wrongGuesses >= 1) {
		cout << "  O\t  |" << endl; // ENTIRE head segment
	}
	else if (wrongGuesses < 1) {
		cout << "   \t  |" << endl; // NO head segment
	}
	
	if (wrongGuesses == 2) {
		cout << "  | \t  |" << endl; // ONLY torso segment
	}
	else if (wrongGuesses == 3) {
		cout << " /| \t  |" << endl; // BOTH torso AND left arm segment
	}
	else if (wrongGuesses >= 4) {
		cout << " /|\\\t  |" << endl; // ENTIRE upper body segment
	}
	else if (wrongGuesses <= 1) {
		cout << "    \t  |" << endl; // NO upper body segment
	}

	if (wrongGuesses == 5) {
		cout << " /  \t  |" << endl; // ONLY left leg segment
	}
	else if (wrongGuesses >= 6) {
		cout << " / \\\t  |" << endl; // ENTIRE lower body segment
	}
	else if (wrongGuesses < 5) {
		cout << "    \t  |" << endl; // NO lower body segment
	}
	
	cout << "    \t  |" << endl; // BOTTOM part of gallows
	cout << "      *********" << endl << endl;
}

bool isValidLetter(const string& input) {
	unsigned int num_chars = 0;
	bool found_letter = false;
	
	for (auto& ch : input) {
		if (isspace(ch)) { // found whitespace
			continue; // and ignore it
		}
		else if (isalpha(ch)) {
			found_letter = true;
		}
		else {
			cout << "Invalid argument(s) found [i.e. non-alphabetical(s)]" << endl;
			return false;
		}

		num_chars++;
		if (num_chars > 1) {
			cout << "Too many letters were entered" << endl;
			return false;
		}
	}

	if (found_letter && num_chars == 1) { // must find ONLY ONE alphabetical letter 
		return true;
	}

	cout << "No letters were entered" << endl;
	return false;
}

bool isQuit(const string& input) {
	unsigned int num_chars = 0;
	bool found_quit = false;

	for (auto& ch : input) {
		if (isspace(ch)) { // found whitespace
			continue; // and ignore it
		}
		else { 
			if (ch == '0') {
				found_quit = true;
			}

			num_chars++;
			if (num_chars > 1) { // found more than a singular character
				return false;
			}
		}
	}

	if (found_quit && num_chars == 1) {
		return true;
	}

	return false;
}

void getGuesses(char& letter, const int& wrongGuesses, const string& guess, const set<char>& guesses) {
	string input;
	
	do {
		cout << "Please guess a letter (type 0 to quit): ";
		getline(cin, input);

		if (isQuit(input)) {
			exit(0);
		}

		drawHang(wrongGuesses, guess, guesses);
	} while (!isValidLetter(input));

	istringstream iss(input);
	iss >> letter;

	cout << endl; // for formatting reasons
}

bool isInWord(const char& letter, const string& word) {
	return (word.find(letter) != string::npos);
}

bool isWon(const string& word, const string& guess) {
	return (word.compare(guess) == 0);
}

void updateGuess(const string& word, const char& letter, string& guess) {
	for (unsigned int i = 0; i < word.size(); i++) {
		if (word[i] == letter) {
			guess[i] = word[i];
		}
	}
}

void printGuesses(const set<char>& guesses) {
	cout << "Guesses: ";
	
	for (auto i : guesses) {
		cout << i << " ";
	}
	cout << endl;
}

void print(const string& word) {
	for (unsigned int i = 0; i < word.size(); i += 2) {
		cout << word[i];
	}
}

int main() {
	Dictionary d;
	// d.print(); // displays all words in dictionary
	
	srand(time(0)); // will give unique seed based on the time when the program runs
	int random = rand() % 50; // pseudo-randomly chooses from 50 possible unique words

	string word = d.dict[random], guess("_ _ _ _ _");
	set<char> guesses;
	char letter;
	int wrongGuesses = 0, totalGuesses = 0;;
	
	greeting(guess, guesses);

	while (wrongGuesses < 6 && !isWon(word, guess)) {
		getGuesses(letter, wrongGuesses, guess, guesses);
		guesses.insert(tolower(letter));
		if (isInWord(tolower(letter), word)) {
			cout << "The letter '" << static_cast<char>((tolower(letter))) << "' is in the word!" << endl;
			updateGuess(word, tolower(letter), guess);
		}
		else {
			wrongGuesses++;
			cout << "The letter '" << static_cast<char>((tolower(letter))) << "' is NOT in the word!" << endl;
		}
		drawHang(wrongGuesses, guess, guesses);

		totalGuesses++;
	}

	if (wrongGuesses >= 6) {
		cout << "Game over! :(" << endl << endl;
		cout << "In total, you guessed " << totalGuesses << " times." << endl;
		cout << "You guessed " << guesses.size() << " unique letters." << endl;
		cout << "The word was \"";
		print(word);
		cout << "\"." << endl << endl << "Better luck next time!" << endl << endl;
	}
	else if (isWon(word, guess)) {
		cout << "Congratulations, you won! :)" << endl << endl;
		cout << "In total, you guessed " << totalGuesses << " times." << endl;
		cout << "You guessed " << guesses.size() << " unique letters." << endl << endl;
		cout << "The word was \"";
		print(word);
		cout << "\", but you obviously knew that! ;)" << endl << endl;
	}
}