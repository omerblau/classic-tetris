#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "board.h"
#include "general.h"
#include "game.h"
#include "player_computer.h"
#include "player_human.h"

using std::cout;

// the general game loop, take care of game modes and actions
void Game::run()
{
	Board::set_color_mode(false);// to set color off by default
	srand(time(NULL));
	show_consol_cursor(); // for game visualizition
	bool savedGame = false;
	char pressed = ' ';
	while (pressed != '9')
	{
		pressed = menu();
		switch (pressed)
		{
		case '1':
			new_game(HUMAN_VS_HUMAN);
			break;
		case '2':
			new_game(HUMAN_VS_COMPUTER);
			break;
		case '3':
			new_game(COMPUTER_VS_COMPUTER);
			break;
		case '4':
			continue_game();
			break;
		case '6':
			Board::set_color_mode(false);
			break;
		case '7':
			Board::set_color_mode(true);
			break;
		case '8':
			print_game_rules();
			break;
		case '9':
			delete player1;
			delete player2;
			break;
		default:
			break;
		}

	}
	clrscr();
	cout << "you chose to end the game\n";
	Sleep(500);
}

// prints the game menu and options
char Game::menu() const
{
	char ch;
	clrscr();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "For a new game - Human vs Human press: 1\n";
	cout << "For a new game - Human vs Computer press: 2\n";
	cout << "For a new game - Computer vs Computer press: 3\n";
	if (_gameStatus == Board::GAME_PAUSED)
		cout << "To continue press: 4\n";
	cout << "For no colors press: 6 (is set by default)\n";
	cout << "For colors press: 7\n";
	cout << "For instructions and keys press: 8\n";
	cout << "Exit press: 9\n";
	ch = _getch();
	if (_gameStatus == Board::GAME_PAUSED)
		while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '8' && ch != '9' && ch != '7' && ch != '6')
			ch = _getch();
	else
		while (ch != '1' && ch != '2' && ch != '3' && ch != '8' && ch != '9' && ch != '7' && ch != '6')
			ch = _getch();
	return ch;
}


void Game::make_player(int player, char player_type)
{

	;
	char level = '0';

	if (player_type == '1')
		if (player == 1)
			player1 = new player_human(player);
		else
			player2 = new player_human(player);

	else
	{
		cout << "pick the dificulty level of the computer: \n'a' for BEST\n'b' for GOOD\n'c' for NOVICE\n";
		while (level != 'a' && level != 'b' && level != 'c')
			level = _getch();

		if (player == 1)
			player1 = new player_computer(player, level);
		else
			player2 = new player_computer(player, level);
	}
}

// reset the data of the boards for a new gmae
void Game::new_game(int mode)
{
	clrscr();
	delete player1;
	delete player2;
	if (mode == 1)
	{
		make_player(1, '1');
		make_player(2, '1');
	}
	else if (mode == 2)
	{
		make_player(1, '1');
		make_player(2, '2');
	}
	else {
		make_player(1, '2');
		make_player(2, '2');
	}

	Sleep(1500);


	clrscr();
	for (int i = 3; i > 0; i--)
	{
		cout << "game starts in : " << i;
		Sleep(700);
		cout << "\b";
		clrscr();
	}
	player1->init_board_arr();
	player2->init_board_arr();
	game_round();
}

// set up the game from the last save point
void Game::continue_game()
{
	clrscr();
	player1->print_saved_board();
	player1->draw_boarder_and_score();

	player2->print_saved_board();
	player2->draw_boarder_and_score();
	game_round();
}

// prints the keys each player can use
void Game::print_game_rules()  const
{
	clrscr();
	cout << "           PLAYER 1                                   PLAYER 2 \n";
	cout << "use 'a' or 'A' to move left                use 'j' or 'J' to move left\n";
	cout << "use 'd' or 'D' to move right               use 'l' or 'L' to move right\n";
	cout << "use 'x' or 'X' to move down                use 'm' or 'M' to move down\n";
	cout << "use 's' or 'S' to rotate clockwise         use 'k' or 'K' to rotate clockwise\n";
	cout << "use 'w' or 'W' to move left                use 'i' or 'I' to move left\n";
	cout << "use 'esc' to pause and go to manu          use 'esc' to pause and go to manu\n\n";

	cout << "                     Press any key to go back to manu\n";
	(void)_getch(); // cast to void to make it clear the value isnt returned or saved, jsut wait for user input.
	return;
}


// this is function controlls the flow of the game
void Game::game_round()
{
	bool board1_collided = false, board2_collided = false;
	_gameStatus = Board::GAME_CONTINUES;
	player1->draw_boarder_and_score(); // draw the boards
	player2->draw_boarder_and_score();
	time_t loopStart;
	time_t timeToDrop = time(NULL);
	char pressed = ' ';
	while (_gameStatus == Board::GAME_CONTINUES) // game will run untill paused or a loss
	{
		loopStart = time(NULL);
		while (timeToDrop - loopStart < 1 && _gameStatus == Board::GAME_CONTINUES) // players gets 1 sec window to play, then we break to drop the blocks by 1
		{

			if (_kbhit())
				pressed = _getch();
			if (pressed == 27)
				_gameStatus = Board::GAME_PAUSED;

			player1->remember_key(pressed);
			player2->remember_key(pressed);
			pressed = ' ';

			player1->turn(board1_collided, _gameStatus);
			player2->turn(board2_collided, _gameStatus);

			Sleep(50);
			timeToDrop = time(NULL); // times the loop
		}

		if (!board1_collided && _gameStatus == Board::GAME_CONTINUES) // we drop the blocks ny 1
			player1->auto_drop_block(board1_collided, _gameStatus);

		if (!board2_collided && _gameStatus == Board::GAME_CONTINUES)
			player2->auto_drop_block(board2_collided, _gameStatus);
	}

	if (_gameStatus == Board::GAME_OVER)
	{
		game_winner();
	}

}


// prints the game winner
void Game::game_winner()
{
	clrscr();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	if (player1->get_score() > player2->get_score())
		cout << "PLAEYR 1 WINS!\n";
	else if (player1->get_score() < player2->get_score())
		cout << "PLAEYR 2 WINS!\n";
	else
		cout << "IT'S A TIE!\n";
	Sleep(1000);
	cout << "press any key to go back go back to menu";

	while (true)
	{
		if (_kbhit())
			break;
		Sleep(50);
	}

}

// used to not show the blinking cursur and helps the game visually
void Game::show_consol_cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
