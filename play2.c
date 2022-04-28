#include "stdio.h"
#include "stdlib.h"

#define SYMBOL_FOR_EMPTY ' '
#define SYMBOL_FOR_CROSS 'X'
#define SYMBOL_FOR_ZERO 'O'

int current_turn = 1;
//impair: joueur 1, pair: joueur 2 ou bot

struct Position {
     int row;
     int col;
};




void init_board(int height, int width, char board[height][width]); //5pt
int is_valid_board(int height, int width); //5pt
int is_valid_game(int n_symbols2win, int height, int width); //5pt
void visualize_board(int height, int width, char board[height][width]); //10pt
int is_valid_pos( struct Position pos, int height, int width, char board[height][width]); //5pt
int did_player_win(struct Position pos, int n_symbols2win, int height, int width, char board[height][width]); //15 pt
struct Position get_bot_pos(int height, int width, char board[height][width]); //10pt
struct Position step(int height, int width, char board[height][width], int play_with_pc); //15pt
int is_game_winnable(int n_symbols2win, int height, int width, char board[height][width]);//15pt
void play();//15pt

int main(){
     play();
     return 0;
}

//start: play
void play(){
     
     char play_bot;
     int play_with_pc;
     int height, width, n_symbols2win, end=0;
     
     play_with_pc=-1;
     char respons='y';
     
     
     do {
          printf("Please input the height and the width of the board:\n");
     scanf("%d %d",&height, &width);
     }
     while(is_valid_board(height, width)==0);
     char board[height][width];


     do{
          printf("Please input the number of consecutive symbols in a row to win:\n");
     scanf("%d",&n_symbols2win );
     }
     while(is_valid_game(n_symbols2win, height, width)==0);
     do{

     
     printf("Do you want to play with a bot? Write 'y' for yes and 'n' for no:\n");
     
     scanf(" %c", &play_bot);
     if (play_bot=='y'){
          play_with_pc=1;
     }
     else if (play_bot=='n'){
          play_with_pc=0;
     }}
     while (play_with_pc==-1);

     
     do{
     init_board(height, width,board);
     visualize_board(height, width, board);
     struct Position pos;
     current_turn=1;
          end=0;
     
     do {
          do{
               pos= step(height, width, board, play_with_pc);
               if(is_valid_pos(pos,height,width,board)==0){
                    printf("Invalid input!\nDo you want to forfeit the game? Write 'y' for yes and 'n' for no:\n");
                    char respons='y';
                    scanf(" %c", &respons);
                    if(respons=='y'&& current_turn % 2==0){
                         printf("Congratulations! Player #1 won!\n");
                         end=2;
                         
                         
                    }
                    else if(respons=='y'&& current_turn % 2!=0){
                         printf("Congratulations! Player #2 won!\n");
                         end=1;
                         
                         
                    }
                    
               }
               else if(is_valid_pos(pos,height,width,board)==-1){
                    printf("Wrong input! The cell is not empty!\n");
               }
          }
          while(is_valid_pos(pos,height,width,board)!=1 && end==0);
          
          
          if(current_turn % 2==0){
               board[pos.row][pos.col]=SYMBOL_FOR_ZERO;
          }
          else {
               board[pos.row][pos.col]=SYMBOL_FOR_CROSS;}
          
          if (end==0){
               visualize_board(height, width, board);}
          
          current_turn++;
     }
     while (did_player_win(pos, n_symbols2win, height, width, board)!=1 && is_game_winnable(n_symbols2win, height, width, board)==1 && end==0);


     if (did_player_win(pos, n_symbols2win, height, width, board)==1){
          if (board[pos.row][pos.col]==SYMBOL_FOR_CROSS ){
               printf("Congratulations! Player #1 won!\n");
          }
          else {
               printf("Congratulations! Player #2 won!\n");
          }
     }
     else if (is_game_winnable(n_symbols2win, height, width, board)==0){
          printf("Thank you for participation, it is a tie!\n");
     }


     
     printf("Do you want to play again? Write 'y' for yes and 'n' for no:\n");
     scanf(" %c", &respons);
} while(respons=='y');
     

}
//end: play





//start: init_board
void init_board(int height, int width, char board[height][width]) {
     for(int i=0; i<height;i++){
          for (int j=0; j<width; j++){
               board[i][j]=SYMBOL_FOR_EMPTY;
          }
     }
     // chaque case tu tableau initialisee comme vide
}
//end: init_board

//start: is_valid_board
int is_valid_board(int height, int width){
     if(height<3|| width<3){
          printf("Wrong input!\n");
          return 0;}
     else {
          return 1;
     }
     //largeur et hauteur du tableau doit etre superieur ou egale a 3
     }

//end: is_valid_board

//start: is_valid_game
int is_valid_game(int n_symbols2win, int height, int width){
     if(n_symbols2win>2 && n_symbols2win<=height && n_symbols2win<=width){
          return 1;
     }
     else {
          printf("Wrong input!\n");
          return 0;
     }
     // le nombre de symboles consecutifs pour gagner doir etre superieur a 2, et inferieur ou egale a la taille du tableau
}
//end: is_valid_game

//start: visualize_board
void visualize_board(int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     
     printf(" ");
     //deux premiers espaces

     for(int i=1; i<=width;i++){
          printf(" %d", i);
     }
     printf("\n ");
     //enumeration des colonnes 

     for (int i=1; i<=height; i++){
          for (int j=1; j<=width; j++){
               printf("+-");}
               //ligne de +-

          printf("+\n%d",i);
          //dernier + de la ligne et saut de ligne avec numero de la nouvelle ligne

          for (int j=1; j<=width; j++){
               printf("|%c", board[i-1][j-1]);
          }
          //enumeration des valeurs du tableau separes par des |

          printf("|\n ");
          // dernier | de la ligne et saut de ligne
          }
     
     for (int j=1; j<=width; j++){
          printf("+-");}
          //ligne de +-

     printf("+\n");
     //dernier +


     //permet de montrer le tableau sur le terminal
}
//end: visualize_board

//start: is_valid_pos
int is_valid_pos(struct Position pos, int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     if (pos.row<0 || pos.col<0|| pos.row>=height || pos.col>=width){
          return 0;
     }
     else if(board[pos.row][pos.col]!=SYMBOL_FOR_EMPTY){
          return -1;
     }
     else {
          return 1;
     }
     
     }

//end: is_valid_pos

//start: did_player_win
int did_player_win(struct Position pos, int n_symbols2win,int height, int width, char board[height][width]) {

     /* TODO: Write your implementation of the function here */
char symbol;
     
     if(board[pos.row][pos.col]==SYMBOL_FOR_CROSS){
          symbol=SYMBOL_FOR_CROSS;
          }
     else {
          symbol=SYMBOL_FOR_ZERO;
     }
    // definition du symbole a rechercher

     int i, k;
     i=1;
     k=1;
     while (board[pos.row][pos.col-i]==symbol && pos.col-i >=0){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row][pos.col+i]==symbol && pos.col +i <width){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des lignes 

     i=k=1;
     while (board[pos.row-i][pos.col]==symbol && pos.row -i >=0){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row+i][pos.col]==symbol && pos.row +i <height){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des colonnes

     i=k=1;
     while (board[pos.row+i][pos.col-i]==symbol && pos.row +i <height && pos.col-i>=0){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row-i][pos.col+i]==symbol && pos.row-i>=0 && pos.col+i<width){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des diag haut bas

     i=k=1;
     while (board[pos.row-i][pos.col-i]==symbol && pos.row-i>=0 && pos.col-i>=0){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row+i][pos.col+i]==symbol && pos.row+i<height && pos.col +i<width){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification diagonale de bas a haut




     return 0;
     }
//end: did_player_win


//start: get_bot_pos
struct Position get_bot_pos(int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     struct Position pos_bot;
     do{
          pos_bot.row=rand() % height;
     pos_bot.col=rand() % width;

     }
     while(is_valid_pos(pos_bot, height, width, board)!=1);
     return pos_bot;
     // peermet de faire jouer le bot aleatoirement
}
//end: get_bot_pos

//start: step
struct Position step(int height, int width, char board[height][width], int play_with_pc) {
     /* TODO: Write your implementation of the function here */
     struct Position pos;
     pos.row=0;
     pos.col=0;
     int i;
if (current_turn % 2==0)
{
     i=2;
}
else {
     i=1;
}
printf("Player #%d's turn:\n", i);

     if (current_turn % 2==0 &&play_with_pc==1){
          //current turn pair: au joueur 2 ou au bot de jouer
          pos=get_bot_pos(height, width, board);
          }
          
     else{
          scanf("%d %d", &pos.row, &pos.col);
          pos.row--;
          pos.col--;
          }
     
     return pos;
     }

//end: step

//start: is_game_winnable
int is_game_winnable(int n_symbols2win, int height, int width, char board[height][width]) {
     char symbol;
     int i, k;


     for(int row=0; row<height; row++){
          for (int col=0; col<width;col++){
          symbol=board[row][col];
          i=1;
          k=1;
               while ((board[row][col-i]== SYMBOL_FOR_EMPTY || board[row][col-i]==symbol)&& col-i>=0) {
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while ((board[row][col+i]==SYMBOL_FOR_EMPTY||board[row][col+i]==symbol)&& col+i<width ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verifiaction ligne

          i=k=1;
     while ((board[row-i][col]== SYMBOL_FOR_EMPTY  || board[row-i][col]==symbol)&&(row-i>=0) ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while ((board[row+i][col]==SYMBOL_FOR_EMPTY||board[row+i][col]==symbol)&& (row+i<height)){
     
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification colonne

     i=k=1;
     while ((board[row+i][col-i]==SYMBOL_FOR_EMPTY||board[row+i][col-i]==symbol)&& row+i<height && col-i>=0 ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while ((board[row-i][col+i]==SYMBOL_FOR_EMPTY||board[row-i][col+i]==symbol) && row -i>=0 && col+i<width ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des diag haut bas

     i=k=1;
     while ((board[row-i][col-i]==SYMBOL_FOR_EMPTY||board[row-i][col-i]==symbol) && row-i>=0 && col-i>=0 ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while ((board[row+i][col+i]==SYMBOL_FOR_EMPTY||board[row+i][col+i]==symbol) && row+i<height && col+i<width ){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification diagonale de bas a haut


}}
return 0;
}
//end: is_game_winnable

//End of the script