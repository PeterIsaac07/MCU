#include "stdint.h"
#include "BIT_MATH.h"
#include "types.h"
#include "DIO.h"
#include "uart.h"
#include "tm4c123gh6pm.h"
#include "KPAD_int.h"
#include "stdio.h"
#define FREE '0'
#define OCCUPIED '1'
#define ROOMCLEANING '2'
#define SETTING_UP  '3'


char room_number;
void SystemInit() {}	
char Room_Status = FREE;
int x = 0;
int password[4];
char enteredpassword[4] ;
char uartread;
int counter = 0;
int uart_complete = 0;	
	
	
	
	
	
void UART0_Handler(void){
	
	//taking the input from the uart
	char read = uart_rx();
	
	//clear the interrupt flag
	SET_BIT(UART0_ICR_R,4);
	SET_BIT(UART0_ICR_R,5);
	
	//taking the room number
	if (Room_Status == FREE && read != 'n'){
		room_number = read;
		Uart_Send_String("Welcome to room number ");
		uart_tx(room_number);
		Uart_Send_String("\nTo Set password press n , to open for room service press c");

	}
	
	
	if (read == 'n' && Room_Status == FREE){ // room is getting occupied and setting a password
		Uart_Send_String("\nPlease Enter the required 4 characters pass");
		DIO_SetPinValue(PORTF_,PIN3,HIGH);
		Room_Status = SETTING_UP;
			
	}
	else if (counter < 4 && Room_Status == SETTING_UP){ // to set password
				enteredpassword[counter] = read;
				counter++;
				if (counter ==4){
					Uart_Send_String("\nPassword was Set succefully!");
					counter=0;
					Room_Status =OCCUPIED;
					DIO_SetPinValue(PORTF_,PIN3,LOW);
					DIO_SetPinValue(PORTF_,PIN1,HIGH);		
				}
	
	}
 

	else if (read == 'c' && Room_Status == OCCUPIED){
				Uart_Send_String("\nThe room is currently open for cleaing");
				Room_Status = ROOMCLEANING;
				DIO_SetPinValue(PORTF_,PIN3,HIGH);
				DIO_SetPinValue(PORTF_,PIN1,HIGH);

	}

}
	
	
int main (void){
		char* stringtosend;
		__enable_irq();
	DIO_PortInit(PORTF_);
	DIO_SetPintDirection(PORTF_,PIN1,OUTPUT);
	DIO_SetPintDirection(PORTF_,PIN2,OUTPUT);
	DIO_SetPintDirection(PORTF_,PIN3,OUTPUT);	
	//ENABLE UART0 INTERRUBT
	 SET_BIT(NVIC_EN0_R,5);
	 NVIC_PRI1_R=0;
	//SET_BIT(NVIC_PRI1_R,13);
	Uart_Init();
	//Uart_Send_String("Press n for new password, or C for Room service mood");
	DIO_PortInit(PORTB_);
	DIO_SetPintDirection(PORTB_,PIN0,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN1,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN2,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN3,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN4,INPUT);
	DIO_SetPintDirection(PORTB_,PIN5,INPUT);
	DIO_SetPintDirection(PORTB_,PIN6,INPUT);
	DIO_SetPintDirection(PORTB_,PIN7,INPUT);
	KPAD_VidInit();
	Uart_Send_String("Please Enter the room number");

	
	while(1){
		char kpad = KPAD_u8GetKeyPressed();
		if(kpad != 'z'){
			uart_tx(kpad);
			password[counter] = kpad;
			counter++; 
			if (counter == 4){
					counter = 0;
				if(enteredpassword[0] == password[0] &&enteredpassword[1] == password[1] &&enteredpassword[2] == password[2] &&enteredpassword[3] == password[3]){
						GPIO_PORTF_DATA_R = 0;
						DIO_SetPinValue(PORTF_,PIN3,HIGH);
				
				
				}
				
			
			}
			
			
		}

}
			return 0 ;


}

/*

char read = uart_rx(); //read from uart
	
	//clear the interrupt flag
	SET_BIT(UART0_ICR_R,4);
	SET_BIT(UART0_ICR_R,5);

	if(Room_Status == FREE && read == 'n'){ //to make the room occupied
		DIO_SetPinValue(PORTF_,PIN2,HIGH);
		Room_Status = OCCUPIED;
	}
	
	else if (Room_Status == OCCUPIED && counter <4 ){ //occupied but still making the password

	password[counter]= uart_rx();
	counter++;
		if(counter == 4){
		DIO_SetPinValue(PORTF_,PIN2,LOW);
		DIO_SetPinValue(PORTF_,PIN1,HIGH);
		counter=0;
		}
	}
		




void	SysTick_Handler(void){
	TOG_BIT(GPIO_PORTF_DATA_R,3);
}

void GPIOF_Handler (void){
	SET_BIT(GPIO_PORTF_ICR_R,0);

	TOG_BIT(GPIO_PORTF_DATA_R,1);


}

	DIO_PortInit(PORTB_);
	DIO_SetPintDirection(PORTB_,PIN0,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN1,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN2,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN3,OUTPUT);
	DIO_SetPintDirection(PORTB_,PIN4,INPUT);
	DIO_SetPintDirection(PORTB_,PIN5,INPUT);
	DIO_SetPintDirection(PORTB_,PIN6,INPUT);
	DIO_SetPintDirection(PORTB_,PIN7,INPUT);
	KPAD_VidInit();



	DIO_PortInit(PORTF_);
	DIO_SetPintDirection(PORTF_,PIN0,INPUT);
	DIO_SetPintDirection(PORTF_,PIN4,INPUT);
	DIO_SetPintDirection(PORTF_,PIN1,OUTPUT);
	DIO_SetPintDirection(PORTF_,PIN2,OUTPUT);
	DIO_SetPintDirection(PORTF_,PIN3,OUTPUT);

	DIO_Pull_Pin_Up(PORTF_,PIN0);
	DIO_Pull_Pin_Up(PORTF_,PIN4);
	Uart_Init();
			
	NVIC_ST_RELOAD_R= 16000000-1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 7;
	__enable_irq();
	// pin0 a portf is edge sensitive
	CLR_BIT(GPIO_PORTF_IS_R,1);
	//not both edges
	CLR_BIT(GPIO_PORTF_IBE_R,0);
	//falling edge
	CLR_BIT(GPIO_PORTF_IEV_R,0);
	//clear interruput flag by writing 1
	SET_BIT(GPIO_PORTF_ICR_R,0);
	//unmask
	SET_BIT(GPIO_PORTF_IM_R,0);
	//set priority to 1
	SET_BIT(NVIC_PRI7_R,21); 
	//enable the interrupt
	NVIC_EN0_R = 0x40000000;
	
	*/
	