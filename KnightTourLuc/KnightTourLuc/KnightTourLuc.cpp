// KnightTourLuc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <string>
#define size 8
using namespace std;

int the_x, the_y;
string *the_chosen;

// defines the structure for moves
typedef struct the_moves {
	// x and y coordinates on board
	int x, y;
}the_moves;

void printTour(int tour[size][size])
{
	string pointer = *the_chosen;
	int x = atoi(pointer.c_str());
	int i, j;
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			cout << tour[i][j] << "\t";
		}
		cout << endl;
	}
	system("pause");
}

bool isMovePossible(the_moves next_move, int tour[size][size])
{
	string pointer = *the_chosen;
	int x = atoi(pointer.c_str());
	int i = next_move.x;
	int j = next_move.y;
	if ((i >= 0 && i < x) && (j >= 0 && j < x) && (tour[i][j] == 0))
		return true;
	return false;
}

bool findTour(int tour[size][size], the_moves move_KT[], the_moves current_move, int move_count)
{
	int i;
	the_moves next_move;
	string pointer = *the_chosen;
	int x = atoi(pointer.c_str());

	if (move_count == x * x - 1)
	{
		//tour finished
		return true;
	}

	for (int i = 0; i < x; i++)
	{
		next_move.x = current_move.x + move_KT[i].x;
		next_move.y = current_move.y + move_KT[i].y;

		if (isMovePossible(next_move, tour)) {
			tour[next_move.x][next_move.y] = move_count + 1;
			if (findTour(tour, move_KT, next_move, move_count + 1) == true) {
				return true;
			}
			else {
				tour[next_move.x][next_move.y] = 0;
			}
		}
	}
	return false;
}


void runTour()
{
	int tour[size][size];
	int i, j;

	//init the board
	string pointer = *the_chosen;
	int x = atoi(pointer.c_str());
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			tour[i][j] = 0;
		}
	}

	//all moves that a knight can make
	the_moves move_KT[8] = { { 2, 1 }, { 1, 2 }, { -1, 2 }, { -2, 1 },
	{ -2, -1 }, { -1, -2 }, { 1, -2 }, { 2, -1 } };

	//start position
	the_moves start_move = { the_x, the_y };

	if (findTour(tour, move_KT, start_move, 0) == false) {
		cout << "\nKnight tour does not exist\n";
		system("pause");
	}
	else {
		cout << "\nKnights Tour exists! It has the following solution starting from\n";
		cout << "x: " + the_x;
		cout << "\ny: " + the_y;
		cout << "\n";
		printTour(tour);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "What size do you want the board to be? (Press Enter for standard size)\n";
	string reference;
	getline(cin, reference);
	the_chosen = &reference;
	if (*the_chosen == "")
	{
		*the_chosen = size;
		cout << "You didn't choose a size, we will use the standard: " + *the_chosen;
	}
	else
		cout << "You chose a board size of " + *the_chosen;
	string x, y;
	cout << "\n\nAt what x position do you want to start?\n";	
	getline(cin, x);
	x != "" ? cout << "You selected " + x : cout << "You've selected nothing, using 0";
	cout << "\n\nAt what y position do you want to start?\n";
	getline(cin, y);
	y != "" ? cout << "You selected " + y : cout << "You've selected nothing, using 0";
	the_x = x != "" ? atoi(x.c_str()) : 0;
	y != "" ? the_y = atoi(y.c_str()) : the_x = 0;
	cout << "\n\nCalculating...\n";
	runTour();
	cout << endl;
	return 0;
}

