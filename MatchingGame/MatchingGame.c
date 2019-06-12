// hide warning message
#pragma diag_suppress 1, 177, 1295

/* ------ Include ------ */
#include <RTL.h>
#include <LPC17xx.H>
#include <stdlib.h>
#include "LPC1768_utility.h"
#include "GLCD.h"
#include "Keypad.h"

/* ----- Definition ----- */
int Count;
int nCardindex[2];
int match_count;

BOOL card_matching(uint8_t Keypad_Value);
void GamePan(BOOL Start);
void InitGame();
char NumToWord(int x);

/* ----- Structure ----- */
typedef enum _CARD_STATE {
   OPEN, CLOSE, MATCH
} CARD_STATE;

typedef struct _CARD_INFO {
   CARD_STATE State;
   int shape;
   int nX, nY;
} CARD_INFO;

CARD_INFO Card[16];

/* ----- Function ----- */
BOOL card_matching(uint8_t Keypad_Value) {
   int i;
   for (i = 0; i < 16; i++) {
      
      if (Keypad_Value == i) {
         if (Card[i].State == CLOSE) {
            Card[i].State = OPEN;
             
            nCardindex[Count%2] = i;
            Count++;
         } else {   // if (Card[i].State == MATCH || Card[i].State == OPEN)
            return __FALSE;
         }
      }
}
      if (Count % 2 == 0) {
         if (Card[nCardindex[0]].shape == Card[nCardindex[1]].shape) {
            Card[nCardindex[0]].State = MATCH;
            Card[nCardindex[1]].State = MATCH;
            match_count += 2;   
         } else {
            Delay(200000000);
            Card[nCardindex[0]].State = CLOSE;
            Card[nCardindex[1]].State = CLOSE;
         }
      }

    if (match_count == 16) {
         return __TRUE;
		}
		 return __FALSE;
}

void GamePan(BOOL Start) {
   int x;
   
   for (x = 0; x < 16; x++) {
      if (Start == __TRUE || Card[x].State == OPEN) {
         GLCD_displayChar(Card[x].nX , Card[x].nY, NumToWord(Card[x].shape));
         
      } else if (Card[x].State == CLOSE) {
         GLCD_displayChar(Card[x].nX , Card[x].nY,'?');
         
      } else if (Card[x].State == MATCH) {
         GLCD_displayChar(Card[x].nX , Card[x].nY, NumToWord(Card[x].shape));
      }
   }
}

void InitGame() {
   int i, j, k; 
   int x = 0;
   int init_X = 33;
   int init_Y = 28;
   Count = 0;
   match_count = 0;
   
   GLCD_displayStringLn(Line0, " +-++-++-++-++-++-+ ");
   GLCD_displayStringLn(Line1, " | || || || || || | ");
   GLCD_displayStringLn(Line2, " +-++-++-++-++-++-+ ");
   GLCD_displayStringLn(Line3, " +-++-++-++-++-++-+ ");
   GLCD_displayStringLn(Line4, " | || || || || || | ");
   GLCD_displayStringLn(Line5, " +-++-++-++-++-++-+ ");
   GLCD_displayStringLn(Line6, " +-++-++-++-+  MP  ");
   GLCD_displayStringLn(Line7, " | || || || | LOVE");
   GLCD_displayStringLn(Line8, " +-++-++-++-+  S2");
   GLCD_displayStringLn(Line9, " 0");
   // x 48 y 70
    //initalize position X ,Y
for(k = 0 ; k < 16 ; k++){
      Card[k].shape = 0;
   // x = 48 , y = 70
     if( (k !=0) && (k % 6 == 0) ){
         init_Y=init_Y+70;
         init_X = 33;//inital x_position again
      } else if (k !=0 && (k%6 > 0)){
            init_X =init_X +48 ;
         }
       
      Card[k].nX = init_X;
      Card[k].nY=init_Y;
   }

   for (i = 0; i < 8; i++) {
      for (j = 0; j < 2; j++) {
         do {
            x = rand()%16;
					 
         } while (Card[x].shape != 0);//to protect duplication
				 //printf("x=%d",x);

         Card[x].shape = i;
         Card[x].State = CLOSE;
      }
   }
   
   GamePan(__TRUE);
   Delay(5000000000);
   GamePan(__FALSE);
}

char NumToWord(int x) {
   switch (Card[x].shape) {
      case 0:
         return '!';
      case 1:
         return '@';
      case 2:
         return '#';
      case 3:
         return '$';
      case 4:            
         return '%';
      case 5:
         return '*';
      case 6:
         return '+';
      case 7:
         return '=';
      default:
         return __FALSE;
   }
}

int main(void) {
   SystemInit();
   
   GLCD_init();
   
   EXT_IO_init();
   Keypad_DIR_Input();
   
   GPIO_SetDir(GPIO_PORT_2, (1<<10), INPUT);
   
   GLCD_clear(White);
   GLCD_setBackColor(White);
   GLCD_setTextColor(Black);
   
   GLCD_displayStringLn(Line3, "   MATCHING  GAME   ");
   GLCD_displayStringLn(Line4, "       Team 6       ");
   
   GLCD_displayStringLn(Line6, " Press INT to START ");
   uint8_t Keypad_Value;
   
   while(1) {
      uint32_t Button_Status = 0;
      Button_Status = (GPIO_ReadValue(GPIO_PORT_2) & (1<<10));
      if(Button_Status == 0) {
        
            InitGame();
            for (;;) {
                     Keypad_Value = Keypad('C');//키보드 인터럽트.....
               card_matching(Keypad_Value);
              GamePan(__FALSE);
              
                     
                     
               if (match_count == 16) 
                  break;
            
         }
                  if (match_count == 16) 
                  break;
      }
   }
    
    GLCD_clear(White);
                  GLCD_setBackColor(White);
                  GLCD_setTextColor(Black);
                  
                  GLCD_displayStringLn(Line2, " GAME CLEAR! ");
                  
                  GLCD_displayStringLn(Line4, " count:");
                  GLCD_displayStringLn(Line5, " time: ");
                  
                  GLCD_displayStringLn(Line7, " Press Reset ");
}