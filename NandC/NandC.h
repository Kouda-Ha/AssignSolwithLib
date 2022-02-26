#pragma once
#include "std_lib_facilities.h"	// get the facilities for this course

class NandC
{
public:
	NandC();

	bool notFinished();

	void printGame();

	bool setO(int r, int c);

	bool setX(int r, int c);

	char whoWon();

	int numGoes();

	bool setType(char in);

	bool isSinglePlayer();

	void computerX();

private:
	bool m_playing;
	vector<char> m_spaces;
	int m_goes;
	char m_winner;
	vector<vector<int>> m_patterns;
	bool m_single;

};

