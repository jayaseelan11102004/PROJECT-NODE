
#include <LPC21xx.H>
#include "headerfp.h"
#include "dashboard.c"
#include "spi-fp.c"
#include "mcp3204-fp.c"
#include "can-driver-fp.c"


main(){	
	
	int c;
	
	VICIntSelect=0;
	VICVectCntl0=(1<<5)|27;
	VICVectAddr0=(unsigned long)can2_rx;
	VICIntEnable=1<<27;
	
	can2_init();
	dashboard();
	
	PINSEL1|=1<<10;
	PWMMR0=(60000*20)-1;
	PWMMR5=(60000*1.5)-1;
	PWMMCR=2;
	PWMPCR=1<<13;
	PWMTCR=0x9;
	
	delay_milliseconds(750);
	
	lcd(0x80,0);
	str("TEMP : 0.0 c");
	lcd(0xc0,0);
	str("FUEL : 0.0 %");
	
	while(1){
		if((IOPIN0)&1<<22){
			
			PWMMR5=(60000*2)-1;
			PWMLER=1<<5;
			for(c=0;c<5000000;c++);
			PWMMR5=(60000*1)-1;
			PWMLER=1<<5;
			for(c=0;c<5000000;c++);
		}
		else{
			
			PWMMR5=(60000*1.5)-1;
			PWMLER=1<<5;
		}
	}
}
