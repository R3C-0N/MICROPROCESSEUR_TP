//------------------------------------------------------------------------------------
// Base_TP4_IRC
//------------------------------------------------------------------------------------
//
// AUTH: FJ
// DATE: 03-03-2022
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
//------------------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//------------------------------------------------------------------------------------
sfr16 TMR3RL = 0x92;                    // Timer3 reload value
sfr16 TMR3 = 0x94;                    // Timer3 counter
sfr16 ADC0 = 0xbe;                    // ADC0 data
sfr16 ADC0GT = 0xc4;                    // ADC0 greater than window
sfr16 ADC0LT = 0xc6;                    // ADC0 less than window
sfr16 RCAP2 = 0xca;                    // Timer2 capture/reload
sfr16 T2 = 0xcc;                    // Timer2
sfr16 RCAP4 = 0xe4;                    // Timer4 capture/reload
sfr16 T4 = 0xf4;                    // Timer4
sfr16 DAC0 = 0xd2;                    // DAC0 data
sfr16 DAC1 = 0xd5;                    // DAC1 data

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400L //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

// El�ments pr�sents sur la carte 8051F020
sbit  LED = P1 ^ 6;  // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;    // Bouton Poussoir '1' relach�, '0' press�

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void); // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void send(unsigned char* s); // Send string
//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void) {

	// Configurations globales
	Init_Device();

	// Configurations des Sorties GPIO

	// Initialisations des sorties	
	LED = LED_Off;

	//CONFIG POUR LA LIAISON SERIE

	TR1 = 0;			//disable timer 1											//TIMER
	TF1 = 0;			//set timer 1 overflow to 0									//TIMER
	CKCON &= ~0x10;		//Set timer 1 to use system clock (not divided by 12)		//TIMER
	SCON0 = 0x50;         //Mode 1, Baudrate generating from Timer 1 					//UART
	TMOD = 0x20;			//Timer 1 Auto reload mode									//TIMER
	TH1 = TL1 = 0xfa;       //Values Calculated for 9600 baudrate						//UART
	PCON |= (1 << 7);	 	//Set SMOD0 = 1 so that we have 19200 baudrate (9600 * 2)	//UART
	TR1 = 1;              //Run the timer												//TIMER
	IE0 = 1;			//enable IT for timer 1										//TIMER 
	EA = 1; 				//enable global IT											//Global IT Enable


// Boucle infinie	
	while (1) {
		LED = ~LED;
		SBUF0 = 'c';    //sends character.
		fct_tempo(50000);	 //Tempo	  
	}
}


//method to send a string
//void send(unsigned char *s)
//{
//    while(*s) {
//        SBUF=*s++;
//        while(TI==0);
//        TI=0;
//    }
//}