#include<lpc214x.h>
#include"lcd.h"
//#include"modernlcd.h"
#include"gpio.h"
#include"serial.h"
#include"gsm.h"
#include"adc.h"
#define trig    P1_16			 //p1.16
#define echo    P1_17		     //p1.17


unsigned int j,count,distance,adcdata=0,temp,ske=0,hum=0;

void serial0_RxISR(void) __irq; 

void InitSerial0Int(unsigned isrPtr)
{
  U0IER = 0x01;
  VICVectCntl0 	= 0x00000026;  						//select a priority slot for a given interrupt  
  VICVectAddr0 	= (unsigned long)isrPtr;		//pass the address of the IRQ into the VIC slot 
  VICIntEnable 	|= 0x00000040;						//enable interrupt2
} 
 
  void pin()
{
 PINSEL0=0X00050005;//SELECTING PIN OPERATION
 PINSEL1=0X15000000;
 PINSEL2=0X00000000;
 IODIR0=0XFFFFFFFF;// as output	and 2 pins as input
 IODIR0&=~((1<<21)|(1<<22));
 IODIR1&=~(1<<17);
 IOCLR1=0XFFFFFFFF;
 IOPIN1=0X0;
 AD0CR=0X00210600;// ADC CONTROL REGISTER

}
char inp0(unsigned long int pinNumber)
{
	unsigned long int pinBlockState =IOPIN0;
	int pinState = (pinBlockState & (pinNumber)) ? 1 : 0;
	return pinState;
}
char inp1(unsigned long int pinNumber)
{
   unsigned long int pinBlockState=IOPIN1;
  int pinState = (pinBlockState &(pinNumber)) ? 1 : 0;
  return pinState;
}


int main()
{
	

	unsigned long int j,count=0,distance=0;

	pin();
	IODIR1=0XFFFFFFFF;
	IODIR1&=~(1<<17);
	IODIR0=0xFFFFFFFF;
	IODIR0&=~((1<<21)|(1<<22));
	initlcd();
	adcinit();
	delay(50);
	ser_init_1(0x61,0x00);
	ser_init_0(0x61,0x00);
 
 clcd(0x01);delay(10);

stringlcd(0x01," TEST BED ON ");
stringlcd(0xC0,"  REAL TIME  ");
delay(2000);
stringlcd(0x01," AGRICULTURE ");
stringlcd(0xC0," PARAMETERS  ");
delay(2000);

IOCLR0|=0x00000080;
delay(2000);
gsminit();

while(1)
{
 		stringlcd(0x01,"TE:");delay(500);	
		stringlcd(0x88," MO:");delay(500);
		stringlcd(0xc0,"WL:");delay(500);

		adcdata=as1();
		temp=adcdata*3300;
		temp=temp/10240;
		clcd(0x84);
		conv(temp);
		delay(100);
				
		ske=as3();
		clcd(0x8c);
		delay(100);
		conv(ske);	 
		delay(500);


	for(j=0;j<10;j++)
    {	

        count=0;distance=0;
		IOSET1|=trig;
		delay(1);
	   	IOCLR1|=trig;	
		while((inp1(echo)==0));
		while(inp1(echo)==1)
		{
		count=count+1;
	     }
		 distance=count/6;
     	}	
	
	 
		 delay(50);
		 count=0;
		 clcd(0xc3);
		 delay(100);
		 conv(distance);
	 	 delay(500);
	

		if(ske>800)
		{
			IOSET0|=(0x00000020);
			stringlcd(0x01,"SOIL MOISTURE LOW");
			stringlcd(0xC0,"   MOTOR ON ");
			delay(1000);
			stringlcd(0X01,"MSG sending .......	");			
			string_0("AT+CMGS=");
			send_0(0x22);
			string_0("+919039136091");
			send_0(0x22);
			send_0(0x0D);send_0(0x0A);
			string_0("SOIL MOISTURE LEVEL: Low  \r\n");
			send_0(0x1a);
			delay(500);delay(500);
			stringlcd(0X01,"MSG SENT ");

		}
		if((ske>150)&&(ske<750))
		{
			stringlcd(0x01,"SOIL MOISTURE");
			stringlcd(0xC0,"LEVEL:MODERATE ");
			delay(1000);
	
		}
		if(ske<150)
		{
			IOCLR0|=(0x00000020);
			stringlcd(0x01,"SOIL MOISTURE HIGH ");
			stringlcd(0xC0,"   MOTOR OFF");
			delay(1000);
			stringlcd(0X01,"MSG sending .......	");			
			string_0("AT+CMGS=");
			send_0(0x22);
			string_0("+919039136091");
			send_0(0x22);
			send_0(0x0D);send_0(0x0A);
			string_0("SOIL MOISTURE LEVEL: HIGH \r\n");
			send_0(0x1a);
			delay(500);delay(500);
			stringlcd(0X01,"MSG SENT ");

		}


if(distance>800)
		{
			IOCLR0|=(0x00000020);
			stringlcd(0x01,"    WATER  ");
			stringlcd(0xC0," LEVEL: LOW  ");
			delay(1000);
			stringlcd(0X01,"MSG sending .......	");			
			string_0("AT+CMGS=");
			send_0(0x22);
			string_0("+919039136091");
			send_0(0x22);
			send_0(0x0D);send_0(0x0A);
			string_0("WATER LEVEL: LOW \r\n");
			send_0(0x1a);
			delay(500);delay(500);
			stringlcd(0X01,"MSG SENT ");

		}

		if(distance<200)
		{
			IOCLR0|=(0x00000020);
			stringlcd(0x01,"    WATER  ");
			stringlcd(0xC0," LEVEL: HIGH  ");
			delay(1000);
			stringlcd(0X01,"MSG sending .......	");			
			string_0("AT+CMGS=");
			send_0(0x22);
			string_0("+919039136091");
			send_0(0x22);
			send_0(0x0D);send_0(0x0A);
			string_0("WATER LEVEL: HIGH \r\n");
			send_0(0x1a);
			delay(500);delay(500);
			stringlcd(0X01,"MSG SENT ");

		}


			     
} 
}
