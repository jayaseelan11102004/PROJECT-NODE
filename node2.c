
#include <LPC21xx.H>
#include "headerfp.h"
#include "dashboard.c"
#include "spi-fp.c"
#include "mcp3204-fp.c"
#include "can-driver-fp.c"


void delay_milliseconds(u32);

main(){	
	
	u32 number;
	CAN2_MSG m1;
	
	IODIR0|=(3<<8)|(0xff<<0);
	IOSET0|=(3<<8)|(0xff<<0);
	IOCLR0|=(3<<8)|(0xff<<0);
	
	lcd(0x0e,0);
	lcd(0x0c,0);
	lcd(0x38,0);
	lcd(0x80,0);
	
	can2_init();
	Init_SPI1();
	
	while(1){
		
		m1.id=0x00000160;
		m1.rtr=0;//data frame
		m1.dlc=4;
		m1.byteA=Read_ADC_MCP3204(0);
		m1.byteB=0;
		{
		
		lcd(0x01,0);
		lcd(0x80,0);
		
		number = m1.byteA;
		lcd_integer(number);
		lcd('.',1);
		number=(m1.byteA-number)*100;
		lcd_integer(number);	
	}
		can2_tx(m1);
		delay_milliseconds(750);
	}
}

void delay_milliseconds(u32 milliseconds)
{
	//T0CTCR=0X00;
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<milliseconds);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
