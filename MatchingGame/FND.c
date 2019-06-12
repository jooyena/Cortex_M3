/******************************************************************************
  * @file  FND.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   FND Control (StopWatch)
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/           
#include "LPC1768_fnd.h"
#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

/* Private variables ---------------------------------------------------------*/
uint8_t time_10m =0 ;
uint8_t time_1m =0 ;
uint8_t time_10s = 0;
uint8_t time_1s = 0;

uint8_t lap_time_10m =0 ;
uint8_t lap_time_1m =0 ;
uint8_t lap_time_10s = 0;
uint8_t lap_time_1s = 0;

/* Private function ---------------------------------------------------------*/
void TIMER0_Config(void);

/* Private struct ---------------------------------------------------------*/
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;


void TIMER0_IRQHandler(void)	// 1초에 한번 씩 진입
{
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); //TIM0 interrupt clear
	
	// 초 : 1의 자리 , 10의 자리 / 분 : 1의 자리, 10의 자리
	time_1s++;
	if(time_1s == 10)
	{
		time_10s++;
		time_1s=0;
	}
	if(time_10s == 6)
	{
		time_1m++;
		time_10s = 0;
	}
	if(time_1m == 10)
	{
		time_10m++;
		time_1m = 0;
	}	
	if(time_10m == 6)
	{
		time_10m =0 ;
		time_1m =0 ;
		time_10s = 0;
		time_1s = 0;
	}	
}

// INT 버튼을 누르면 진입
void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);	// Interrupt 정보를 클리어 하여 다시 대기 상태로 바꾼다.
	lap_time_10m = time_10m;	// 현재 시간 저장 
	lap_time_1m = time_1m;
	lap_time_1s = time_1s;
	lap_time_10s = time_10s;
}

void TIMER0_Config(void)
{
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;	//	us(microsecond) 기준으로 Prescale 설정
	TIM_ConfigStruct.PrescaleValue	= 100;	//	100us
	TIM_MatchConfigStruct.MatchChannel = 0;	//	0번 채널 사용
	TIM_MatchConfigStruct.IntOnMatch = ENABLE;	//	Timer가 일치할 때  Interrupt 발생 Enable
	TIM_MatchConfigStruct.ResetOnMatch = ENABLE;	//	Timer가 일치할 때  Reset Enable
	TIM_MatchConfigStruct.StopOnMatch = DISABLE;	//	Timer가 일치할 때 Timer Stop Disable
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;	//	Timer 일치할때 아무런 외부 출력 하지 않음 (외부로 출력하지 않기 때문에 GPIO를 설정하지 않아도 됨.)
	TIM_MatchConfigStruct.MatchValue = 10000;	// Timer 일치 값 설정 100us * 10000번 = 1초
}
