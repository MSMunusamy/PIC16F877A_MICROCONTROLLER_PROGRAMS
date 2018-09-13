#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(HS & WDTDIS & PWRTDIS & BOREN & LVPDIS );

#define RS RC0 
#define RW RC1
#define EN RC2

void delay();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
int main()
{
	int i;
	TRISB=0;    //TRISB output port selection 
	TRISD=0;    //TRISD output port selection 
	TRISC=0;    //TRISC output port selection
	PORTB=0x00; //initializing a portB value is 0	
	
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0F);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
	
	for(i=0;i<10;i++)
	lcd_data('a');

	
	while(1)
	{}
}
void delay()
{
		TMR1CS=0;
		
		T1CKPS0=1;     
		T1CKPS1=1;
		TMR1H=0X3C;
		TMR1L=0XB0;
		TMR1ON=1;
		while(!TMR1IF);
				TMR1IF=0;
				TMR1ON=0;
}


void lcd_cmd(unsigned char cmd)
{
	RS	= 0;
	RW	= 0;
	EN	= 1;
	PORTD=cmd;
	delay();
	EN	= 0;
}

void lcd_data(unsigned char data)
{
	RS	= 1;
	RW	= 0;
	EN	= 1;
	PORTD= data;
	delay();
	EN	= 0;
}
