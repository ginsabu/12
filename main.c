#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAXLENGTH   30
#define MAX_DIE     6
#define N_PLAYER    3

#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2

char player_name[N_PLAYER][MAXLENGTH];
int player_position[N_PLAYER];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAXLENGTH] = {"LIVE", "DIE", "END"};

int getAlivePlayer(void)
{
   int i;
   int cnt=0;
   for(i=0;i<N_PLAYER;i++)
   {
       if(player_status[i] == PLAYERSTATUS_END)
         cnt++;
   }
   return cnt;
}
    
int getWinner(void)
{
    int i;
    int winner=0;
    int max_coin=-1;
       
    for(i=0;i<N_PLAYER;i++)
    {
         if(player_coin[i]>max_coin)
         {
              max_coin = player_coin[i];
              winner = i;                           
         }              
    }    
    return winner;
}
    
void printPlayerPosition(int player) 
{
     int i;
     for(i=0;i<N_BOARD;i++)
     {
          printf("|");
          if(i==player_position[player])
               printf("%c", player_name[player][0]);
          else
          {
              if(board_getBoardStatus(i) == BOARDSTATUS_OK)
                  printf(" ");
              else
                  printf("X");
              
          }   
      }
      printf("|\n"); 
}

void printPlayerStatus(void)
{
     int i;
     printf("player status -----------\n");
     for(i=0;i<N_PLAYER;i++)
     {
        printf("%s : pos %i, coin %i, status %s\n",
                   player_name[i],
                   player_position[i],
                   player_coin[i],
                   player_statusString[player_status[i]]);//
        printPlayerPosition(i);
     }

     printf("--------------------------\n");
}

void initPlayer(void)
{
     int i;
     for(i=0;i<N_PLAYER;i++)    
     {
        player_position[i] = 0;
        player_coin[i] = 0;
        player_status[i]=PLAYERSTATUS_LIVE;
        printf("Player %i's name: ", i);
        scanf("%s", player_name[i]);
        fflush(stdin);
     }
}

int gameEnd(void)
{
    int i;
    int flag_end = 1;
    
    //if all the players are died? 
    for(i=0;i<N_PLAYER;i++)
    {
         if(player_status[i] == PLAYERSTATUS_LIVE)
         {
             flag_end = 0;
         }
    }
    
    return flag_end;
}

void checkDie(void)
{
         int i;
         
         for(i=0;i<N_PLAYER;i++)
         {
            if(board_getBoardStatus(player_position[i])== BOARDSTATUS_NOK)
              {
               player_status[i] = PLAYERSTATUS_DIE;
               printf("So Sad! %s died at position %i\n", player_name[i], player_position[i]);
              } 
         }
}
        
int rolldie(void)
{
    return rand()%MAX_DIE +1;
}

int main(int argc, char *argv[])
{
    int dum;
    int turn;
    
    srand((unsigned)(time(NULL)) );
    
    //opening
	printf("-------------------------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("                                 SHARK ISLAND GAME                             \n");
	printf("                                       START                                   \n\n\n");
	printf("                                 ,-\n");
    printf("                               ,'::|\n");
    printf("                              /::::|\n");
    printf("                            ,'::::o\\                                      _..\n");
    printf("         ____........-------,..::?88b                                  ,-' /\n");
    printf(" _.--\"\"\"\". . . .      .   .  .  .  \"\"`-._                           ,-' .;'\n");
    printf("<. - :::::o......  ...   . . .. . .  .  .\"\"--._                  ,-'. .;'\n");
    printf(" `-._  ` `\":`:`:`::||||:::::::::::::::::.:. .  \"\"--._ ,'|     ,-'.  .;'\n");
    printf("     \"\"\"_=--       //'doo.. ````:`:`::::::::::.:.:.:. .`-`._-'.   .;'\n");
    printf("         \"\"--.__     P(       \\               ` ``:`:``:::: .   .;'\n");
    printf("                \"\\\"\"--.:-.     `.                             .:/\n");
    printf("                  \\. /    `-._   `.\"\"-----.,-..::(--\"\".\\\"\"`.  `:\\\n");
    printf("                   `P         `-._ \\          `-:\\          `. `:\\\n");
    printf("                                   \"\"            \"            `-._)  \n\n\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-------------------------------------------------------------------------------\n\n");
    //step1. initialization(player name, variables)
    board_initBoard();
    //player init
    initPlayer();
    
    //step2. turn play (do-while)
    turn = 0;
 
    do{
          int die_result;
          
          if(player_status[turn] != PLAYERSTATUS_LIVE)
          {
             turn = (turn +1)%N_PLAYER;
             continue;                        
          }
         //2-1. status printing
         board_printBoardStatus();
         // player status(????)
         printPlayerStatus();
   
   
    
         //2-2. roll die
         printf("%s turn!!", player_name[turn]);
         printf("Press any key to roll a die!\n");
         scanf("%d",&dum);
         fflush(stdin);
         die_result = rolldie();//player turn
    
         //2-3. move(result)//player turn
         player_position[turn] += die_result;
         //coinResult = board_getBoardCoin(pos);
         if(player_position[turn]>=N_BOARD)
         {
              player_position[turn] = N_BOARD-1;
              player_status[turn] = PLAYERSTATUS_END;
         }
         printf("Die result : %i, %s moved to %i\n", die_result, player_name[turn], player_position[turn]);
    
         player_coin[turn] += board_getBoardCoin(player_position[turn]);
         printf("Lucky! %s got %i coins\n" , player_name[turn], player_coin[turn]);////////////////////////
        //2-4. change turn, shark move
        //change turn
        turn = (turn + 1)%N_PLAYER;
            
        //shark move
        if(turn == 0)
        {
             int shark_pos = board_stepShark();
             printf("Shark moved to %i\n", shark_pos);
              
             checkDie();
        }
  }while(gameEnd() == 0);
  
    //step3. game end(winner printing)
    
    printf("\n\n\nGAME END!!");
    printf("\n\n%i players are alive!! The winner is %s!!", getAlivePlayer(), player_name[getWinner()]);

    //ending
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("                                 SHARK ISLAND GAME                             \n");
	printf("                                     THE END                                   \n\n\n");
	printf("      ,|\n");
    printf("     / ;\n");
    printf("    /  \\\n");
    printf("   : ,'(\n");
    printf("   |( `.\\\n");
    printf("   : \\  `\\       \\\n");
    printf("    \\ `.         | `.\n");
    printf("     \\  `-._     ;   \\\n");
    printf("      \\     ``-.'.. _ `._\n");
    printf("       `. `-.            ```-...__\n");
    printf("        .'`.        --..          ``-..____\n");
    printf("      ,'.-'`,_-._            ((((   ._``,_<               `-\\,-'`-'      ~\n");
    printf("_________,'       `' `/\n");
    printf("                                                  ~~\n");
    printf("        ~~                    ~             ~  >\n\n\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-------------------------------------------------------------------------------\n\n");
	
    
    system("PAUSE");	
    return 0;
}


////??? ??? ?? ??? ???? ??? ????
////?????? ???????? ????. 