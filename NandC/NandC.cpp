#include "stdafx.h"
#include "NandC.h"


// You're in the wrong place, I did demonstration questions 3 (articulated motion) and 4 (dodging game), please see
// OpenGL_1 and OpenGL_3 for my solutions to the coursework, thank you :)


NandC::NandC()
{
	m_playing = true;
	m_goes = 0;
	m_spaces = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	m_winner = ' ';
	m_patterns = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	m_single = false;
	srand((int)time(nullptr));
	rand();
}

void NandC::computerX()
{
	bool check;
	do {
		int r = (int)(2.0f * ((float)rand()) / RAND_MAX) + 1;
		int c = (int)(2.0f * ((float)rand()) / RAND_MAX) + 1;
		check = setX(r, c);
	} while (!check);

}

bool NandC::setType(char in)
{
	if (in == 's')
	{
		m_single = true;
		return true;
	}
	if (in == 't')
	{
		m_single = false;
		return true;
	}
	return false;
}

bool NandC::isSinglePlayer()
{
	return m_single;
}

bool NandC::notFinished()
{

	//1. No point in doing anything unless at least 3 'X' or 'O' are drawn...
	int n_x = 0;
	int n_o = 0;
	for (int i = 0; i < (int)m_spaces.size(); i++)
	{
		if (m_spaces[i] == 'X')  n_x++;
		if (m_spaces[i] == 'O')  n_o++;
	}
	if (n_x < 3 && n_o < 3)
		m_playing = true;

	//2. But if there are no space left to fill....
	if (n_x + n_o == 9)
		m_playing = false;

	//3. OK, so perhaps 'X' has won?
	if (n_x >= 3 && m_playing)
	{
		for (int i = 0; i < (int)m_patterns.size(); i++)
		{
			m_playing = false;
			vector<int> pattern = m_patterns[i];
			for (int j = 0; j < (int)pattern.size(); j++)
				if (m_spaces[pattern[j]] != 'X') m_playing = true;
			if (!m_playing) { m_winner = 'X'; break; }

		}

	}
	// 4. In that case, what about 'O'?
	if (n_o >= 3 && m_playing)
	{
		for (int i = 0; i < (int)m_patterns.size(); i++)
		{
			m_playing = false;
			vector<int> pattern = m_patterns[i];
			for (int j = 0; j < (int)pattern.size(); j++)
				if (m_spaces[pattern[j]] != 'O') m_playing = true;
			if (!m_playing) { m_winner = 'O'; break; }

		}

	}
	return m_playing;
}



void NandC::printGame()
{
	int k = 0;
	for (int i = 1; i <= 3; i++)
	{
		cout << "  ";
		for (int j = 1; j <= 3; j++)
		{
			cout << m_spaces[k];
			if (j < 3) cout << '|';
			k++;
		}
		cout << endl;
		if (i < 3) cout << "  -----" << endl;
	}
	cout << endl;
}

bool NandC::setO(int r, int c)
{
	if (m_spaces[3 * (r - 1) + c - 1] == ' ')
	{
		m_spaces[3 * (r - 1) + c - 1] = 'O';
		m_goes++;
		return true;
	}
	return false;

}

bool NandC::setX(int r, int c)
{
	if (m_spaces[3 * (r - 1) + c - 1] == ' ')
	{
		m_spaces[3 * (r - 1) + c - 1] = 'X';
		m_goes++;
		return true;
	}
	return false;

}

char NandC::whoWon()
{
	return m_winner;
}

int NandC::numGoes()
{
	return m_goes;
}
