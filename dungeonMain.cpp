#include <iostream>
#include "dungeonHeader.h";

using std::cout;
using std::endl;

int main(void)
{
	cout << "Welcome to the dungeon crawl " << endl;

	DuGame dg;
	char userMove;
	
	while(true)
	{
		cout << dg;

		std::cout << "Choose your direction: (w,a,s,d)";
		std::cin >> userMove;

		dg.displayPlayerStatus();
		dg.prevCoor();
		dg.startPlaying(userMove);
		
		if(dg.updateBoard())
			dg.nextLevel();
		if(dg.checkLives())
			break;
		if(dg.checkLevel())
			break;
	}
	cout << "GAME OVER" << endl;
	system("pause");
	return 0;
}
