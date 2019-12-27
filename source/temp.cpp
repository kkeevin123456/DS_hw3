#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/board.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    int color = player.get_color();
    int weight[5][6] = {0};

    // if next step will win, choose it
    for (int i=0; i<5; i++){
        for (int j=0; j<6; j++){
            Board test_board;
            test_board = board;
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w')
                test_board.place_orb(i, j, &player);
            if(test_board.win_the_game(player)){
                index[0] = i;
                index[1] = j;
                return;
            }
        }
    }

    // initialize weight
    for(int i=1; i<4; i++){
        for(int j=1; j<5; j++){
            if(board.get_cell_color(i, j) == 'w') weight[i][j] = 9;
            else if(board.get_cell_color(i, j) != color) weight[i][j] = -1000;
            else if(board.get_cell_color(i, j) == color && board.get_orbs_num(i, j) == 1) weight[i][j] = 7;
            else if(board.get_cell_color(i, j) == color && board.get_orbs_num(i, j) == 2) weight[i][j] = 6;
        }
    }

    for(int i=0; i<5; i++){
        if(board.get_cell_color(0, i) == 'w') weight[0][i] = 8;
        if(board.get_cell_color(i, 0) == 'w') weight[i][0] = 8;
        if(board.get_cell_color(i, 5) == 'w') weight[i][5] = 8;
        if(board.get_cell_color(4, i) == 'w') weight[4][i] = 8;
    }

    if(board.get_cell_color(0, 0) == 'w') weight[0][0] = 10;
    if(board.get_cell_color(0, 5) == 'w') weight[0][5] = 10;
    if(board.get_cell_color(4, 0) == 'w') weight[4][0] = 10;
    if(board.get_cell_color(4, 5) == 'w') weight[4][5] = 10;

    /*for(int i=0; i<5; i++){
        for(int j=0; j<6; j++){
            cout << weight[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i=0; i<5; i++){
        for(int j=0; j<6; j++){
            cout << board.get_cell_color(i, j) << " ";
        }
        cout << endl;
    }*/

    int max = 0;
    for(int i=0; i<5; i++){
        for(int j=0; j<6; j++){
            if(weight[i][j] > max){
                max = weight[i][j];
                index[0] = i;
                index[1] = j;
            }
        }
    }
    if(max != 0) return;

    //system("pause");

    srand(time(NULL));
    int row, col;
    
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
}