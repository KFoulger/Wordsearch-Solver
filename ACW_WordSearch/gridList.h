#pragma once
#include <vector>
#include <string>

using namespace std;
using std::vector;
class gridList
{
private:

	struct node {

		node* right = nullptr;
		node* left = nullptr;
		node* down = nullptr;
		node* up = nullptr;
		node* upR = nullptr;
		node* downL = nullptr;
		node* upL = nullptr;
		node* downR = nullptr;

		int x = 0;
		int y = 0;

		char cell = 0;

		node() 
		{
		}
		
		~node()
		{
		}

		node(const node &pNode) : right(pNode.right), left(pNode.left), down(pNode.down), up(pNode.up), upR(pNode.upR), downL(pNode.downL), upL(pNode.upL), downR(pNode.downR)
		{
		}

		node &operator=(const node &pNode) {
			if (this != &pNode) {
				right = pNode.right;
				left = pNode.left;
				down = pNode.down;
				up = pNode.up;
				upR = pNode.upR;
				downL = pNode.downL;
				upL = pNode.upL;
				downR = pNode.downR;
				x = pNode.x;
				y = pNode.y;
				cell = pNode.cell;
			}
			return *this;
		}
	};

	vector<string> dict;
	vector<string> foundW;
	vector<int> startX;
	vector<int> startY;

	using nodePtr = node*;
	nodePtr head;
	nodePtr lineStart;
	nodePtr current;
	nodePtr temporary;



	int dCount = 0;
	int gCount = 0;
	int wordCount = 0;
	int pSize = 0;

	bool breaker = false;
public:
	gridList();
	~gridList();
	gridList(const gridList &pGridList);
	gridList &operator=(const gridList &pGridList);
	void addNode(const char addCell, const int x, const int y, const int size, const bool nextLine);
	const void findWord(vector<string>& dictionary, vector<string>& foundWords, vector<int>& startingX, vector<int>& startingY, const int& size, int& gridCount, int& dictCount);
};

