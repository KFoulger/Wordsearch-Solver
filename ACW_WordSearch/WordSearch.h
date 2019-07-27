#pragma once
#include"gridList.h"
#include <vector>
#include <string>
using namespace std;
using std::vector;

class WordSearch {
	gridList grid;

	vector<string> dictionary;
	vector<string> foundWords;

	vector<int> startingX;
	vector<int> startingY;

	char puzzleGridSimple[9][9];
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	const char* outputFile;


	int currentWord = 0;
	int dictCount = 0;
	int gridCount = 0;
	int size = 0;
	int character = 0;
	int length = 0;

	// Add your code here

public:
	explicit WordSearch(const char * const filename);
	~WordSearch();
	WordSearch(const WordSearch &pWordSearch);
	WordSearch &operator=(const WordSearch &pWordSearch);
	void ReadSimplePuzzle();
	void ReadSimpleDictionary();
    void ReadAdvancedPuzzle();
	void ReadAdvancedDictionary();
	void SolvePuzzleSimple();
	const void SolvePuzzleAdvanced();
	void WriteResults(const	double loadTime, const double solveTime) const;

	// Add your code here
};

inline const void WordSearch::SolvePuzzleAdvanced() {
	currentWord = 0;
	grid.findWord(dictionary, foundWords, startingX, startingY, size, gridCount, dictCount);
	// Add your code here
}

