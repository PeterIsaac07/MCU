/*
 * DIO.h
 *
 *  Created on: Feb 26, 2020
 *      Author: PI
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

/* Port Defines */
#define PORTA_   0
#define PORTB_   1
#define PORTC_   2
#define PORTD_   3
#define PORTE_   4
#define PORTF_   5

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0



void DIO_SetPortDirection (char charPortId, char charPortDir) ;
void DIO_PortInit (char charPortId);
void DIO_Pull_Pin_Up (char charPortId , char  charPinIdCopy);
void DIO_Pull_Pin_Down (char charPortId , char  charPinIdCopy);
void DIO_SetPintDirection (char charPortId , char  charPinIdCopy , char charPinDirCopy);

void DIO_SetPinValue(char charPortIdCopy , char charPinIdCopy, char charPinValCopy);
char DIO_GetPinValue(char charPortIdCopy, char charPinIdCopy) ;
void DIO_SetPortValue (char charPortId, char charPortVal) ;



#endif /* INC_DIO_H_ */
