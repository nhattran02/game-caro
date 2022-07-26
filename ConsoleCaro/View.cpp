#include "View.h"

void CreateConsoleWindow(int pWidth, int pHeight)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,10);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE);
}

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void DrawTableLine(int numOfCol, char mainSym, char subSym, int width)
{
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) cout << mainSym;
		cout << subSym;
	}
	for (int i = 0; i < width; i++) cout << mainSym;
}

void DrawBoard(int row, int col, int width, int height, int x, int y)
{
	GotoXY(x, y);
	cout << TOP_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, TOP_CROSS, width);
	cout << TOP_RIGHT;

	for (int i = 0; i < (row - 1) * (height + 1); i++)
	{
		GotoXY(x, y + i + 1);
		if ((i + 1) % (height + 1) != 0)
		{
			cout << VERTICAL_LINE;
			DrawTableLine(col, SPACE, VERTICAL_LINE, width);
			cout << VERTICAL_LINE;
		}
		else
		{
			cout << LEFT_CROSS;
			DrawTableLine(col, HORIZONTAL_LINE, CROSS, width);
			cout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + (row - 1) * (height + 1) + 1 + i);
		cout << VERTICAL_LINE;
		DrawTableLine(col, SPACE, VERTICAL_LINE, width);
		cout << VERTICAL_LINE;
	}

	GotoXY(x, y + (row - 1) * (height + 1) + 1 + height);
	cout << BOTTOM_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, BOTTOM_CROSS, width);
	cout << BOTTOM_RIGHT;
}

void DrawLoaded(_POINT _A[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].c == P_X)
			{
				PrintText("X", 260, _A[i][j].x, _A[i][j].y);
			}
			else if (_A[i][j].c == P_O)
			{
				PrintText("O", 259, _A[i][j].x, _A[i][j].y);
			}
	}
}

_MENU MainMenu()
{
	_MENU menu;

	menu.options = 5;
	menu.x = X_CENTER - 13;
	menu.y = Y_CENTER + 10;
	menu.cursorColor = 12;

	system("cls");

	DrawBigText("Logo.txt", 262, 12, 1);
	DrawBox(271, 50, 13, X_CENTER - 25, Y_CENTER + 5);
	//PrintText("***************************", 271, menu.x, menu.y - 3);
	//PrintText("*    Welcome to Caroro    *", 271, menu.x, menu.y - 2);
	//PrintText("***************************", 271, menu.x, menu.y - 1);
	PrintText("          NEW GAME          ", 271, menu.x, menu.y);
	PrintText("         LOAD GAME          ", 271, menu.x, menu.y + 1);
	PrintText("           RANKING          ", 271, menu.x, menu.y + 2);
	PrintText("         HOW TO PLAY        ", 271, menu.x, menu.y + 3);
	PrintText("            QUIT            ", 271, menu.x, menu.y + 4);

	return menu;
}

_MENU LoadingMenu()
{
	_MENU menu;
	string name;


	std::vector<string> files;
	files = LoadFiles();

	menu.options = files.size();
	menu.x = X_CENTER - 15;
	menu.y = Y_CENTER - files.size() / 2;
	menu.cursorColor = 12;

	DrawBox(260, 100, menu.options + 10, X_CENTER - 50, Y_CENTER - 5);
	PrintText("[----------Saved Games----------]", 262, menu.x, menu.y - 2);
	for (int i = 0; i < files.size(); i++)
	{
		name = "         " + files.at(i);
		PrintText(name, 271, menu.x, menu.y + i);
	}
	PrintText("Press ESC to turn back", 266, menu.x + 3, menu.y + 16);
	return menu;
}

_MENU EscMenu(_POINT _A[][BOARD_SIZE])
{
	_MENU menu;

	menu.options = 3;
	menu.x = _A[0][BOARD_SIZE - 1].x + 65;
	menu.y = Y_CENTER + 3;
	menu.cursorColor = 12;

	//DrawBoard(1, 1, 62, 25, menu.x - 23, menu.y - 19);
	DrawBox(3, 63, 25, menu.x - 23, menu.y - 19);
	DrawBigText("EscLogo.txt", 3, menu.x - 22, menu.y - 17);
	PrintText("    CONTINUE    ", 258, menu.x, menu.y);
	PrintText("    SAVE GAME   ", 258, menu.x, menu.y + 1);
	PrintText("    EXIT GAME   ", 258, menu.x, menu.y + 2);

	return menu;
}

_MENU YesNoMenu(int x, int y)
{
	_MENU menu;

	menu.options = 2;
	menu.x = x;
	menu.y = y;
	menu.cursorColor = 12;

	PrintText("YES", 271, menu.x, menu.y);
	PrintText("NO", 271, menu.x, menu.y + 1);

	return menu;
}

void ShowTurn(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN)
{
	int start = _A[0][BOARD_SIZE - 1].x + 12;

	DrawBox(256, 30, 10, start, 2);

	DrawBigText((_TURN) ? "X.txt" : "O.txt", (_TURN) ? 260 : 259, start, 2);

	DrawBox(256, 20, 1, start - 2, 14);
	PrintText(((_TURN) ? _PLAYER1.name : _PLAYER2.name) + "'s turn!", (_TURN) ? 260 : 259, start - 2, 14);
}

void ShowPlayerInfo(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2)
{
	int start = _A[0][BOARD_SIZE - 1].x + 4;

	DrawBoard(3, 3, 10, 1, start, 17);

	PrintText(_PLAYER1.name, 260, start + 12, 18);
	PrintText(_PLAYER2.name, 259, start + 23, 18);
	PrintText("WIN GAMES", 262, start + 1, 20);
	PrintText(std::to_string(_PLAYER1.wins), 271, start + 12, 20);
	PrintText(std::to_string(_PLAYER2.wins), 271, start + 23, 20);
	PrintText("RANK", 262, start + 1, 22);
	PrintText(std::to_string(_PLAYER1.rank), 271, start + 12, 22);
	PrintText(std::to_string(_PLAYER2.rank), 271, start + 23, 22);
	DrawBoard(1, 1, 43, 8, _A[0][BOARD_SIZE - 1].x + 58, Y_CENTER - 7);
	//PrintText("PAUSE:      ESC", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 6);
	//PrintText("MOVE LEFT:  A", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 5);
	//PrintText("MOVE RIGHT: D", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 4);
	//PrintText("MOVE UP:    W", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 3);
	//PrintText("MOVE DOWN:  S", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 2);
	PrintText("       +---+		", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 6);
	PrintText("       | W |		", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 5);
	PrintText("       +---+	       +-------+", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 4);
	PrintText("+---+  +---+  +---+  | ENTER |", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 3);
	PrintText("| A |  | S |  | D |  +-------+", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 2);
	PrintText("+---+  +---+  +---+  ", 264, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 1);
	PrintText("MOVE: W/S/A/D		CHECK: ENTER  ", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER + 0);
	PrintText("PAUSE: ESC   		CHECK: SPACE  ", 271, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER + 1);






}

void ShowHelp()
{
	int x = X_CENTER - 25;
	int y = Y_CENTER - 10;
	int x_ = X_CENTER - 25;
	int y_ = Y_CENTER - 5;
	string line;
	int i = 0;
	int j = 0;

	std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);

	system("cls");
	while (getline(helpFile, line))
	{
		PrintText(line, 264, x, y + i);
		i++;
	}
	std::fstream XFile;
	XFile.open("XFile.txt", std::fstream::in);

	//system("cls");
	while (getline(XFile, line))
	{
		PrintText(line, 266, x_, y_ + j);
		j++;
	}
}

void ShowRank()
{
	int x = X_CENTER - 10;
	int y = Y_CENTER - 10;
	std::vector<_PLAYER> players = GetPlayerList();

	system("cls");

	PrintText("********************", 271, x, y);
	PrintText("*      RANKING     *", 271, x, y + 1);
	PrintText("********************", 271, x, y + 2);
	PrintText("----------------------------------------", 224, x - 10, y + 4);
	PrintText("[Master King] " + players.at(0).name, 260, x - 2, y + 6);
	PrintText("[King] " + players.at(1).name, 263, x - 2, y + 7);
	for (int i = 2; i < 10; i++)
	{
		cout << "\n";
		PrintText("[Master] " + players.at(i).name, 270, x - 2, y + 6 + i);
	}
	PrintText("Press ESC to turn back", 266, x - 2, y + 18);
}

void GotoXY(int x, int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBox(int color, int width, int height, int x, int y)
{
	SetColor(color);
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
	}
	SetColor(10);
}

void SetColor(int color)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void PrintText(string text, int color, int x, int y)
{
	GotoXY(x, y);
	SetColor(color);
	cout << text;
	SetColor(7);
}

void DrawBigText(string filename, int color, int x, int y)
{
	std::fstream textFile;
	textFile.open(filename.c_str(), std::fstream::in);
	string line;
	std::vector<std::string> line1;
	int tempY = y;
	while (getline(textFile, line)) line1.push_back(line);
	if (filename == "XWin.txt" || filename == "OWin.txt" || filename == "Draw.txt")
	{
		int count = 0;
		while (count <= 48)
		{
			for (int i = 0; i < line1.size(); i++)
				PrintText(line1[i], color + count % 10, x, y++);
			y = tempY;
			Sleep(0);
			for (int i = 0; i < line1.size(); i++)
			{
				string templine = "";
				for (int j = 0; j < line1[i].length(); j++) templine += ' ';
				PrintText(templine, 10, x, y++);
			}
			Sleep(0);
			y = tempY;
			count++;
		}
	}
	for (int i = 0; i < line1.size(); i++)
		PrintText(line1[i], color, x, y++);
	textFile.close();
}

int ProcessFinish(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int pWhoWin)
{
	switch (pWhoWin)
	{
	case P_X:
		_PLAYER1.wins++;
		PlaySoundA("WinSounds_.wav", NULL, SND_ASYNC);
		DrawBox(4, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("XWin.txt", 4, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		SavePlayer(_PLAYER1);
		break;
	case P_O:
		_PLAYER2.wins++;
		PlaySoundA("WinSounds_.wav", NULL, SND_ASYNC);
		DrawBox(9, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("OWin.txt", 9, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		SavePlayer(_PLAYER2);
		break;
	case 0:
		PlaySoundA("WinSounds_.wav", NULL, SND_ASYNC);
		DrawBox(111, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("Draw.txt", 111, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		break;
	case 2:
		_TURN = !_TURN;
		ShowTurn(_A, _PLAYER1, _PLAYER2, _TURN);
		break;
	}
	return pWhoWin;
}

bool AskContinue(int x, int y)
{
	int option;

	option = SelectMenu(YesNoMenu(x, y));
	switch (RunYesNoMenu(option))
	{
	case 'Y':
		return true;
	case 'N':
		return false;
	}
}