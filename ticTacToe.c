/**
 * Tic Tac Toe mini-project in C
 * Still need to add some user input securities (enter letters, big numbers, etc.)
 * Written by Aleksandar Stajic, idea inspired from the interet
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

/* Grid position structure */
typedef struct position {
    int x;
    int y;
} data;

/* Array to hold the x and y values of each position on the board */
static data posData[9];

/* Grid formatting */
static char grid[5][18] = {
    {' ',' ','1',' ',' ','|',' ',' ','2',' ',' ','|',' ',' ','3',' ',' ', '\n'},
    {'-','-','-','-','-','|','-','-','-','-','-','|','-','-','-','-','-', '\n'},
    {' ',' ','4',' ',' ','|',' ',' ','5',' ',' ','|',' ',' ','6',' ',' ', '\n'},
    {'-','-','-','-','-','|','-','-','-','-','-','|','-','-','-','-','-', '\n'},
    {' ',' ','7',' ',' ','|',' ',' ','8',' ',' ','|',' ',' ','9',' ',' ', '\n'},
};

/* Function prototypes */
void printGrid(int position, char c);
void assignPos(void);
void playGame(void);
bool checkMove(int move);
int checkWin(void);

/* MAIN */
int main () {
    assignPos();  
    playGame();  

    return 0;
}

/**
 * playGame function controls the logic and sequencing of the game
 */
void playGame(void){
    int move;
    int turn = 0;
    int win = -1;

    printGrid(0, 'Z');

    while(turn < 9 && win == -1){
        if(turn % 2 == 0) printf("O's turn: ");
        else printf("X's turn: ");
        scanf("%d", &move);

        if(checkMove(move)){
            if(turn % 2 == 0) printGrid(move, 'O');
            else printGrid(move, 'X');
            turn++;
        }
        else{
            printf("\r\33[A\33[2K");
            printf("You cannot play there, try again ");
            Sleep(1500);
            printf("\r\33[2K");            
        }

        if(turn > 2){
            win = checkWin();
        }
    }

    if(win == 0) printf("X wins");
    else if(win == 1) printf("O wins");
    else printf("Tie game");
}

/**
 * checkWin function checks if a player has won the game
 * Start row by row, checking each value
 * If two different letters are next to each other, then that row doesn't have a winner
 * If we get to three letters in the same row, that letter has won
 * Do the same for columns
 * CHeck diagonals separately using same logic 
 */
int checkWin(void){
    int i = 0;
    int result = -1;

    /* Check each row */
    for(i = 0; i < 5; i += 2){
        if(grid[i][2] == grid[i][8] && grid[i][8] == grid[i][14]){
            if(grid[i][2] == 'X') return 0;
            else return 1;
        }
    }

    /* Check each column */
    for(i = 2; i < 18; i += 6){
        if(grid[0][i] == grid[2][i] && grid[2][i] == grid[4][i]){
            if(grid[0][i] == 'X') return 0;
            else return 1;
        }
    }

    /* Check first posible diagonal direction */
    if(grid[0][2] == grid[2][8] && grid[2][8] == grid[4][14]){
        if(grid[0][2] == 'X') return 0;
            else return 1;
    }

    /* Check second possible diagonal direction */
    else if(grid[0][14] == grid[2][8] && grid[2][8] == grid[4][2]){
        if(grid[0][i] == 'X') return 0;
        else return 1;
    }

    return result;

}

/**
 * checkMove function validates if a given space on the board is already taken
 * if a space is taken, player is informed they cannot play there based on the return value
 */
bool checkMove(int move){
    if(grid[posData[move-1].y][posData[move-1].x] == 'X' || grid[posData[move-1].y][posData[move-1].x] == 'O'){
        return false;
    }

    else return true;
}

/**
 * printGrid function prints out and updates the game board on the console
 * takes in the parameter of which position to write to and the letter that was played
 * updates the letter that was played on the board and then prints to the screen
 */
void printGrid(int position, char c){
    system("cls");
    printf("\n");

    /* if statement makes sure we print a clean board upon starting the game */
    if(c != 'Z') grid[posData[position-1].y][posData[position-1].x] = c;

    /* Printing grid UI */
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 18; j++){
            printf("%c", grid[i][j]);
        }
    }
    printf("\n\n");
}

/** 
 * assignPos function initializes the position data array
 * stores the positions of each open space on the board 
 * useful because then we can just reference this array in order to 
 * play a letter on the board, and the indeces make sense logically with the 
 * grid formatting
 */
void assignPos(void){
    int i, j;
    int temp = 2;
    
    for(i = 0; i < 9; i++){
        if(temp > 14) temp = 2;
        posData[i].x = temp;
        temp += 6;
    }

    temp = 0;
    for(i = 0; i < 5; i += 2){
        posData[temp++].y = i;
        posData[temp++].y = i;
        posData[temp++].y = i;
    }
}
