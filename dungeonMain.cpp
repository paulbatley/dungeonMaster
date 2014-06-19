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
		dg.startPlaying(userMove);
		if(dg.checkLives() == 1)
			break;
		dg.nextLevel();
		if(dg.checkLevel() == 1)
			break;
	}
	cout << "GAME OVER" << endl;
	system("pause");
	return 0;
}
