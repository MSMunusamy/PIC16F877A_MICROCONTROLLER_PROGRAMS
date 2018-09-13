#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);

unsigned char prtc = 0x00,prtd = 0x00;
unsigned int count = 1, wait = 0;

void portc(void);
void portd(void);
void tmr1_init(void);

int main()
{
	GIE		= 1;
	PEIE	= 1;
	TRISC	= TRISD = 0x00;
	tmr1_init();
	while(1)
	{
		switch(count)
		{
			case 5:
				portc();
				break;
			case 10:
				portc();
				portd();
				break;
			default :
				break;
		}
		wait = 1;
		while(wait==1);
	}
}

void interrupt ISR(void)
{
	if(TMR1IF==1)
	{
		TMR1IE	= 0;
		TMR1IF	= 0;
		wait	= 0;
		
		if(count <= 10)
			count = count + 1;
		else
			count = 1;
		
		TMR1H	= 0x0B;
		TMR1L	= 0xDB;
		TMR1IE	= 1;
	}
}

void tmr1_init(void)
{
	TMR1CS	= 0;
	T1CKPS0 = 1;
	T1CKPS1 = 1;
	TMR1H	= 0x0B;
	TMR1L	= 0xDB;
	TMR1ON	= 1;
}

void portc(void)
{
	prtc	= ~prtc;
	PORTC	= prtc;
}

void portd(void)
{
	prtd 	= ~prtd;
	PORTD	= prtd;
}