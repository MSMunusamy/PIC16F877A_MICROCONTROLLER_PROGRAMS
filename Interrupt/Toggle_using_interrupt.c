# TOGGLE-USING-INTERRUPT

#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);            
unsigned char ptrc=0x00 ,ptrd =0x00;                                      
unsigned int count=1,wait =0;                                             |  GLOBAL DECLARATION 
void portc(void);                                                         |  VARIABLES 
void portd(void);                                                         |
void delay_s(void);                                                       |
int main()
{
   TMR0IF =0;                                                             | Timer '0' interrupt Flag
   GIE    =1;                                                             | Global interrupt enable bit
   PEIE   =1;                                                             | Peripheral interrupt enable bit
   TRISC = TRISD =0X00;                                                   | Making a output PORTC and PORTD
   delay_s();                                                             | Delay function
   while(1)                                                               | Infinite loop
   {
	   switch(count)                                                         
	   {
		   case 400:
		      portc();
			  break;
		   case 800:
		      portc();
			  portd();
			  break;
		   default:
		      break;
	   }
	   wait =1;                
	   while(wait==1);
   }	   
}
void interrupt ISR(void)
{
	if(TMR0IF==1)
	{
		TMR0IE=0;
		TMR0IF=0;
		wait=0;
		if(count<=800)
			count = count + 1;
		else
			count = 1;
		TMR0=31;                                
		TMR0IE=1;
	}
}

void delay_s()
{
	T0CS = 0;
	T0SE = 0;
	PSA  = 0;
	PS0  = 0;
	PS1  = 0;
	PS2  = 1;
	TMR0IF=0;
	TMR0IE=1;
	TMR0  =31;
}

void portc(void)
{
	ptrc=~ptrc;
	PORTC=ptrc;
}

void portd(void)
{
	ptrd=~ptrd;
	PORTD=ptrd;
}

