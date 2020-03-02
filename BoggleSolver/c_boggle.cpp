#include "pch.h"
#include "c_boggle.h"
#include <algorithm>
#include <iostream>

c_boggle::c_boggle()
{

}

c_boggle::~c_boggle()
{

}

void c_boggle::TrieInsert(char legalWord[], const int len)
{
	
	trieNode *Node = dict;

	for (int i = 0; legalWord[i]; i++)
	{
		legalWord[i] = tolower(legalWord[i]);
		int index = legalWord[i] - 'a';
		if ( !Node->children[index] )
		{
			Node->children[index] = trieConstructor();
		}
		Node->children[index]->parent = Node;

		Node = Node->children[index];
	}
	Node->isEndOfWord = true;
}

void c_boggle::boggleBoardSearch(int** board, int board_width, int board_height)
{
	trieNode* Node = dict;
	int boardSize = board_width * board_height;
	//intialize visited board to entirely false
	for (int visitedI = 0; visitedI < board_height; visitedI++)
	{
		for (int visitedJ = 0; visitedJ < board_width; visitedJ++)
		{
			visited[visitedI][visitedJ] = false;
		}
	}

	for (int boardI = 0; boardI < board_height; boardI++)
	{
		for (int boardJ = 0; boardJ < board_width; boardJ++)
		{
			if ((boardI*boardJ) <= boardSize)
			{
				descend(boardI, boardJ, boardSize, Node, visited);
			}
		}
	}
}

int ** c_boggle::boggleBoardBuilder(int board_width, int board_height, const char * boardLetters)
{
	int boardLetterStepper = 0;
	int** boggleBoard = new int*[board_height];
	for (int i = 0; i < board_height; i++)
	{
		boggleBoard[i] = new int[board_width];
		for (int j = 0; j < board_width; j++)
		{
			int boardLetterToInt = boardLetters[boardLetterStepper] - 'a';
			boggleBoard[i][j] = boardLetterToInt;
			boardLetterStepper++;
		}
	}
	return boggleBoard;
}



void c_boggle::handleOutput(trieNode* dict)
{
	if (dict)
	{
		if(dict->isEndOfWord)
		{
			foundWords.push_back(dict->word);

			for (int i = 0; i < ALPHABET; i++)
			{
				handleOutput(dict->children[i]);
			}
		}
	}
	std::sort(foundWords.begin(), foundWords.end());
}

 inline bool c_boggle::descend(int boardI, int boardJ, int boardSize, trieNode * dict, std::vector<std::vector<bool>> visited)
{
	 dict = searchTrieDict(board[boardI][boardJ], dict);

	if (dict && dict->count)
	{
		visited[boardI][boardJ] = true;

		for (int i = 0; i < NUM_NODE_BRANCHES; i++)
		{
			int childI = boardI + childrenI[i];
			for (int j = 0; j < NUM_NODE_BRANCHES; j++)
			{
				int childJ = boardJ + childrenJ[j];
				if (((childI*childJ) <= boardSize) && !visited[childI][childJ])
				{
					descend(childI, childJ, boardSize, dict, visited);
				}
			}
			
		}
	}
}

void c_boggle::set_legal_words(const std::vector<std::string>& all_words)
{
	char* dictionary;
	std::transform(all_words.begin(), all_words.end(), std::back_inserter(dictionary), [](unsigned char c) -> convert(dictionary));
	dict = trieConstructor();
	char* word = strtok(dictionary, "\n\t");
	while(word != NULL)
	{
		int len = strlen(word);
		if (len >= 3)
		{
			TrieInsert(word, len);
		}
	}
}

char* c_boggle::convert(const std::string &s)
{
	char* pc = new char[s.size() + 1];
	std::strcpy(pc, s.c_str());
	return pc;
}

std::vector<std::string> c_boggle::solve_board(int board_width, int board_height, const char * board_letters)
{
	board = boggleBoardBuilder(board_height, board_width, board_letters);
	boggleBoardSearch(board, board_width, board_height);
	handleOutput(dict);
	return foundWords;
	
}
