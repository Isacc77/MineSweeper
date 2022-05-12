#include "game.h"

void InitBoard(char board[ROWS][COLS],int rows, int cols,char set){
  int i=0;
  int j=0;

  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
        board[i][j]=set;
    }
  }
}


void DisplayBoard(char board[ROWS][COLS],int row, int col){
  int i = 0;
  int j = 0;

  for(i=0;i<=col;i++){
    printf("%d ", i);
  }
  printf("\n");

  for(i=1;i<=row;i++){
    printf("%d ",i);
    for(j=1;j<=col;j++){
      printf("%c ",board[i][j]);
    }
    printf("\n");
  }
}


void SetMine(char board[ROWS][COLS],int row, int col)
{
  int count = EASY_COUNT;

  while(count){
      int x = rand()%row+1;
      int y = rand()%col+1;
      if(board[x][y]=='0'){
        board[x][y]='1';
        count--;
      }
  }
}

//'1'-'0'=1
//'3'-'0'=3
 int get_mine_count(char mine[ROWS][COLS], int x ,int y){
    return mine[x-1][y] +
    mine[x-1][y-1]+
    mine[x][y-1]+
    mine[x+1][y-1]+
    mine[x+1][y]+
    mine[x+1][y+1]+
    mine[x][y+1]+
    mine[x-1][y+1]-8*'0';
 }



void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row, int col){
  int x=0;
  int y=0;
  int win=0;
  //9*9-1=71;

  while(win<row*col-EASY_COUNT){
    printf("Please, input the location you wanne check\n");
    scanf("%d%d",&x,&y);  
    if(x>=1 && x<=row && y>=1 && y<= col){
        if(show[x][y] != '*'){
            printf("you already check this location, try another location\n");
               DisplayBoard(show, ROW, COL);
        }else{
        //valid value
        //1.mine
            if(mine[x][y]=='1'){
              printf("It's mine, you dead.\n");
              DisplayBoard(mine, row, col);
              break;
            }
            else {//not mine
                //check how many mine around the location you check
                int count = get_mine_count(mine,x,y);
                show[x][y]=count+'0';
                win++;
                expand(mine, x, y, show, &win); 
                DisplayBoard(show, row, col);
            }
          }
    }
    else{
        printf("Error, please input valid location: ");
    }
  }

  if(win==row*col-EASY_COUNT){
    printf("You win!\n");
    DisplayBoard(mine, row, col);
  }
}

//////////////////////
void expand(char mine[ROWS][COLS], int x, int y, char show[ROWS][COLS], int *p){
    int i = -1;
    int j = -1;
    for (i = -1; i < 2; i++){//bound
        for (j = -1; j < 2; j++){
            if (i != 0 || j != 0) {
                if (x + i >= 1 && x + i <= ROW && y + j >= 1 && y + j <= COL){
                    if (show[x + i][y + j] == '*'&&mine[x+i][y+j]!='1'){
                        int count = get_mine_count(mine, x + i, y + j);
                        if (count != 0){
                            show[x + i][y + j] = count + '0';
                            (*p)++;
                        }else{
                            show[x + i][y + j] = ' ';
                            (*p)++;
                            expand(mine, x + i, y + j, show, p);
                        }
                    }
                }
            }
        }
    }
}