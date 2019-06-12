#include <RTL.h>
#include <stdlib.h>
#include <LPC17xx.H>
#include "GLCD.h"
#include "Keypad.H"
#include "LPC1768_fnd.h"
#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

typedef enum _CARD_STATE {
	OPEN, CLOSE, MATCH
} CARD_STATE;

typedef struct _CARD_INFO {
	CARD_STATE State;
	int shape;
	int nX, nY;
} CARD_INFO;

CARD_INFO Card[16];
int Count;
int nCardindex[2];
int match_count;

BOOL card_matching() {
	uint8_t Keypad_Value = 0;
	Keypad_Value = Keypad('C');
	
	int i;
	for (i = 0; i < 16; i++) {
		
		if (Keypad_Value == i) {
			if (Card[i].State == CLOSE) {
				Card[i].State = OPEN;
				 
				nCardindex[Count%2] = i+1;
				Count++;
			} else {	// if (Card[i].State == MATCH || Card[i].State == OPEN)
				return 1;
			}
		}
		if (Count % 2 == 0) {
			if (Card[nCardindex[0]].shape == Card[nCardindex[1]].shape) {
				Card[nCardindex[0]].State = MATCH;
				Card[nCardindex[1]].State = MATCH;
				match_count += 2;	
			} else {
				Delay(2000);
				Card[nCardindex[0]].State = CLOSE;
				Card[nCardindex[1]].State = CLOSE;
			}
		}
//		if (match_count == 16) {
//			return true;
//		}
	}
	
	return __FALSE;
}

void GamePan(BOOL Start) {
	int x;
	
	for (x = 0; x < 16; x++) {
		if (Start == __TRUE || Card[x].State == OPEN) {
			// ? ?? NumToWord(x)
		} else if (Card[x].State == CLOSE) {
			// ? ?? x
		} else if (Card[x].State == MATCH) {
			// ? ?? NumToWord(x)
		}
	}
}

void InitGame() {
	int i, j, k;
	int x = 0;
	
	Count = 0;
	match_count = 0;
	
	GLCD_clear(White);
	
	GLCD_displayStringLn(Line0, " +-++-++-++-++-++-+ ");
	GLCD_displayStringLn(Line1, " | || || || || || | ");
	GLCD_displayStringLn(Line2, " +-++-++-++-++-++-+ ");
	GLCD_displayStringLn(Line3, " +-++-++-++-++-++-+ ");
	GLCD_displayStringLn(Line4, " | || || || || || | ");
	GLCD_displayStringLn(Line5, " +-++-++-++-++-++-+ ");
	GLCD_displayStringLn(Line6, " +-++-++-++-+");
	GLCD_displayStringLn(Line7, " | || || || | ");
	GLCD_displayStringLn(Line8, " +-++-++-++-+");
	GLCD_displayStringLn(Line9, " 0");

	for(k = 0 ; k < sizeof(Card) ; k++){
		Card[k].shape = 0;
	}

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 2; j++) {
			do {
				x = rand()%16;
			} while (Card[x].shape != 0);

			Card[x].shape = i;
			Card[x].State = CLOSE;
		}
	}
	
	GamePan(__TRUE);
	Delay(2000);
	GamePan(__FALSE);
}

char* NumToWord(int x) {
	switch (Card[x].shape) {
		case 0:
			return "!";
		case 1:
			return "@";
		case 2:
			return "#";
		case 3:
			return "$";
		case 4:				
			return "%";
		case 5:
			return "*";
		case 6:
			return "+";
		case 7:
			return "?";
		default:
			return __FALSE;
	}
}

int main(void) {
	SystemInit();
	EXT_IO_init();
	GLCD_init();
	EXTI_Init();

	GPIO_SetDir(GPIO_PORT_2, (1<<10), INPUT);
	
	GLCD_clear(White);
	GLCD_setBackColor(White);
	GLCD_setTextColor(Black);
	
	GLCD_displayStringLn(Line3, "   MATCHING  GAME   ");
	GLCD_displayStringLn(Line4, "       Team 6       ");
	
	GLCD_displayStringLn(Line6, " Press INT to START ");
	
	
}
