  #include<LPC17xx.h>
#include "lcd.h"
#include "lcd_fun.c"
 unsigned int adc_value;

void pwm_config(){

 LPC_SC->PCONP|=(1<<6);
 LPC_SC->PCLKSEL0=(1<<12)|(1<<13);
 LPC_PINCON->PINSEL3=(1<<21);//P1.26
  
  //PWM CONFIGURATION	   //single edge

  LPC_PWM1->PR=3;
  LPC_PWM1->MR0=5000;
  LPC_PWM1->MCR=(1<<1);//REPEAT
  LPC_PWM1->LER=(1<<0);
  LPC_PWM1->PCR&=~(1<<6);//P1.26 SINGLE EDGE
  LPC_PWM1->PCR|=(1<<14);//P1.26 PWM OUTPUT
  LPC_PWM1->TCR=(1<<0)|(1<<3); //CLEAR COUNTER,ENABLE PWM

}

void adc_config(){
  	 LPC_SC->PCONP|=(1<<12);
	 LPC_SC->PCLKSEL0=(1<<25)|(1<<24);
	 LPC_PINCON->PINSEL1=(1<<16); 

	  LPC_ADC->ADCR=(1<<1)|(4<<8)|(1<<16)|(1<<21);
  
	



}



int main(){

 	LPC_GPIO1->FIODIR|=(0xFF<<19);
		led_config();
	 pwm_config();
	 adc_config();


	 while(1){
	  while(!(LPC_ADC->ADGDR&(1<<31)))  ;
	 adc_value=(LPC_ADC->ADDR1&(0XFFF<<4));
	 adc_value=adc_value>>4;
	 led_cmd(0x01);
	 led_cmd(0x80);
	 led_str("var:");
	 led_cmd(0xc0);
	 led_num(adc_value);
	 
	 delay(1000);

	  LPC_PWM1->MR6=adc_value;
	  LPC_PWM1->LER=(1<<6);

	  delay(1000);


//	   LPC_PWM1->MR6=5000;
//	  LPC_PWM1->LER=(1<<6);
//	  delay(1000);
//
//	   LPC_PWM1->MR6=7000;
//	  LPC_PWM1->LER=(1<<6);
//	  delay(1000);
//
//	   LPC_PWM1->MR6=10000;
//	  LPC_PWM1->LER=(1<<6);
//	  delay(1000);

	 }


}