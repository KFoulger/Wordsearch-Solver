#include "WordSearch.h"
#include "gridList.h"

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <locale>
using namespace std;
using std::vector;


WordSearch::WordSearch(const char * const filename) : grid(), puzzleGridSimple(), outputFile(filename), currentWord(0), dictCount(0), gridCount(0), size(0) {
	
}

WordSearch::~WordSearch() {
	
}

WordSearch::WordSearch(const WordSearch & pWordSearch) : grid(), puzzleGridSimple(), outputFile(pWordSearch.outputFile), currentWord(pWordSearch.currentWord), dictCount(pWordSearch.dictCount), gridCount(pWordSearch.gridCount), size(pWordSearch.size)
{
}

WordSearch & WordSearch::operator=(const WordSearch & pWordSearch)
{
	
	if (this != &pWordSearch) {
		grid = pWordSearch.grid;
		puzzleName = pWordSearch.puzzleName;
		dictionaryName = pWordSearch.dictionaryName;
		outputFile = pWordSearch.outputFile;
		currentWord = pWordSearch.currentWord;
		dictCount = pWordSearch.dictCount;
		dictionary = pWordSearch.dictionary;
		foundWords = pWordSearch.foundWords;
		gridCount = pWordSearch.gridCount;
		puzzleGridSimple[9][9] = pWordSearch.puzzleGridSimple[9][9];
		startingX = pWordSearch.startingX;
		startingY = pWordSearch.startingY;
		size = pWordSearch.size;
		character = pWordSearch.character;
		length = pWordSearch.length;
	}
	return *this;
}


void WordSearch::ReadSimplePuzzle() {
	char c;
	ifstream fin(puzzleName);
	fin.get(c);
	fin.get(c);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fin >> puzzleGridSimple[i][j];
		}
	}
}

void WordSearch::ReadSimpleDictionary() {
	ifstream fin(dictionaryName);
	string word;
	while (fin >> word) {
		dictionary.push_back(word);
	}
}

void WordSearch::ReadAdvancedPuzzle() {
	string s;
	char c;
	ifstream fin(puzzleName);
	fin >> s;
	size = stoi(s);
	bool nextLine = false;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fin >> c;
			grid.addNode(c, j, i, size, nextLine);
			nextLine = false;
		}
		nextLine = true;
	}
}

void WordSearch::ReadAdvancedDictionary() {
	ifstream fin(dictionaryName);
	string word;
	while (fin >> word) {
		dictionary.push_back(word);
	}
}

void WordSearch::SolvePuzzleSimple() {
	char currentCharacter;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gridCount++;
			currentCharacter = puzzleGridSimple[i][j];
			currentWord = 0;
			for each (string word in dictionary)
			{
				if (word != "") {
					dictCount++;
					bool found = true;
					if (word[0] == currentCharacter && word != "") {
						character = 1;
						length = word.length();
						while (found && character < length) {
							gridCount++;
							if (word[character] == puzzleGridSimple[i][j - character]) {
								character++;
							}
							else {
								found = false;
							}
						}
						if (character == length) {
							found = true;
						}


						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i][j + character]) {
									character++;
								}
								else {
									found = false;
								}

							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i + character][j]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i - character][j]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i - character][j + character]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i - character][j - character]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i + character][j + character]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == false) {
							character = 1;
							length = word.length();
							found = true;
							while (found && character < length) {
								gridCount++;
								if (word[character] == puzzleGridSimple[i + character][j - character]) {
									character++;
								}
								else {
									found = false;
								}
							}
							if (character == length) {
								found = true;
							}
						}

						if (found == true) {
							foundWords.push_back(word);
							dictionary[currentWord].erase();
							startingX.push_back(j);
							startingY.push_back(i);
						}
					}
				}
			currentWord++;
			}
		}
	}
}

void WordSearch::WriteResults(const double loadTime, const double solveTime) const {
	ofstream fout(outputFile);
	fout << "NUMBER_OF_WORDS_MATCHED " << foundWords.size() << endl << endl;
	fout << "WORDS_MATCHED_IN_GRID" << endl;
	for (int i = 0; i < foundWords.size(); i++) {
		fout << startingX[i] << " " << startingY[i] << " " << foundWords[i] << endl;
	}
	fout << endl << "WORDS_UNMATCHED_IN_GRID" << endl;
	for each(string word in dictionary) {
		if (word != "") {
			fout << word << endl;
		}
	}
	fout << endl << "NUMBER_OF_GRID_CELLS_VISITED " << gridCount << endl << endl;
	fout << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << dictCount << endl << endl;
	fout << "TIME_TO_POPULATE_GRID_STRUCTURE " << loadTime << endl << endl;
	fout << "TIME_TO_SOLVE_PUZZLE " << solveTime << endl;
}

