#include "board.h"

#define N_COINPOS             12
#define MAX_COIN               4
#define MAX_SHARKSTEP          6
#define SHARK_INITPOS         -4

static int board_status[N_BOARD];
static int board_coin[N_BOARD];
static int shark_position;

int board_stepShark(void)
{
    int step = rand()%MAX_SHARKSTEP +1;
    int i;
    
    for(i=0;i<step;i++)
    {
     int posIdx = shark_position + i +1;// 
     if(posIdx>=0)////보드판 안에 있을 때 파손 
       board_status[posIdx] = BOARDSTATUS_NOK;
    }
    shark_position += step;
}

void board_printBoardStatus(void)
{
     int i;
     
     printf("-------------------------BOARD STATUS---------------------------\n");
     for(i=0;i<N_BOARD;i++)
     {
                           printf("|");
                           if(board_status[i] == BOARDSTATUS_NOK)
                               printf("X");
                               
                           else
                               printf("O");
     }
     printf("|\n");
     printf("----------------------------------------------------------------\n");
}

int board_getBoardStatus(int pos)
{
    return board_status[pos];
}

int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];
    board_coin[pos] = 0;
    return coin;
}

void board_initBoard(void)
{
    int i; 
    
    shark_position = SHARK_INITPOS;
    //initialize arrays
    for(i=0;i<N_BOARD;i++)
    {    
         board_status[i] = BOARDSTATUS_OK;
         board_coin[i] = 0;
    }    
    //alllocate coins
    for(i=0;i<N_COINPOS;i++)
    {
         int flag_allocated=0;
         do{
             int coinpos = rand()%N_BOARD;
             if(board_coin[coinpos]==0)
             {
                  board_coin[coinpos] = rand()%MAX_COIN + 1;
                  flag_allocated = 1;
             } 
         }while(flag_allocated == 0);//할당이 안 되어있으면 칸에 코인 할당 
    }
}