#include "dungeonHeader.h";

DuGame::DuGame(int numOfPlayers)
{
	playersNum = numOfPlayers;
	level = 1;
	for (int rr = 0;rr < ROWS; rr++)
		for(int cc = 0;cc < COLS; cc++)
			Board[rr][cc] = bempty;

	rp1 = r1 = 1,	cp1 = c1 = 1;
	PrevObj = bempty;
	Board[r1][c1] = bplayer;

	cash = 0;
	lives = 5;

	Board[2][4] = btrap;
	Board[0][8] = btrap;
	Board[1][8] = btrap;
	Board[1][9] = btrap;
	Board[4][9] = btrap;
	Board[5][8] = btrap;
	Board[6][8] = btrap;
	Board[7][8] = btrap;

	Board[0][(COLS-1)] = bgold;
	Board[(ROWS/2)+2][(COLS/2)-2] = bgold;
	Board[ROWS/2][COLS-1] = bgold;
	Board[(ROWS/2)+1][COLS-1] = bgold;
	Board[(ROWS/2)+2][COLS-1] = bgold;

	Board[ROWS-1][COLS-1] = bexit;
}

char DuGame::BoardElementsToChars(BoardElements b) const
{
	char c;
	switch(b)
	{
		case bempty:
			c = '.';
			break;
		case bplayer:
			c = 'P';
			break;
		case btrap:
			c = '.';
			break;
		case bgold:
			c = 'G';
			break;
		case bexit:
			c = 'X';
			break;
		case bboss:
			c = 'B';
			break;
		default:
			c = '?';
	}
	return c;
}

void DuGame::startPlaying(char userMove)
{
	switch(userMove)
	{
		case 'w':
			r1--;
			break;
		case 'a':
			c1--;
			break;
		case 's':
			r1++;
			break;
		case 'd':
			c1++;
			break;
		default:
			std::cout << "Enter the correct input" << std::endl;
	}
	if(level == 4)
	{		
		Board[rb1][cb1] = bempty;
		switch(userMove)
		{
			case 'w':
				rb1++;
				break;
			case 'a':
				cb1+=2;
				break;
			case 's':
				rb1-=3;
				break;
			case 'd':
				cb1--;
				break;
			default:
				std::cout << "Enter the correct input" << std::endl;
		}
	}
}
  
void DuGame::checkOOB()
{
	if(r1 > (ROWS-1))
		r1 %=ROWS;
	else if(c1 > (COLS-1))
		c1 %=COLS;
	else if(r1 < 0)
		r1 = (ROWS-1);
	else if(c1 < 0)
		c1 = (COLS-1);
	else if(level == 4)
	{
		if(rb1 > (ROWS-1))
			rb1 = (ROWS-1);
		else if(cb1 > (COLS-1))
			cb1 = (COLS - 1);
		else if(rb1 < 0)
			rb1 = 0;
		else if(cb1 < 0)
			cb1 = 0;
	}
}

int DuGame::updateBoard()
{
	if(Board[r1][c1] == bgold)
	{
		PrevObj = bgold;
		cash++;
	}
	else if(Board[r1][c1] == btrap)
	{
		PrevObj = btrap;
		lives--;
	}
	else if(Board[r1][c1] == bboss)
	{
		PrevObj = bboss;
		lives--;
	}
	else
		PrevObj = bempty;
	if(level == 4)
	{
		if(Board[rb1][cb1] == bexit)
		{
			Board[rb1][cb1] = bempty;
			Board[rb1][cb1] = bexit;
			rb1 = 0;
			cb1 = 9;	
		}
	}
	checkOOB();
	if(Board[r1][c1] == bexit)
	{
		PrevObj = bexit;
		level++;
		return 1;
	}
	Board[rp1][cp1] = bempty;
	Board[r1][c1] = bplayer;
	if(level == 4)
		Board[rb1][cb1] = bboss;

	return 0;
}

void DuGame::nextLevel()
{
	if(level == 2)
		levels(level);
	else if(level == 3)
		levels(level);
	else if(level == 4)
		levels(level);
}

void DuGame::levels(int levelSelected)
{
	if(levelSelected == 2)
	{
		resetBoard();
		Board[1][0] = bgold;
		Board[5][7] = bgold;
		Board[9][0] = bgold;
		Board[9][1] = bgold;
		Board[3][4] = bgold;
		Board[3][5] = bgold;

		Board[5][6] = btrap;
		Board[4][7] = btrap;
		Board[6][7] = btrap;
		Board[5][8] = btrap;
		Board[8][0] = btrap;
		Board[8][1] = btrap;
		Board[9][2] = btrap;
	}
	else if(levelSelected == 3)
	{
		resetBoard();
		Board[5][5] = bgold;
		Board[5][7] = bgold;
		Board[5][6] = bgold;
		Board[6][5] = bgold;
		Board[6][6] = bgold;
		Board[6][7] = bgold;

		Board[5][4] = btrap;
		Board[4][7] = btrap;
		Board[6][4] = btrap;
		Board[4][6] = btrap;
		Board[4][5] = btrap;
		Board[6][8] = btrap;
		Board[5][8] = btrap;
		Board[4][6] = btrap;
		Board[4][7] = btrap;
	}
	else if(levelSelected == 4)
	{
		resetBoard();
		int randRow = rand()%ROWS;
		int randCol = rand()%COLS;
		Board[randRow-1][randCol-1] = bexit;
	}
}

void DuGame::resetBoard()
{
	for (int rr = 0;rr < ROWS; rr++)
		for(int cc = 0;cc < COLS; cc++)
			Board[rr][cc] = bempty;
	r1 = 1;
	c1 = 1;
	Board[r1][c1]=bplayer;
	if(level == 4)
	{
		rb1 = 1;
		cb1 = 8;
		Board[rb1][cb1]=bboss;
	}
	else
		Board[ROWS-1][COLS-1] = bexit;

}

std::ostream & operator<<(std::ostream & os, const DuGame d)
{
	system("cls");
	std::cout << "Look out for hidden traps!! Level: " << d.level << std::endl << "  ";
	for(int i = 0;i < COLS;i++)
			std::cout<<"  " << i;
	std::cout<<std::endl<< "   ";
	for(int top = 0;top < (COLS -3);top++)
			std::cout <<"______";
	std::cout<<std::endl;
	for (int rr = 0, i = 0;rr< ROWS; rr++, i++)
	{
		if(i<10)
			std::cout << " "<< i << " ";
		else
			std::cout << i << " ";
		for(int cc = 0;cc < COLS;cc++)
		{
			char c = d.BoardElementsToChars(d.Board[rr][cc]);
			std::cout<<"|_" << c << "_";
		}
		std::cout<< "|" << std::endl;
	}
	
	std::cout << "Cash: "<< d.cash << "  Lives: "<< d.lives << std::endl;
	d.displayPlayerStatus();
	return os;
}

int DuGame::checkLives()
{
	if(lives == 0)
	{
		std::cout << "YOU SUCK!"<<std::endl;
		return 1;
	}
	else
		return 0;
}

int DuGame::checkLevel()
{
	if(level == 5)
		return 1;
	else
		return 0;
}

int DuGame::checkForExit()
{
	if(Board[r1][c1] ==  bexit)
		return 1;
	else 
		return 0;
}

void DuGame::displayPlayerStatus() const
{
	if(PrevObj == btrap)
		std::cout << "You've hit a trap!!" << std::endl;
	else if(PrevObj == bgold)
		std::cout << "You've struck Gold!!" << std::endl;
	else if(PrevObj == bexit)
		std::cout << "You've found the exit" << std::endl;
	else if(PrevObj == bboss)
		std::cout << "The boss tagged you" << std::endl;
}

void DuGame::prevCoor()
{
	rp1 = r1;
	cp1 = c1;
}
