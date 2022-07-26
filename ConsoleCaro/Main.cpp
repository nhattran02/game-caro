#include "Data.h"
#include "View.h"
#include "Control.h"
#include "Model.h"

int main()
{
	_POINT _A[BOARD_SIZE][BOARD_SIZE];
	_PLAYER _PLAYER1, _PLAYER2;
	bool _TURN;
	int _COMMAND;
	int _X, _Y;
	int option;
	bool run = true;


	CreateConsoleWindow(WIDTH, HEIGHT);
	FixConsoleWindow();

	do
	{
		PlaySoundA("nen.wav", NULL, SND_ASYNC | SND_LOOP);
		option = SelectMenu(MainMenu());
		RunMainMenu(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y, run, option);
	} while (run);

}