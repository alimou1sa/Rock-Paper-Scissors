#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
enum engamechoice {stone=1,paper=2, scisser=3};
enum enwinner{player=1,computer=2,draw=3};

struct stroundinfo
{
	short randnumber = 0;
	engamechoice player1choise;
	engamechoice computerchoice;
	enwinner winner;
	string winnername;
};
struct stgameresults
{
	short gameround = 0;
	short playerwintimes = 0;
	short  computer2wintimes = 0;
	short drawtimes = 0;
	enwinner gamewinner;
	string winnername = "";
};

int randomnumber(int from,int to)
{
	int randnum = rand() % (to - from + 1) + from;
	return randnum;
}

string winnername(enwinner winner)
{
	string arrwinnername[3] = { "player1","computer","no wonner" };
	return arrwinnername[winner - 1];
}

enwinner whowontheround(stroundinfo roundinfo)
{
	if (roundinfo.player1choise == roundinfo.computerchoice)
	{
		return enwinner::draw;
	}
	switch (roundinfo.player1choise)
	{
	case engamechoice::stone:
		if (roundinfo.computerchoice == engamechoice::paper)
		{
			return enwinner::computer;
		}
		break;
	case engamechoice::paper:
		if (roundinfo.computerchoice == engamechoice::scisser)
		{
			return enwinner::computer;
		}
		break;
	case engamechoice::scisser:
		if (roundinfo.computerchoice == engamechoice::stone)
		{
			return enwinner::computer;
		}
		break;

	
	}

   return enwinner::player;
}

string choicename(engamechoice choice)
{
	string arrgamechoice[3] = { "stone","paper","scisser" };
	return arrgamechoice[choice - 1];
}

void setwinnerscreencolor(enwinner winner)
{
	switch (winner)
	{
	case player:
		system("color 3f");
		break;
	case computer:
		system("color 5f");
		cout << "\a";
		break;
	case draw:
		system("color 7f");
		break;
	}
}

void printroundresults(stroundinfo roundinfo)
{
	cout << "\n___________Round [" << roundinfo.randnumber << "]___________\n\n";
	cout << "Player1 choice: " << choicename(roundinfo.player1choise) << endl;
	cout << "Computer choice : " << choicename(roundinfo.computerchoice) << endl;
	cout << "Round winner  : [" << roundinfo.winnername << "]\n";
	cout << "_______________________________\n" << endl;
	setwinnerscreencolor(roundinfo.winner);
}

enwinner whowonthegame(short player1wintimes, short computerwintimes)
{
	if (player1wintimes > computerwintimes)
		return enwinner::player;
	else if (computerwintimes > player1wintimes)
		return enwinner::computer;
	else
		return enwinner::draw;
}

stgameresults fillgameresult(int gameround, short player1winntimes, short computerwintimes, short drawtimes)
{
	stgameresults gameresults;
	gameresults.gameround = gameround;
	gameresults.playerwintimes = player1winntimes;
	gameresults.computer2wintimes = computerwintimes;
	gameresults.drawtimes = drawtimes;
	gameresults.gamewinner = whowonthegame(player1winntimes, computerwintimes);
	gameresults.winnername = winnername(gameresults.gamewinner);
	return gameresults;

}

engamechoice readplayer1choice()
{
	short choice = 1;
	do
	{
		cout << "\n Your choice : [1]:stone, [2]:paper, [3]:scissors ? ";
		cin >> choice;

	} while (choice < 1 || choice>3);

		return (engamechoice)choice;
}

engamechoice getcomputerchoice()
{
	return (engamechoice)randomnumber(1, 3);
}

stgameresults playgame(short howmanyrounds)

{
	stroundinfo roundinfo;
	short player1wintimes = 0, computerwintimes = 0, drowtimes = 0;
	for (short gameround = 1; gameround <= howmanyrounds; gameround++)
	{
		cout << "\nRound [" << gameround << "] begins :\n";
		roundinfo.randnumber = gameround;
		roundinfo.player1choise = readplayer1choice();
		roundinfo.computerchoice = getcomputerchoice();
		roundinfo.winner = whowontheround(roundinfo);
		roundinfo.winnername = winnername(roundinfo.winner);

		if (roundinfo.winner == enwinner::player)
			player1wintimes++;
		else if (roundinfo.winner == enwinner::computer)
			computerwintimes++;
		else
			drowtimes++;

		printroundresults(roundinfo);
	}

	return fillgameresult(howmanyrounds, player1wintimes, computerwintimes, drowtimes);
}

string tabs(short numberoftabs)
{
	string t = "";
	for (int i = 1; i < numberoftabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void showgameoverscreen()
{
	cout << tabs(3) << "______________________________________________________\n\n";
	cout << tabs(3) << "                  +++G a m e  O v e r+++                \n";
	cout << tabs(3) << "______________________________________________________\n\n";
}

void showfinalgameresults(stgameresults gameresults)
{
	cout << tabs(3) << "___________________ [Game Results] ___________________\n\n";
	cout << tabs(3) << "Game Results          : " << gameresults.gameround << endl;
	cout << tabs(3) << "Player1 won times     : " << gameresults.playerwintimes << endl;
	cout << tabs(3) << "Coumputer won times   : " << gameresults.computer2wintimes << endl;
	cout << tabs(3) << "Drow times            : " << gameresults.drawtimes << endl;
	cout << tabs(3) << "Final Winner          : " << gameresults.winnername << endl;
	cout << tabs(3) << "______________________________________________________\n";
	setwinnerscreencolor(gameresults.gamewinner);
}

short readhowmanyrounds()
{
	short gamerounds = 1;
	do
	{
		cout << "How many rounds 1 to 10 ? \n";
		cin >> gamerounds;

	} while (gamerounds < 1 || gamerounds>10);

		return gamerounds;
}

void resetscreen()
{
	system("cls");
	system("color 4f");
}

void startgame()
{
	char playagain = 'Y';
	do
	{
		resetscreen();
		stgameresults gameresults = playgame(readhowmanyrounds());
		showgameoverscreen();
		showfinalgameresults(gameresults);
		cout << endl << "Do you want to play again Y/N ? ";
		cin >> playagain;

	} while (playagain == 'Y' || playagain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	startgame();

	return 0;
}