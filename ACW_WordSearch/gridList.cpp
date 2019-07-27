#include "gridList.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using std::vector;

gridList::gridList() : head(nullptr), lineStart(nullptr), current(nullptr), temporary(nullptr) {

}

gridList::~gridList()
{
}

gridList::gridList(const gridList & pGridList) : head(pGridList.head), lineStart(pGridList.lineStart), current(pGridList.current), temporary(pGridList.temporary)
{
}

gridList & gridList::operator=(const gridList & pGridList)
{
	if (this != &pGridList) {
		dict = pGridList.dict;
		foundW = pGridList.foundW;
		startX = pGridList.startX;
		startY = pGridList.startY;
		head = pGridList.head;
		lineStart = pGridList.lineStart;
		current = pGridList.current;
		temporary = pGridList.temporary;
		dCount = pGridList.dCount;
		gCount = pGridList.gCount;
		wordCount = pGridList.wordCount;
		breaker = pGridList.breaker;
		pSize = pGridList.pSize;
	}
	return *this;
	// TODO: insert return statement here
}

void gridList::addNode(const char addCell, const int x, const int y, const int size, const bool nextLine) {
	const nodePtr n = new node;
	n->right = nullptr;
	n->left = nullptr;
	n->down = nullptr;
	n->up = nullptr;
	n->upR = nullptr;
	n->downL = nullptr;
	n->upL = nullptr;
	n->downR = nullptr;
	n->cell = addCell;
	n->x = x;
	n->y = y;
	if (nextLine) {
		current = head;
		while (current->down != nullptr) {
			current = current->down;
		}
		temporary = current;
		current->down = n;
		current = current->down;
		current->up = temporary;
		lineStart = current;
		current->upR = temporary->right;
		temporary = temporary->right;
		temporary->downL = current;
	}
	else if (head != nullptr) {
		current = lineStart;
		while (current->right != nullptr) {
			current = current->right;
		}
		if (current->x != size - 1 && y != 0) {
			temporary = lineStart->up;
			while (temporary->x != (current->x + 1)) {
				temporary = temporary->right;
			}
			current->upR = temporary;
			temporary->downL = current;
		}
		if (current->x > 0 && y != 0) {
			temporary = lineStart->up;
			while (temporary->x != (current->x - 1)) {
				temporary = temporary->right;
			}
			current->upL = temporary;
			temporary->downR = current;
		}
		if (y != 0) {
			temporary = lineStart->up;
			while (temporary->x != current->x) {
				temporary = temporary->right;
			}
			current->up = temporary;
			temporary->down = current;
		}
		temporary = current;
		current->right = n;
		current = current->right;
		current->left = temporary;
		if (n->x == (size - 1)) {
			if (n->y > 0) {
			temporary = lineStart->up;
			while (true) {
				if (temporary->x == (x - 1)) {
					n->upL = temporary;
					temporary->downR = n;
				}
				if (temporary->x == x) {
					n->up = temporary;
					temporary->down = n;
					break;
				}
                temporary = temporary->right;
			}
				
			}
		}
	}
	else {
		head = n;
		lineStart = n;
	}
}

const void gridList::findWord(vector<string>& dictionary, vector<string>& foundWords, vector<int>& startingX, vector<int>& startingY, const int& size, int& gridCount, int& dictCount) {
	dict = dictionary;
	foundW = foundWords;
	startX = startingX;
	startY = startingY;
	pSize = size;
	dCount = dictCount;
	gCount = gridCount;
	breaker = false;
	for each(string word in dict) {
		current = head;
		lineStart = current;
		while (true) {
			gCount++;
			dCount++;
			if (word[0] == current->cell) {
				int i = 0;
				int x = current->x;
				int y = current->y;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->left;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->down;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->up;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->right;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->upL;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->upR;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->downL;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				i = 0;
				temporary = current;
				while (temporary != nullptr && word[i] == temporary->cell) {
					temporary = temporary->downR;
					gCount++;
					i++;
					if (i == word.length()) {
						foundW.push_back(word);
						startX.push_back(x);
						startY.push_back(y);
						dict[wordCount].erase();
						breaker = true;
						break;
					}
				}
				if (breaker) {
					breaker = false;
					break;
				}
				if (current->x != (pSize - 1)) {
					current = current->right;
				}
				else if (current->x == (pSize - 1)) {
					if (current->y == (pSize - 1)) {
						break;
					}
					else {
						current = lineStart->down;
						lineStart = current;
					}
				}

			}
			else if (current->x != (pSize - 1)) {
				current = current->right;
			}
			else if (current->x == (pSize - 1)) {
				if (current->y == (pSize - 1)) {
					break;
				}
				else {
					current = lineStart->down;
					lineStart = current;
				}
			}
		}
		wordCount++;
	}
	dictionary = dict;
	foundWords = foundW;
	startingX = startX;
	startingY = startY;
	dictCount = dCount;
	gridCount = gCount;
}