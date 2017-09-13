#include "project.h"
#include <stdio.h>
#include <stdint.h>

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


void SetupHardware()
{
	UartSetup();
//	UartSetup2();
}

void UnlockPins()
{
	//Need to Unlock PF4
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0xFF;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0; 
	
}

int  main(void)
{
		
		uint8_t temp;
    volatile uint32_t ui32Loop;
	
	
	
    // Enable the GPIO port that is used for the on-board LED.
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SetupHardware();

		
		// Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    
		}
		
		UnlockPins();		//Function that unlocks certain pins that are needed.
    
		// Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2); // set pin 3 and 2 as output
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0); // set pin 4 and 0 as input
		//these two switches need an internal pull up on pins
		GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);//set internal pullup R for pin 0 and 4
		
		//int x;  //Int that contains the output of the button SW2
		//int y;  //Int that contains the output of the button SW1
		
		int x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0); // set x equal to the output of button SW2 
		int y = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4); // set x equal to the output of button SW1
		
		while(x == 1)  //While loop that keeps checking until x does not equal 1, meaning SW2 was pushed. 
		{
			x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);	
		}
			
		
    while(1)
    {
			x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0); // set x equal to the output of button SW2
			y = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4); // set x equal to the output of button SW1
			
			if (x && y == 0) //if loop that checks if SW1 and SW2 are pressed, if they are both pressed, blue LED will light.
			{
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xF);  // Turn on blue LED
				
        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        // Turn off the LED.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
				
			}
			else  //Else green LED will light.
			{
				UARTCharPut(UART0_BASE, temp);
			  temp++;
				//UARTCharPut(UART0_BASE, '\n');
				//UARTCharPut(UART0_BASE, '\r');
        // Turn on the LED.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0xF);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        // Turn off the LED.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
			}
    }
}


