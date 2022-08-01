#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void initializeBoard(); //initialize the board //
void drawBoard(); //draw it on the window //
void player_1_move(); //check if player 1 made a valid move and update the board
void player_2_move(); //check if player 2 made a valid move and update the board

//AI functions
void pickTile(); //picks a tile based on available information
void computerTurn(); //checks if the computer is going first or second

char* isThereaWinningMove(); //checks if the user is abou to win
char tempcT;

int checkWin(); //checks if either player has won at the end of every turn and if so ends the game and declares a winner //

char board[3][3]; //3x3 tic tac toe board

int main(){
	
	int win = 0;
	
	printf("==============");
	printf("\n TIC TAC TOE \n");
	printf("==============\n");
	printf("The World's Number 1 Multiplayer Game! \n\n");
	
	initializeBoard();
	
	//let's the user pick the gamemode
	int x;
	
	printf("Press 1 to PLAY AGAINST A HUMAN or 0 to PLAY AGAINST AI: \n");
	scanf("%d", &x);
	
	while(x!=0 && x!=1){
		printf("Invalid input. Press 1 to PLAY AGAINST A HUMAN or 0 to PLAY AGAINST AI: ");
		scanf("%d", &x);
	}
	if(x==1){ //pvp
		do{
    	    drawBoard();
    	    printf("\n\n");
		
    		player_1_move(); //player 1 (X) moves
    		drawBoard(); //update the board with each move
	    	win=checkWin(); //did player 1 win?
    		if(win==1){
	    		printf("\nPlayer 1 has won!");
    			break;
	    	}
		    
		    printf("\n\n");
	    	player_2_move(); //player 2 (O) moves
	    	drawBoard(); //update the board with each move
	    	win=checkWin(); //did player 2 win?
	    	if(win==1){
	    		printf("\nPlayer 2 has won!");
	    		break;
	    	}
	    }while(1);
	}
	else{ //pvc
		computerTurn();
		if(tempcT == 'O'){ //if the player is going first
			do{
				srand( (unsigned int) time(NULL) ); //initialize random seed
			    drawBoard();
    	        printf("\n\n");
    	    
    	        player_1_move(); //user (X) moves first
    		    drawBoard(); //update the board with each move
	    	    win=checkWin(); //did player 1 win?
    		    if(win==1){
	    		    printf("\nPlayer has won!");
    			    break;
	    	    }
	    	    //computer turn
	    	    printf("\n\n");
	    	    pickTile(); //picks available tile
	    	    drawBoard();
				win=checkWin();
	    	    if(win == 1){
	    	    	printf("\nI win!");
	    	    	break;
				}
	        }while(1);
		}
		else{ //if the computer goes first
		    do{
		    	
	    	    //computer turn
	    	    srand( (unsigned int) time(NULL) ); //initialize random seed
	    	    printf("\n\n");
	    	    pickTile(); //picks available tile
	    	    drawBoard();
	    	    win=checkWin();
	    	    if(win == 1){
	    	    	printf("\nI win!");
	    	    	break;
				}
				
				//player turn
		    	drawBoard();
    	        printf("\n\n");
    	    
    	        player_1_move(); //user (X) moves first
    		    drawBoard(); //update the board with each move
	    	    win=checkWin(); //did player 1 win?
    		    if(win==1){
	    		    printf("\nPlayer has won!");
    			    break;
	    	    }
			}while(1);
		}
	}
	return 0;
}

//initialize the board
void initializeBoard(){
	
	int i, j;
	
	for(i=0; i<=2; i++){
		for(j=0; j<=2; j++){
			board[i][j]= ' ';
		}
	}
	
}

//draws the board on the window
void drawBoard(){
	int t;
	
	for(t=0; t<=2; t++){
		printf(" %c | %c | %c ", board[t][0], board[t][1], board[t][2]);
		if(t!=2){
			printf("\n---|---|---\n");
		}
	}
	printf("\n");
}

//checks if there is a winner at the end of every turn
int checkWin(){
	
	int i;
	
	//checks rows
	for(i=0; i<=2; i++){
		if(board[i][0]==board[i][1] && board[i][0]==board[i][2] && board[i][0]!= ' '){
			return 1;
		}
	}
	
	//checks columns
	for(i=0; i<=2; i++){
		if(board[0][i]==board[1][i] && board[0][i]==board[2][i] && board[0][i]!= ' '){
			return 1;
		}
	}
	
	//checks diagonals from top left to bottom right
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!= ' '){
		return 1;
	}
	
	//checks diagonals from bottom left to top right
	if(board[2][0]==board[1][1] && board[1][1]==board[0][2] && board [2][0]!= ' '){
		return 1;
	}
	
	return 0;
}

//player 1 (X) move
void player_1_move(){
	
	int x, y;
	
	//player 1 picks coordinates on the board
	printf("Player 1, please pick a row (1-3): ");
	scanf("%d", &x);
	printf("Now pick a column (1-3): ");
	scanf("%d", &y);
	
	x--, y--;
	
	//check if it's a valid tile
	while(1){
		if(x<0 || x>2){
			if(y<0 || y>2){
				printf("Invalid tile, please enter a valid tile (same order as before, 1-3): ");
				scanf("%d%d", &x, &y);
				x--, y--;
			}
			else{
				printf("Invalid row, please try again (1-3): ");
				scanf("%d", &x);
				x--;
			}
		}
		else if(y<0 || y>2){
			printf("Invalid column, please try again (1-3): ");
			scanf("%d", &y);
			y--;
		}
		else{
			break;
		}
	}
	
	//check if the tile is free
	while(board[x][y]=='O' || board[x][y]=='X'){
		printf("Invalid move, please enter valid coordinates (same order as before, 1-3): ");
		scanf("%d%d", &x, &y);
		x--, y--;
	}
	
	board[x][y]='X';
}

//player 2 (O) move
void player_2_move(){
	
	int x, y;

    //player 2 picks a tile
	printf("Player 2, please pick a row (1-3): ");
	scanf("%d", &x);
	printf("Now pick a column (1-3): ");
	scanf("%d", &y);
	x--, y--; 

	//check if it's a valid tile
	while(1){
		if(x<0 || x>2){
			if(y<0 || y>2){
				printf("Invalid tile, please enter a valid tile (same order as before, 1-3): ");
				scanf("%d%d", &x, &y);
				x--, y--;
			}
			else{
				printf("Invalid row, please try again (1-3): ");
				scanf("%d", &x);
				x--;
			}
		}
		else if(y<0 || y>2){
			printf("Invalid column, please try again (1-3): ");
			scanf("%d", &y);
			y--;
		}
		else{
			break;
		}
	}
	
	//check if the tile is free
	while(board[x][y]=='O' || board[x][y]=='X'){
		printf("Invalid move, please enter valid coordinates (same order as before, 1-3): ");
		scanf("%d%d", &x, &y);
		x--, y--;
	}
	
	board[x][y]='O';
}

//AI functions

//checks if the computer is going first or second
void computerTurn(){
	
	int x;
	
	printf("Press 1 if you'd like to GO FIRST and 0 if you'd like to GO SECOND: ");
	scanf("%d", &x);
	while(x!=0 && x!=1){
		printf("Invalid input. Press 1 if you'd like to GO FIRST and 0 if you'd like to GO SECOND: ");
		scanf("%d", &x);
	}
	if(x==1){
		printf("OK, the player is going first.\n\n");
		tempcT = 'O';
	}
	else{
		printf("OK, I'm going first.\n\n");
		tempcT = 'X';
	}
}

//if there is a winning move available on the AI's turn
char* isThereaWinningMove(){
	int i;
	
	//checks rows
	for(i=0; i<=2; i++){
		if(board[i][0]==board[i][1] && board[i][0] != ' ' && board[i][2] == ' '){
			return &board[i][2];
		}
	}
	for(i=0; i<=2; i++){
		if(board[i][0]==board[i][2] && board[i][0] != ' ' && board[i][1] == ' '){ 
			return &board[i][1];
		}
	}
	for(i=0; i<=2; i++){
		if(board[i][1]==board[i][2] && board[i][1] != ' ' && board[i][0] == ' '){
			return &board[i][0];
		}
	}
	
	//checks columns
	for(i=0; i<=2; i++){
		if(board[0][i]==board[2][i] && board[0][i] != ' ' && board[1][i] == ' '){
			return &board[1][i];
		}
	}
	for(i=0; i<=2; i++){
		if(board[0][i]==board[1][i] && board[0][i] != ' ' && board[2][i] == ' '){
			return &board[2][i];
		}
	}
	for(i=0; i<=2; i++){
		if(board[1][i]==board[2][i] && board[1][i] != ' ' && board[0][i] == ' '){
			return &board[0][i];
		}
	}
	
	//checks diagonals from top left to bottom right
	if(board[1][1]==board[2][2] && board[1][1] != ' ' && board[0][0] == ' '){
		return &board[0][0];
	}
	if(board[0][0]==board[2][2] && board[0][0] != ' ' && board[1][1] == ' '){
		return &board[1][1];
	}
	if(board[0][0]==board[1][1] && board[0][0] != ' ' && board[2][2] == ' '){
		return &board[2][2];
    }
	//checks diagonals from bottom left to top right
	if(board[1][1]==board[0][2] && board[1][1] != ' ' && board [2][0] == ' '){
		return &board[2][0];
	}
	if(board[2][0]==board[1][1] && board[1][1] != ' ' && board [0][2] ==' '){
		return &board[0][2];
	}
	if(board[2][0]==board[0][2] && board[0][2] != ' ' && board [1][1] == ' '){
		return &board[1][1];
	}
	return 0;
}

//picks a tile based on available information
void pickTile(){
	int rndX, rndY;
	char *p = isThereaWinningMove();
	
	//did the computer detect a winning move?
	if(p != 0){
		*p = tempcT;
	}
	
	//if not, pick a random available tile
	else{
		while(1){
	    	rndX = rand()%3;
	    	rndY = rand()%3;
	    	
	    	if(board[rndX][rndY] == ' '){
	    		board[rndX][rndY] = tempcT;
	    		break;
			}
		}
	}
}
