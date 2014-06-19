#ifndef _DUNGEONHEADER_H_
#define _DUNGEONHEADER_H_

#include <iostream>

const int ROWS = 10;
const int COLS = 10;

enum BoardElements {bempty, bplayer, btrap , bgold, bboss , bexit };

class DuGame
{
	private:
		BoardElements Board[ROWS][COLS];
		int playersNum;
		int r1,c1;
		int cash;
		int rb1,cb1;
		int level;
		int lives;
		char BoardElementsToChars(BoardElements b) const;
	public:
		DuGame(int numOfPlayers = 1);
		void printBoard();
		void checkOOB();
		void updateBoard();
		void startPlaying();
		void nextLevel();
		void levels(int levelSelected);
		void resetBoard();
		int checkLives()
		{
			if(lives == 0)
				return 1;
			else
				return 0;
		}
		int checkLevel()
		{
			if(level == 5)
				return 1;
			else
				return 0;
		}
};

#endif
