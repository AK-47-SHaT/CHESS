#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include<conio.h>
#define SIZE 8
#define TIME_LIMIT 600 // time of 600 seconds for each player

typedef struct point
{
  int point1 ;
  int point2 ;
}point;




// Chessboard with pieces

char board[SIZE][SIZE] = 
{
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'R', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

// Function to print the chessboard

void printBoard()

{
  printf("\n           |---------------------|         \n");
  printf("           |      C*CHESS        |     \n");
  printf("           |---------------------|         \n\n");


  printf("         a   b   c   d   e   f   g   h     \n");

  printf("       |---|---|---|---|---|---|---|---|  \n");

  printf("     8 | %c | %c | %c | %c | %c | %c | %c | %c | 8 \n", board[0][0],board[0][1],board[0][2],board[0][3],board[0][4],board[0][5],board[0][6],board[0][7]);

  printf("       |---|---|---|---|---|---|---|---|   \n");

  printf("     7 | %c | %c | %c | %c | %c | %c | %c | %c | 7 \n",board[1][0],board[1][1],board[1][2],board[1][3],board[1][4],board[1][5],board[1][6],board[1][7] );

  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     6 | %c | %c | %c | %c | %c | %c | %c | %c | 6 \n", board[2][0],board[2][1],board[2][2],board[2][3],board[2][4],board[2][5],board[2][6],board[2][7] );
  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     5 | %c | %c | %c | %c | %c | %c | %c | %c | 5 \n",board[3][0],board[3][1],board[3][2],board[3][3],board[3][4],board[3][5],board[3][6],board[3][7] );
  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     4 | %c | %c | %c | %c | %c | %c | %c | %c | 4 \n",board[4][0],board[4][1],board[4][2],board[4][3],board[4][4],board[4][5],board[4][6],board[4][7] );
  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     3 | %c | %c | %c | %c | %c | %c | %c | %c | 3 \n",board[5][0],board[5][1],board[5][2],board[5][3],board[5][4],board[5][5],board[5][6],board[5][6],board[5][7] );

  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     2 | %c | %c | %c | %c | %c | %c | %c | %c | 2 \n",board[6][0],board[6][1],board[6][2],board[6][3],board[6][4],board[6][5],board[6][6],board[6][7] );

  printf("       |---|---|---|---|---|---|---|---|   \n");

 printf("     1 | %c | %c | %c | %c | %c | %c | %c | %c | 1 \n",board[7][0],board[7][1],board[7][2],board[7][3],board[7][4],board[7][5],board[7][6],board[7][7] );

  printf("       |---|---|---|---|---|---|---|---|   \n");

  printf("         a   b   c   d   e   f   g   h   \n");
}

//converting chess notation to array index

int fileToIndex(char file) 
{
    return file - 'a';
}

int rankToIndex(char rank) 
{
    return SIZE - (rank - '0');
}


//Check if position is in the board

bool isOnBoard(int x, int y) 
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

//Checking if the path is clear for sliding pieces (rooks, bishops, queens)

bool isSlidePathClear(int startX, int startY, int endX, int endY) 
{
    /*int dx = (endX - startX) != 0 ? (endX - startX) / abs(endX - startX) : 0;
    int dy = (endY - startY) != 0 ? (endY - startY) / abs(endY - startY) : 0;*/
    int dx;
    int dy;
    if((endX - startX) != 0)
    {
        dx=(endX - startX) / abs(endX - startX);
    }
    else
    {
        dx=0;
    }
    if((endY - startY) != 0)
    {
        dy=(endY - startY) / abs(endY - startY);
    }
    else
    {
        dy=0;
    }
    int x = startX + dx;
    int y = startY + dy;

    while (x != endX || y != endY) 
    {
        if (board[y][x] != ' ') {
            return false; // Path is blocked
        }
        x += dx;
        y += dy;
    }
    return true;
}

//Checking if a move is a valid jumping a knight

bool isJumpMoveValid(int startX, int startY, int endX, int endY) 
{
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

//Function to check piece movement according to rules and move pieces on the board

bool isValidMove(int startX, int startY, int endX, int endY, char piece) 
{
    int dx = endX - startX;
    int dy = endY - startY;

    switch (tolower(piece)) 
    {
        case 'p': //for Pawn
            if (piece == 'P')
             { 
                //the pawn is a White pawn

             //normal moment for white piece
               if((dx==0 && dy==-1 && board[endY][endX]==' ') ||
                (startY == 6 && dx == 0 && dy == -2 && board[endY][endX]==' ' && board[endY-1][endX]==' ') )
                {
                return true;
               }
               // return ((dx == 0 && dy == -1) || (startY == 6 && dx == 0 && dy == -2)) ;

             //for capturing
             else if(abs(dx)==1 && dy==-1 && islower(board[endY][endX]))
             {
                return true;
             }

            } 
            else
             { //Black pawn
               // return ((dx == 0 && dy == 1) || (startY == 1 && dx == 0 && dy == 2)) ;
               //normal moment for black piece
               if((dx==0 && dy==1 && board[endY][endX]==' ') ||
                (startY == 1 && dx == 0 && dy == 2 && board[endY][endX]==' ' && board[endY-1][endX]==' ') )
                {
                return true;
               }
               // return ((dx == 0 && dy == -1) || (startY == 6 && dx == 0 && dy == -2)) ;

             //for capturing
             else if(abs(dx)==1 && dy== 1 && isupper(board[endY][endX]))
             {
                return true;
             }
            }
            return false;

        case 'r': //Rook

            return (dx == 0 || dy == 0) && isSlidePathClear(startX, startY, endX, endY);

        case 'b': //Bishop

            return (abs(dx) == abs(dy)) && isSlidePathClear(startX, startY, endX, endY);

        case 'q': //Queen

            return (dx == 0 || dy == 0 || abs(dx) == abs(dy)) && isSlidePathClear(startX, startY, endX, endY);

        case 'k': //King

            return abs(dx) <= 1 && abs(dy) <= 1;

        case 'n': //Knight

            return isJumpMoveValid(startX, startY, endX, endY);
    }
    return false;
}
//
//void points(int endX ,int endY , int currentPlayer ,point);
//








//Moving function with movement checking

bool movePiece(char startFile, char startRank, char endFile, char endRank, int *currentPlayer)
{
    int startX = fileToIndex(startFile);
    int startY = rankToIndex(startRank);
    int endX = fileToIndex(endFile);
    int endY = rankToIndex(endRank);

    if (!isOnBoard(startX, startY) || !isOnBoard(endX, endY))
    {
        printf("Move out of bounds.\n");
        return false;
    }

    char piece = board[startY][startX];
    if (piece == ' ')
    {
        printf("No piece at starting position.\n");
        return false;

         }

        //check if the pieces are of same colour
    if ((*currentPlayer==1 && isupper(board[endY][endX])) || (*currentPlayer==2 && islower(board[endY][endX])) )
    {
       printf("can not capture your own piece");
       return false;
    }


    //Check if the move is valid
    if (!isValidMove(startX, startY, endX, endY, piece))
    {
        printf("Invalid move for %c.\n", piece);
        return false;
    }





    





    // Perform the move
    board[endY][endX] = piece;
    board[startY][startX] = ' ';
    return true;
}

//function for upgrading pawn when it reaches end rank of opposition
bool pawnUpgration(int endY,int endX)
{

    char piece = board[endY][endX];
    char choice;

    if((endY==0 && piece=='P') || (endY==7 && piece=='p') ){

        printf("Choose piece to be upgraded in place of pawn\n R N B Q\n");
        scanf(" %c",&choice);
        getchar();





        if(piece == 'P' )
        {
            switch (choice)
        {
            case 'R': board[endY][endX]='R' ;
                        break;

            case 'N': board[endY][endX]='N' ;
                        break;

            case 'B': board[endY][endX]='B' ;
                        break;

            case 'Q': board[endY][endX]='Q' ;
                        break;

            default: printf("Invalid Input\n"); pawnUpgration(endY,endX) ;
            }
        }
        else if(piece == 'p')
        {
           switch (choice)
        {
            case 'r': board[endY][endX]='r' ;
                        break;

            case 'n': board[endY][endX]='n' ;
                        break;

            case 'b': board[endY][endX]='b' ;
                        break;

            case 'q': board[endY][endX]='q' ;
                        break;

            default: printf("Invalid Input\n"); pawnUpgration(endY,endX) ;
        }
        }
        //else {
          //  printf("Invalid choice. Please choose R, N, B, or Q.\n");
            //pawnUpgration(endY, endX); // Retry on invalid input
        //}
        //return true ;

   }
        return false;

}









/*
bool pawnUpgration(int endY,int endX){

    char piece = board[endY][endX];
    char choice;

    if((endY==0 && piece=='P') || (endY==7 && piece=='p') ){

        printf("Choose piece to be upgraded in place of pawn\n R N B Q\n");
        //scanf("%c",&choice);
        choice = getchar();

        if(piece == 'P')
        {
            board[endY][endX]=choice;
            }
        else if(piece == 'p')
        {
            board[endY][endX]=choice;
        }
        else {
            printf("Invalid choice. Please choose R, N, B, or Q.\n");
            pawnUpgration(endY, endX); // Retry on invalid input
        }
        return true ;
}

        return false;

}
*/






int player1Time = TIME_LIMIT;
int player2Time = TIME_LIMIT;
time_t lastMoveTime;


//function for switching players after each turn

void switchPlayer(int *currentPlayer)
{

    int elapsed = (int)(time(NULL)-lastMoveTime);

    if(*currentPlayer==1)player1Time-=elapsed;
    else player2Time-=elapsed;

    // Display time remaining for both players
    printf("Player 1 time: %d:%02d\n", player1Time / 60, player1Time % 60);
    printf("Player 2 time: %d:%02d\n", player2Time / 60, player2Time % 60);

    //check if a player ran out of time
    if (player1Time <= 0 || player2Time <= 0)
    {
        printf("Player %d ran out of time! Player %d wins!\n", *currentPlayer, (*currentPlayer == 1) ? 2 : 1);
        exit(0);}



    // Switch player and reset last move time
    *currentPlayer = (*currentPlayer == 1) ? 2 : 1;
    lastMoveTime = time(NULL);
}


//checkmate code begins



//function to find coordinates of king of current player

void findKing(int *kingX, int *kingY, int currentPlayer)
{
    char king = (currentPlayer == 1) ? 'K' : 'k';

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (board[y][x] == king)
            {
                *kingX = x;
                *kingY = y;
                return;
            }
        }
    }
}

//functon to check if the king of current player is in check

bool isKingInCheck(int kingX, int kingY, int currentPlayer)
{
    for (int y = 0; y < SIZE; y++)
    {                 // Loop through all rows
        for (int x = 0; x < SIZE; x++)
        {             // Loop through all columnsr
            char piece = board[y][x];                // Get the piece at position (x, y)

            if (piece == ' ') continue;             // Skip empty squares

            // Check if the piece belongs to the opponent
            if ((currentPlayer == 1 && islower(piece)) || // Player 1 is uppercase, opponent is lowercase
                (currentPlayer == 2 && isupper(piece)))
                { // Player 2 is lowercase, opponent is uppercase

                //Checking if this piece can move to the king's position
                if (isValidMove(x, y, kingX, kingY, piece))
                {
                    return true; // King is under attack
                }
            }
        }
    }

    return false; // No piece can attack the king
}



/*bool simulateAllMoves(int currentPlayer) {
    for (int startY = 0; startY < SIZE; startY++) {  // Loop through all rows
        for (int startX = 0; startX < SIZE; startX++) { // Loop through all columns
            char piece = board[startY][startX];      // Get the piece at position (startX, startY)

            // Skip if there's no piece or it's the opponent's piece
            if (piece == ' ' ||
                (currentPlayer == 1 && islower(piece)) ||
                (currentPlayer == 2 && isupper(piece))) {
                continue;
            }

            // Check all possible destinations
            for (int endY = 0; endY < SIZE; endY++) {
                for (int endX = 0; endX < SIZE; endX++) {
                    // Skip invalid moves
                    if (!isValidMove(startX, startY, endX, endY, piece)) {
                        continue;
                    }

                    // Simulate the move
                    char originalPiece = board[endY][endX];
                    board[endY][endX] = piece;
                    board[startY][startX] = ' ';

                    // Check if the move leaves the king in check
                    int kingX, kingY;
                    findKing( &kingX, &kingY , currentPlayer );
                    bool stillInCheck = isKingInCheck(kingX, kingY, currentPlayer);

                    // Revert the move
                    board[startY][startX] = piece;
                    board[endY][endX] = originalPiece;

                    // If the king is safe after this move, it's valid
                    if (!stillInCheck) {
                        return true; // At least one valid move exists
                    }
                }
            }
        }
    }

    return false; // No valid moves exist
}



bool simulateAllMoves(int currentPlayer) {
    for (int startY = 0; startY < SIZE; startY++) {
        for (int startX = 0; startX < SIZE; startX++) {
            char piece = board[startY][startX];

            // Skip if square is empty or not the current player's piece
            if (piece == ' ' ||
                (currentPlayer == 1 && islower(piece)) ||
                (currentPlayer == 2 && isupper(piece))) {
                continue;
            }

            for (int endY = 0; endY < SIZE; endY++) {
                for (int endX = 0; endX < SIZE; endX++) {
                    // Check if the move is valid
                    if (!isValidMove(startX, startY, endX, endY, piece)) {
                        continue;
                    }

                    // Simulate the move
                    char capturedPiece = board[endY][endX];
                    board[endY][endX] = piece;
                    board[startY][startX] = ' ';

                    // Find the king's new position
                    int kingX, kingY;
                    findKing(&kingX, &kingY, currentPlayer);

                    // Check if the king is still in check
                    bool inCheck = isKingInCheck(kingX, kingY, currentPlayer);

                    // Undo the move
                    board[startY][startX] = piece;
                    board[endY][endX] = capturedPiece;

                    // If the move leaves the king safe, return true
                    if (!inCheck) {
                        return true;
                    }
                }
            }
        }
    }
    return false; // No valid moves found
}*/

//function to sim all moves of the pieces to check if the king has any valid moves left for the turn

bool simulateAllMoves(int currentPlayer)
{
    for (int startY = 0; startY < SIZE; startY++)
    {
        for (int startX = 0; startX < SIZE; startX++)
        {
            char piece = board[startY][startX];

            // Skip if square is empty or not the current player's piece

            if (piece == ' ' ||
                (currentPlayer == 1 && islower(piece)) ||
                (currentPlayer == 2 && isupper(piece)))
            {
                continue;
            }

            for (int endY = 0; endY < SIZE; endY++)
            {
                for (int endX = 0; endX < SIZE; endX++)
                {
                    // Check if the move is valid

                    if (!isValidMove(startX, startY, endX, endY, piece))
                    {
                        continue;
                    }


                    // Simulate the move

                    char capturedPiece = board[endY][endX];
                    board[endY][endX] = piece;
                    board[startY][startX] = ' ';


                    //Finding the king's position after the move

                    int kingX, kingY;
                    findKing(&kingX, &kingY, currentPlayer);

                    //Checking if the king is still in check

                    bool inCheck = isKingInCheck(kingX, kingY, currentPlayer);


                    if(inCheck)printf("CHECK AND MATE,\tLOST\n");
                    break;


                    // Undo the move

                    board[startY][startX] = piece;
                    board[endY][endX] = capturedPiece;

                    // If the move doesn't leave the king in check, return true

                    if (!inCheck) {
                        return true;
                    }
                }
            }
        }
    }
    return false; //No valid moves left
}



//function to check if current player has been checkmated

bool isCheckmate(int currentPlayer)
{
    int kingX, kingY;
    findKing(&kingX, &kingY, currentPlayer);

    if (isKingInCheck(kingX, kingY, currentPlayer) && !simulateAllMoves(currentPlayer))
    {
        printf("king in check");
        return true;
    }

    else
    {

    return false;
    }
}


void points(int endX ,int endY  ,int*point1,int*point2);

void declare(int *point1 , int *point2);

void welcome();

void end();

//Main function for doing all operations and integrating the code

int main()
{
    system("color 06") ;
    char startFile, startRank, endFile, endRank;
    bool gameRunning = true;
    int currentPlayer = 1;
    int kingX ,kingY;
    int point1 = 0;
    int point2=0;
    int chance;
    lastMoveTime=time(NULL);
    welcome();
    printf("Simple Chess Program\n");
    printBoard();

    while (gameRunning)
    {

        (currentPlayer==1) ? system("color 0C") : system("color 0B") ;

        findKing( &kingX,  &kingY, currentPlayer);

        if(isKingInCheck( kingX,  kingY, currentPlayer))
        {
            system("color 72");
            printf("KING IS UNDER ATTACK\n");
            
        }






       

        printf("Player %d's turn\n",currentPlayer);
        printf("Enter move (e.g., e2 e4) or 'q' to quit: ");
        scanf(" %c%c %c%c", &startFile, &startRank, &endFile, &endRank);

        if (startFile == 'q')
        {   

            declare(&point1,&point2);
            printf("Quitting the game.\n");
            break;
        }

        int startX = fileToIndex(startFile);
        int startY = rankToIndex(startRank);
        int endX = fileToIndex(endFile);
        int endY = rankToIndex(endRank);

          
          points(endX,endY,&point1,&point2);
          


        if( isupper(board[startY][startX]) && currentPlayer == 1 || islower(board[startY][startX]) && currentPlayer == 2)
        {
                 if (movePiece(startFile, startRank, endFile, endRank,&currentPlayer))
                 {

                  
                  pawnUpgration(endY,endX);
                  

                  printBoard();
                  printf("Player 1 points : %d\n",point1);
                  printf("Player 2 points : %d\n",point2);

                  if (isCheckmate(currentPlayer))
                  {
    printf("Checkmate! Player %d loses. Player %d wins!\n", currentPlayer, (currentPlayer == 1) ? 2 : 1);
    gameRunning = false; // End the game
    end();
    break;
}


                  switchPlayer(&currentPlayer);
                 } 
                 
                 else
                 {

                // Clear the screen before printing the board each time
                /* #ifdef _WIN32
                 system("cls"); // For Windows
                  #endif
                  printf("Simple Chess Program\n");
                 printBoard();*/

            printf("Invalid move. Try again.\n");
        }
        //currentPlayer = (currentPlayer == 1) ? 2 : 1;

        }


       else printf("Not your turn\n");
    }

      
        

    return 0;
}





void points(int endX ,int endY  ,int *point1,int *point2)
{

   /* 
    int point1=0;
    int point2=0;
   */

    //if(isupper(board[endY][endX]))

    char piece = board[endY][endX] ;

    switch ( piece)
    {
    case 'p':
            *point1 = *point1 + 1;
        break;

    case 'r':
            *point1 = *point1 + 5;
        break;    

    case 'b':
            *point1 = *point1 + 3;
        break;

    case 'n':
            *point1 = *point1 + 3;
        break;       

    case 'q':
            *point1 = *point1 + 9;
        break;


    case 'P':
            *point2 = *point2 + 1;
        break;

    case 'R':
            *point2 = *point2 + 5;
        break;    

    case 'B':
            *point2 = *point2 + 3;
        break;

    case 'N':
            *point2 = *point2 + 3;
        break;       

    case 'Q':
            *point2 = *point2 + 9;
        break;    

    case ' ':
            *point2 = *point2;

            *point1 = *point1;
           
        break;   
              
    
   

        
    }
}

void declare(int *point1 , int *point2)
{

    if(*point1==*point2)
    {
        printf("TIE\n");
    }


    else
    {
        int winner = *point1 > *point2 ? 1 : 2 ;
    


    printf("WINNER IS %d\n",winner);
}

end();
}

void welcome()
{

printf("  /***                                                               \n");
printf(" *     _    _  _____  _      _____  _____ ___  ___ _____             \n");
printf(" *    | |  | ||  ___|| |    /  __ \|  _  ||  \/  ||  ___|            \n");
printf(" *    | |  | || |__  | |    | /  \/| | | || .  . || |__              \n");
printf(" *    | |/\| ||  __| | |    | |    | | | || |\/| ||  __|             \n");
printf(" *    \  /\  /| |___ | |____| \__/\\ \_/ /| |  | || |___             \n");
printf(" *     \/  \/ \____/ \_____/ \____/ \___/ \_|  |_/\____/             \n");
printf(" *                                                                   \n");
printf(" *                                                                   \n");
printf(" */                                                                  \n");
printf("                                                                     \n");
printf("                                                                     \n");
                                     
}


void end()
{
printf("    /***                                              \n                  ");
printf(" *     _____  _   _   ___   _   _  _   __ _____       \n                   ");
printf(" *    |_   _|| | | | / _ \ | \ | || | / //  ___|      \n                    ");
printf(" *      | |  | |_| |/ /_\ \|  \| || |/ / \ `--.        \n                      ");
printf(" *      | |  |  _  ||  _  || . ` ||    \  `--. \         \n");
printf(" *      | |  | | | || | | || |\  || |\  \/\__/ /       \n  ");
printf(" *      \_/  \_| |_/\_| |_/\_| \_/\_| \_/\____/          \n");
printf(" *                                                       \n");
printf(" *                                                       \n");
printf(" *    ______  _____ ______                               \n");
printf(" *    |  ___||  _  || ___ \                              \n");
printf(" *    | |_   | | | || |_/ /                              \n");
printf(" *    |  _|  | | | ||    /                               \n");
printf(" *    | |    \ \_/ /| |\ \                               \n");
printf(" *    \_|     \___/ \_| \_|                              \n");
printf(" *                                                       \n");
printf(" *                                                       \n");
printf(" *    ______  _       ___  __   __ _____  _   _  _____   \n");
printf(" *    | ___ \| |     / _ \ \ \ / /|_   _|| \ | ||  __ \  \n");
printf(" *    | |_/ /| |    / /_\ \ \ V /   | |  |  \| || |  \/  \n");
printf(" *    |  __/ | |    |  _  |  \ /    | |  | . ` || | __   \n");
printf(" *    | |    | |____| | | |  | |   _| |_ | |\  || |_\ \  \n");
printf(" *    \_|    \_____/\_| |_/  \_/   \___/ \_| \_/ \____/  \n");
printf(" *                                                       \n");
printf(" *                                                       \n");
printf(" *     _____  _   _ ______                               \n");
printf(" *    |  ___|| \ | ||  _  \                              \n");
printf(" *    | |__  |  \| || | | |                              \n");
printf(" *    |  __| | . ` || | | |                              \n");
printf(" *    | |___ | |\  || |/ /                               \n");
printf(" *    \____/ \_| \_/|___/                                \n");
printf(" *                                                       \n");
printf(" *                                                       \n");
printf(" */                                                        \n      ");

}
