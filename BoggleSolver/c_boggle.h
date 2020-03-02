#pragma once
#include <vector>
#include <string>

class c_boggle
{

public:
	//default constructor
	c_boggle();
	//default destructor
	~c_boggle();

	void set_legal_words(const std::vector < std::string > &all_words);

	std::vector<std::string> solve_board(int board_width, int board_height, const char *board_letters);

	

private:
	//constants
	const static int ALPHABET = 26;
	const static int NUM_NODE_BRANCHES = 8;

	//structs for trie
	struct trieNode
	{
		trieNode *children[ALPHABET];
		trieNode *parent;
		int count;
		char* word;
		bool isEndOfWord;
	};

	//trie "constructor"
	trieNode* trieConstructor()
	{
		trieNode* newTrieNode;
		newTrieNode->count = 0;
		newTrieNode->word = NULL;
		newTrieNode->isEndOfWord = false;
		for (int i = 0; i < ALPHABET; i++)
		{
			newTrieNode->children[i];
		}
		return newTrieNode;
	}

	trieNode* searchTrieDict(const int index, trieNode * dict)
	{
		dict = dict->children[index];

		if (dict && dict->word)
		{
			if(!dict->isEndOfWord)
			{
				dict->isEndOfWord = true;
				dict->parent->count--;
			}
		}
		return dict;
	}

	//variables
	std::vector<std::string> finalWords;
	std::vector<std::string> sortedDictionary;
	std::vector<std::vector<bool>> visited;
	std::vector<std::string> foundWords;
	trieNode *dict;
	int ** board;
	int * childrenI = new int[NUM_NODE_BRANCHES] {0,1,1,1,0,-1,-1,-1};
	int * childrenJ = new int[NUM_NODE_BRANCHES] {1,1,0,-1,-1,-1,0,1};
	

	//functions to build trie
	void TrieInsert(char legalWord[], int len);
	void boggleBoardSearch(int** board, int board_width, int board_height);
	char * convert(const std::string & s);


	//functions for boggle
	int** boggleBoardBuilder(int board_width, int board_height, const char* boardLetters);
	void sortAlphabetically(std::vector<std::string> createdWords);
	void handleOutput(trieNode* dict);
	bool descend(int boardI, int boardJ, int boardSize, trieNode* dict, std::vector<std::vector<bool>> visited);
};