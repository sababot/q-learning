#include <iostream>
#include <stdlib.h>
#include "utils.h"

#define RAN_LIM 500000

double qMatrix[8][8], rMatrix[8][8], gammaLR = 0.8;
int max_index[8], available_acts[8];
int ran[RAN_LIM];

using namespace std;

int main()
{
	///////////////////////////////
	////////// VARIABLES //////////
	///////////////////////////////

	int i, j;
	int initial_state, final_state = 7;
	int current_state, size_av_actions, action;
	double final_max=0.0, scores[100000], rMatrix[8][8], score=0.8;

	//////////////////////////////////////////
	////////// INPUT STARTING STATE //////////
	//////////////////////////////////////////

	cout << "enter the initial state: ";
	cin >> initial_state;
	
	/////////////////////////////////////////////////////////////////
	////////// CREATE ARRAY WITH RANDOM NUMBERS FROM 0 - 7 //////////
	/////////////////////////////////////////////////////////////////

	for (int i = 0; i < RAN_LIM; i++)
	{
		ran[i] = rand() % 8;
	}

	////////////////////////////////////////////////////
	////////// INITIALIZE Q-MATRIX & R-MATRIX //////////
	////////////////////////////////////////////////////

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			rMatrix[i][j] = -1.0;
			qMatrix[i][j] = 0.0;

			if ((i == 0 && j == 1) || (i == 1 && j == 5) || (i == 5 && j == 6) || (i == 5 && j == 4) || (i == 1 && j == 2) || (i == 2 && j == 3) || (i == 2 && j == 7) || (i == 4 && j == 7) || (i == 1 && j == 4))
			{
				rMatrix[i][j] = 0.0;
			}

			if ((j == 0 && i == 1) || (j == 1 && i == 5) || (j == 5 && i == 6) || (j == 5 && i == 4) || (j == 1 && i == 2) || (j == 2 && i == 3) || (j == 2 && i == 7) || (j == 4 && i == 7) || (j == 1 && i == 4) )
            		{
                		rMatrix[i][j] = 0.0;
            		}

			if ((i == 2 && j == 7) || (i == 7 && j == 7) || (i == 4 && j == 7))
			{
				rMatrix[i][j] = 100.0;
			}
		}
	}

	cout << "R-Matrix: " << endl;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			cout << rMatrix[i][j] << "\t";
		}

		cout << "\n";
	}

	cout << "\n\n\n";

	cout << rMatrix[7][7];

	///////////////////////////////////////
	////////// TRAINING Q-MATRIX //////////
	///////////////////////////////////////

	// functions included from "utils.h":   "update()", "available_actions()", 
	//										"sample_next_action()", "returnRandom()"

	for (i = 0; i < 500; i++)
	{
		cout << "\n";
		cout << "--------------------------------------------------------------------------------\n";
		cout << "------------------------------------Training------------------------------------\n";
		cout << "--------------------------------------------------------------------------------\n";

		current_state = returnRandom(ran);
		size_av_actions = available_actions(current_state, available_acts, rMatrix);
		action = sample_next_action(size_av_actions, available_acts, ran);

		cout << "\nnext step: " << action;

		score = update(current_state, action, rMatrix, qMatrix, max_index, ran, gammaLR);
		scores[i] = score;

		cout << "\nScore: " << score;

		if (i != 499)
		{
			system("clear");
		}
	}

	///////////////////////////////////
	////////// NORMALIZATION //////////
	///////////////////////////////////

	// find max
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (final_max < qMatrix[i][j])
			{
				final_max = qMatrix[i][j];
			}
		}
	}

	// print normalized q-matrix
	cout << "\n\n";
	cout << "--------------------------------------------------------------------------------\n";
	cout << "--------------------------------Trained Q-Matrix--------------------------------\n";
	cout << "--------------------------------------------------------------------------------\n";
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			cout << "\t" << qMatrix[i][j] / final_max * 100.0;
		}

		cout << "\n";
	}

	///////////////////////////////////////
	////////// FIND OPTIMAL PATH //////////
	///////////////////////////////////////

	int curr_state = initial_state;
	int visited[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int no_way = 0;
	int row_max = 0, max_ind = 0;

	cout << "Path: " << endl;

	while (visited[final_state] != 1)
	{
		cout << curr_state << " --> ";
		row_max = 0;
		max_ind = 0;

		for (int i = 0; i < 8; i++)
		{
			if (visited[i] == 0)
			{
				if (qMatrix[curr_state][i] > row_max)
				{
					max_ind = i;
					row_max = qMatrix[curr_state][i];
				}
			}
		}

		curr_state = max_ind;
		visited[max_ind] = 1;

		if (row_max == 0)
		{
			no_way = 1;
			break;
		}

		if (curr_state == final_state)
		{
			break;
		}
	}

	if (no_way == 1)
	{
		cout << "There's not way after this" << endl;
	}

	else
	{
		cout << curr_state << " is the shortest path" << endl;
	}
}
