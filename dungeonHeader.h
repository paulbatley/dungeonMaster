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
		BoardElements PrevObj;
		int playersNum;
		int r1,c1;
		int cash;
		int rb1,cb1;
		int rp1, cp1;
		int level;
		int lives;
		char BoardElementsToChars(BoardElements b) const;
	public:
		DuGame(int numOfPlayers = 1);
		void checkOOB();
		int updateBoard();
		void startPlaying(char userMove);
		void nextLevel();
		void levels(int levelSelected);
		void resetBoard();
		friend std::ostream & operator<<(std::ostream & os, const DuGame d);
		int checkLives();
		int checkForExit();
		int checkLevel();
		void displayPlayerStatus() const;
		void prevCoor();
};

#endif
