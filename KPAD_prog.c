#include "types.h"
#include "DIO.h"
#include "KPAD_int.h"

#include "KPAD_cfg.h"
#define F_CPU 8000000

u8 KPAD_au8RowPins [4] = {Row0,Row1,Row2,Row3};
u8 KPAD_au8ColPins [4] = {Col0,Col1,Col2,Col3};
u8 KPAD_au8Value [4][4] = {{'1','2','3','4'},{'5','6','7','8'},{'9','10','11','12'},{'13','14','15','16'}};

void KPAD_VidInit (void)
{
	DIO_Pull_Pin_Up(KPAD_In_PORT,Row0);
	DIO_Pull_Pin_Up(KPAD_In_PORT,Row1);
	DIO_Pull_Pin_Up(KPAD_In_PORT,Row2);
	DIO_Pull_Pin_Up(KPAD_In_PORT,Row3);

	
}
char KPAD_u8GetKeyPressed (void)
{
	u8 u8loopctr1,u8loopctr2 ;
		for (u8loopctr1=0 ; u8loopctr1<4;u8loopctr1++)
		{
			DIO_SetPinValue(KPAD_Out_PORT,KPAD_au8ColPins[u8loopctr1],LOW);

			for (u8loopctr2 = 0 ; u8loopctr2 <4 ; u8loopctr2++)
			{
				if (DIO_GetPinValue(KPAD_In_PORT,KPAD_au8RowPins [u8loopctr2]) == LOW)
				{

					while (DIO_GetPinValue(KPAD_In_PORT,KPAD_au8RowPins [u8loopctr2]) == LOW)
					{}
					//_delay_ms(5);
					DIO_SetPinValue(KPAD_Out_PORT,KPAD_au8ColPins[u8loopctr1],HIGH);
					return KPAD_au8Value [u8loopctr2] [u8loopctr1];
						// or return (loopctr2*4)+loopctr1+1

				}
			}
			DIO_SetPinValue(KPAD_Out_PORT,KPAD_au8ColPins[u8loopctr1],HIGH);
		}


			return 'z';
}
