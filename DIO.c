#include  "types.h"
#include  "BIT_MATH.h"
#include "DIO.h"
#include "DIO_REG.h"


volatile unsigned int* DIO_OutRegisters [6] = {GPIO_PORTA_DATA_REG,GPIO_PORTB_DATA_REG,GPIO_PORTC_DATA_REG,GPIO_PORTD_DATA_REG,GPIO_PORTE_DATA_REG , GPIO_PORTF_DATA_REG};

volatile unsigned int* DIO_DirRegisters [6] = {GPIO_PORTA_DIR_REG , GPIO_PORTB_DIR_REG , GPIO_PORTC_DIR_REG , GPIO_PORTD_DIR_REG, GPIO_PORTE_DIR_REG , GPIO_PORTF_DIR_REG};

volatile unsigned int* DIO_AfselRegisters [6] = {GPIO_PORTA_AFSEL_REG , GPIO_PORTB_AFSEL_REG ,GPIO_PORTC_AFSEL_REG, GPIO_PORTD_AFSEL_REG, GPIO_PORTE_AFSEL_REG, GPIO_PORTF_AFSEL_REG};

volatile unsigned int* DIO_DEN_Registers [6] = {GPIO_PORTA_DEN_REG,GPIO_PORTB_DEN_REG , GPIO_PORTC_DEN_REG , GPIO_PORTD_DEN_REG , GPIO_PORTE_DEN_REG , GPIO_PORTF_DEN_REG};

volatile unsigned int* DIO_Lock_Registers [6] = {GPIO_PORTA_LOCK_REG,GPIO_PORTB_LOCK_REG,GPIO_PORTC_LOCK_REG,GPIO_PORTD_LOCK_REG,GPIO_PORTE_LOCK_REG,GPIO_PORTF_LOCK_REG};

volatile unsigned int* DIO_Commit_Registers [6] = {GPIO_PORTA_CR_REG,GPIO_PORTB_CR_REG,GPIO_PORTC_CR_REG,GPIO_PORTD_CR_REG,GPIO_PORTE_CR_REG,GPIO_PORTF_CR_REG};
volatile unsigned int* DIO_Amsel_Registers [6] = {GPIO_PORTA_AMSEL_REG , GPIO_PORTB_AMSEL_REG , GPIO_PORTC_AMSEL_REG , GPIO_PORTD_AMSEL_REG , GPIO_PORTE_AMSEL_REG , GPIO_PORTF_AMSEL_REG};

volatile unsigned int* DIO_Port_Control_Registers [6] = {GPIO_PORTA_PCTL_REG,GPIO_PORTB_PCTL_REG,GPIO_PORTC_PCTL_REG,GPIO_PORTD_PCTL_REG,GPIO_PORTE_PCTL_REG,GPIO_PORTF_PCTL_REG};

volatile unsigned int* DIO_Port_Pull_Up [6] = {GPIO_PORTA_PUR_REG , GPIO_PORTB_PUR_REG , GPIO_PORTC_PUR_REG , GPIO_PORTD_PUR_REG , GPIO_PORTE_PUR_REG , GPIO_PORTF_PUR_REG};

volatile unsigned int* DIO_Port_Pull_Down [6] = {GPIO_PORTA_PDR_REG , GPIO_PORTB_PDR_REG , GPIO_PORTC_PDR_REG , GPIO_PORTD_PDR_REG , GPIO_PORTE_PDR_REG , GPIO_PORTF_PDR_REG};
volatile unsigned int* DIO_Port_ODR [6] = {GPIO_PORTA_ODR_REG,GPIO_PORTB_ODR_REG,GPIO_PORTC_ODR_REG,GPIO_PORTD_ODR_REG,GPIO_PORTE_ODR_REG,GPIO_PORTF_ODR_REG};


char temp = 0;

void DIO_PortInit (char charPortId){
	
			
    // connect the selected Port to the clock
        SET_BIT(*SYSCTL_RCGCGPIO_REG,charPortId);
        // unlock the Port
        *DIO_Lock_Registers[charPortId] = 0x4C4F434B;
        //commit registers
      
		//commit regs
        *DIO_Commit_Registers [charPortId] = 0xff;
        // digital enable
        *DIO_DEN_Registers[charPortId] = 0xff;
        
        // not analog
         *DIO_Amsel_Registers[charPortId] = 0x00;
         // no opendrain
         *DIO_Port_ODR[charPortId] = 0x00;
		 
		 //alternative selection
		 *DIO_AfselRegisters[charPortId] = 0x00;
		 
		 // control reg
		*DIO_Port_Control_Registers[charPortId] = 0x00;

}

void DIO_SetPortDirection (char charPortId, char charPortDir) {


    //set the direction
    *DIO_DirRegisters[charPortId] = charPortDir;

    

}


void DIO_SetPortValue (char charPortId, char charPortVal) {

    *DIO_OutRegisters [charPortId] = charPortVal;
}



void DIO_Pull_Pin_Up (char charPortId , char  charPinIdCopy){

    SET_BIT(*DIO_Port_Pull_Up[charPortId],charPinIdCopy);

}


void DIO_Pull_Pin_Down (char charPortId , char  charPinIdCopy){

    SET_BIT(*DIO_Port_Pull_Down[charPortId],charPinIdCopy);

}

void DIO_SetPintDirection (char charPortId , char  charPinIdCopy , char charPinDirCopy){

            if ( charPinDirCopy == OUTPUT )
                {
                SET_BIT(*DIO_DirRegisters[charPortId],charPinIdCopy);
                }

            if ( charPinDirCopy == INPUT )
                {
                CLR_BIT(*DIO_DirRegisters[charPortId],charPinIdCopy);
                }


}

void DIO_SetPinValue(char charPortIdCopy , char charPinIdCopy, char charPinValCopy) {


    if (charPinValCopy == HIGH)
            {
                SET_BIT(*DIO_OutRegisters[charPortIdCopy],charPinIdCopy);
            }

            else if (charPinValCopy == LOW)
            {
                CLR_BIT(*DIO_OutRegisters[charPortIdCopy],charPinIdCopy);
            }

}

char DIO_GetPinValue(char charPortIdCopy, char charPinIdCopy) {

 char   charResultLocal= GET_BIT(*DIO_OutRegisters[charPortIdCopy],charPinIdCopy);

return charResultLocal;

}

