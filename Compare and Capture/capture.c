#include<htc.h>
#include<stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS&WDTE_OFF&PWRTE_OFF&BOREN_ON&LVP_OFF);
void delay();
void uart_init(void);
void print_uart(unsigned char *str);
void uart_tx(unsigned char  val);
unsigned char string[]="PIC initialized...\r\n";
int main()
{
	short int a,b,c,d,oldval=0,newval=0,value=0;
	char data[10];
	TRISC2 = 1;
	uart_init();
	print_uart(string);
	while(1)
	{
		CCP1CON = 0X05;
		CCP1IE  = 0;
		while(CCP1IF == 0)            //WAITING FOR "CCO1IF" CONDITION FAILS
		{	 
			 TMR1ON = 1;          //STAR THE TIMER
			 CCP1IF = 0;	      //MAKE THE CCP1IF "0" FOR ITS ANOYHER TIME START "0"
			 a = CCPR1H;	      //ASSAIN CCPR1H TO A
			 b = CCPR1L;          //ASSAIN CCPR1L TO B
		}
	 	while(CCP1IF == 0)	      //THIS FOR SECOND CLICK CHECKING
	 	{
			 CCP1IF = 0;          //MAKE INTERUPT FLAG "0"
			 c = CCPR1H;          //ASAIN CCPR1H TO C
			 d = CCPR1L;	      //ASAIN CCPR1L TO D
		 	oldval = ((a<<8)|b);  //left shifting + b value
		 	newval = ((c<<8)|d);  //left shifting + d value
		 	TMR1ON = 0;	      // TURN OF TIMER
		 	value=oldval-newval;
	 	}
		sprintf(data,"Data from capture A= %d \r Data from capture B= %d \r Data from capture c= %d \r  Data from capture d= %d \r",a,b,c,d);
		print_uart(data);
	}
}


void uart_tx(unsigned char val)
{
	TXREG=val;
	while(TXIF==0);
	TXIF = 0;
}


void uart_init(void)
{
	TRISC6 = 0;
	TRISC7 = 1;
	SPBRG  =31;
	TXEN   = 1;
	SPEN   = 1;
	TXIF   = 0;
	RCIF   = 0;
}


void print_uart(unsigned char *str)
{
	
	while(*str)
	{
		uart_tx(*str);
		delay();
		str++;
	}
}


void delay()
{
	TMR1CS  = 0;
	T1CKPS0 = 1;
	T1CKPS1 = 1;
	TMR1H   = 0X0b;
	TMR1L   = 0Xdb;
	TMR1ON  = 1;
	while(!TMR1IF);
	TMR1IF  = 0;
	TMR1ON  = 0;
}
