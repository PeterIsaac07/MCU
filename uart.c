#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "BIT_MATH.h"
void Uart_Init(){
	
	int x;
	
	//wslna l clock lel uart
	SET_BIT(SYSCTL_RCGCUART_R,0);
	//bnwsl el clock le port B
  
  SET_BIT(SYSCTL_RCGCGPIO_R,0);
		x=1;
		x=2;
		x=3;
		x=4;
		//disable uart
		//CLR_BIT(UART1_CTL_R,0);
		//set the baud rate to 9600
			UART0_IBRD_R = 104;
			UART0_FBRD_R = 21;
			//close parity
			CLR_BIT(UART0_LCRH_R,7);
			CLR_BIT(UART0_LCRH_R,1);

			//8 bit mode
			SET_BIT(UART0_LCRH_R,6);
			SET_BIT(UART0_LCRH_R,5);
			//Enable fifo
			CLR_BIT(UART0_LCRH_R,4);
			//one stop bit
			CLR_BIT(UART0_LCRH_R,3);
			//enable interrupt when 1/8 full
			UART0_IFLS_R = 0;
			// enable interrupt at rx and tx
			SET_BIT(UART0_IM_R,4);
			CLR_BIT(UART0_IM_R,5);
			//clear the interrupt
			SET_BIT(UART0_ICR_R,4);
			SET_BIT(UART0_ICR_R,5);
			
			
			//enable rx tx and uart
			UART0_CTL_R = 0x301;
	///////////////////////
   	//unlock the port
	  GPIO_PORTA_LOCK_R = 0x4C4F434B;
	  //commit the two pins only
	  SET_BIT(GPIO_PORTA_CR_R,0);
	  SET_BIT(GPIO_PORTA_CR_R,1);
	  //digitalise the two pins
		SET_BIT(GPIO_PORTA_DEN_R,0);
		SET_BIT(GPIO_PORTA_DEN_R,1);
		//alternative select 
		SET_BIT(GPIO_PORTA_AFSEL_R,0);
		SET_BIT(GPIO_PORTA_AFSEL_R,1);
		//set the alternative to uart
		SET_BIT(GPIO_PORTA_PCTL_R,0);
		SET_BIT(GPIO_PORTA_PCTL_R,4);
		// set to input and output
		SET_BIT(GPIO_PORTA_DIR_R,1);
		CLR_BIT(GPIO_PORTA_DIR_R,0);
		//set them to pull up
		SET_BIT(GPIO_PORTA_PUR_R,0);
		/////////////////////end of GPIO ///////////////////////
		
		





}

void uart_tx(char x){
	while(GET_BIT(UART0_FR_R,5) == 1){}
	UART0_DR_R = x;

}
char uart_rx(){
	char x = UART0_DR_R;
	return x;

	} 	

	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
void Uart_Send_String(char* sending){
		int counter =0;
		while (sending[counter] != '\0'){
		
			uart_tx(sending[counter]);
			counter++;
		
		
		}
		

}