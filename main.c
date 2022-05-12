#include "game.h"

void menu(){
  printf("*********************\n");
  printf("***** 1.Play ********\n");
  printf("***** 0.Exit ********\n");  
  printf("*********************\n");
}

void game(){
    printf("MineSweeper\n");
    char mine[ROWS][COLS]={ 0 };//11*11
    char show[ROWS][COLS]={ 0 };
    InitBoard(mine,ROWS,COLS,'0');
    InitBoard(show,ROWS,COLS,'*');
    //display
    //DisplayBoard(mine,ROW,COL);
    DisplayBoard(show,ROW,COL);
    SetMine(mine,ROW,COL);
    //DisplayBoard(mine,ROW,COL);
    FindMine(mine,show,ROW,COL);
}

void test(){
  int input=0;
  srand((unsigned int)time(NULL));
  do{ 
    menu();
    printf("make a choice：");
    scanf("%d",&input);
    switch(input){
      case 1:
          game();
          break;
      case 0:
          printf("Quit Game\n");
          break;
      default:
          printf("Error, please input valid value\n");
          break;  
    }
  }while(input);
}

////////////////////////////////////////

int main() {
  test();
  return 0;
}
