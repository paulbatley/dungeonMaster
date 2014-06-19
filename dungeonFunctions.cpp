#include "dungeonHeader.h";

DuGame::DuGame(int numOfPlayers)
{
	playersNum = numOfPlayers;
	level = 1;
	for (int rr = 0;rr < ROWS; rr++)
		for(int cc = 0;cc < COLS; cc++)
			Board[rr][cc] = bempty;

	r1 = 1,	c1 = 1;
	rb1 = 0, cb1 = 7;
	Board[r1][c1] = bplayer;
	Board[rb1][cb1] = bboss;
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

void DuGame::printBoard()
{
	system("cls");
	std::cout << "Look out for hidden traps!! Level: " << level << std::endl << "  ";
	for(int i = 0;i < COLS;i++)
			std::cout<<"  " <<i;
	std::cout<<std::endl<< "  ";
	for(int top = 0;top < COLS;top++)
			std::cout <<" __";
	std::cout<<std::endl;
	for (int rr = 0, i = 0;rr< ROWS; rr++, i++)
	{
		if(i<10)
			std::cout << " "<< i << " ";
		else
			std::cout << i << " ";
		for(int cc = 0;cc < COLS;cc++)
		{
			char c = BoardElementsToChars(Board[rr][cc]);
			std::cout<<"|_" << c;
		}
		std::cout<< "|" << std::endl;
	}
	
	std::cout << "Cash: "<< DuGame::cash << "  Lives: "<< DuGame::lives << std::endl;
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

void DuGame::startPlaying()
{
	char userMove;
	
	while(true)
	{
		//clears previous move
		Board[r1][c1] = bempty;
		Board[rb1][cb1] = bempty;

		

		std::cout << "Choose your direction: (w,a,s,d)";
		std::cin >> userMove;

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
		
		checkOOB();
		updateBoard();

		if(Board[r1][c1] == bexit)
		{
			level++;
			break;
		}
		if(lives == 0)
		{
			std::cout << "I'm sorry. You have died"<< std::endl;
			break;
		}
		
		Board[r1][c1] = bplayer;
		if(level == 4)
			Board[rb1][cb1] = bboss;
		printBoard();
	}
}

void DuGame::checkOOB()
{
	if(r1 > (ROWS-1))
		r1 %= ROWS;
	else if(c1 > (COLS-1))
		c1 %=COLS;
	else if(r1 < 0)
		r1 = (ROWS-1);
	else if(c1 < 0)
		c1 = (COLS-1);
	else if(level == 4)
	{
		if(rb1 > (ROWS-1))
			rb1 = (ROWS-2);
		else if(cb1 > (COLS-2))
			cb1 = (COLS - 1);
		else if(rb1 < 0)
			rb1 = 1;
		else if(cb1 < 0)
			cb1 = 1;
	}
	
}

void DuGame::updateBoard()
{
	if(Board[r1][c1] == bgold)
	{
		std::cout << "You've struck gold!" <<std::endl;
		cash++;
	}
	else if(Board[r1][c1] == btrap)
	{
		std::cout <<"You've hit a trap!!"<<std::endl;
		lives--;
	}
	else if(Board[r1][c1] == bexit)
	{
		std::cout<<"You have found the exit!!"<< std::endl;
		std::cout << "Lives left: " << lives << std::endl;
		std::cout << "Cash scored: " << cash << std::endl << std::endl;
	}
	else if(Board[r1][c1] == bboss)
	{
		std::cout <<"Ouch! the boss tagged you"<< std::endl;
		lives--;
	}
	if(Board[rb1][cb1] == bexit)
	{
		Board[rb1][cb1] = bempty;
		Board[rb1][cb1] = bexit;
		rb1 = 0;
		cb1 = 9;
		std::cout << "The boss left!!"<< std::endl;
	}
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
		Board[rb1][cb1]=bboss;
	else
		Board[ROWS-1][COLS-1] = bexit;

}