# LED-BLINKING 
#include<htc.h>
#define _XTAL_FREQ 20000000		//Device Crystal Frequency
__CONFIG(0x1F7A);				//Configuration Bits refer Datasheet
void delay();
int main()
{
  int i,j=0,a=8,b=4,c=1;    //Initializing and declared variables
  TMR1CS=0;                 //clock source
  T1CKPS1=1;                //prescalar 1
  T1CKPS0=1;                //prescaler 0
  TRISB=0;                  //making a output ports
  PORTB=0x00;               //initially port B value is making '0'
  j=0x18;                   //              
  while(1)
  {
   for(i=0;i<4;i++)
   { 
     PORTB=j;
     j=j<<c;
     j=j+a;
     j=j+b;
     a=a/2;
     b=b/2;
     delay();
    }  
    break;
  } 
}
void delay()   
{
 int i;
 for(i=0;i<10;i++)                //in this loop executed '10'times mean making a delay '1'sec
  {
   TMR1ON=1;  
   TMR1H=0x0b;                   //timer values maximum range
   TMR1L=0xdb;                   //timer values minimum range
   T1CKPS0=1;                    //priscalar making a '1'
   T1CKPS1=1;                    //
   while(!TMR1IF);               //timer interrupt flags
   TMR1IF=0;       
  }
}











  

