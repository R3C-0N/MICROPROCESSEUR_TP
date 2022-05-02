 //------------------------------------------------------------------------------------
// Main_Test.c
//------------------------------------------------------------------------------------
// AUTH: 
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>   // SFR declarations
unsigned char code alphabet[] = "abcdefghijklmnopqrstuvwxyz";
unsigned char code chiffres[] = "0123456789";	
unsigned char xdata table_dest0[20];
unsigned char xdata table_dest[200];

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

sbit  LED = P1^6;         // LED sur Port P1.6  
//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Copy_CODE_to_XRAM(unsigned char xdata *zone_xdata,unsigned char code *zone_code,unsigned char nbr_char);
void ASM_Copy_CODE_to_XRAM(unsigned char nbr_char, unsigned char xdata *zone_xdata,unsigned char code *zone_code);
void Init_Device(void);
//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main (void) {

	 unsigned char j;
	
// Initialisations minimale du 8051F020 -- Configurations globales
    Init_Device();

// Initialisation des zones mémoire de destination	
	  for(j=0;j<sizeof(table_dest);j++) {     // Effacement de la zone XDATA destination
				table_dest[j]=0;
		}
			
// Fin des initialisations
	
// TEST des Fonctions  Copy_CODE_to_XRAM en C
    
	    // Insérer ICI les appels de fonctions Copy_CODE_to_XRAM
	
// TEST des Fonctions  ASM_Copy_CODE_to_XRAM en assembleur
	
	  // Insérer ICI les appels de fonctions Assembleur ASM_Copy_CODE_to_XRAM
	

   while (1) { LED = ~LED;	}
}    // Fin du main

// Fonction Copy_CODE_to_XRAM

  // Insérer ICI le code de la fonction Copy_CODE_to_XRAM
  
  
// Fonction INIT_DEVICE
void Init_Device(void)
	{
		int i;
    WDTCN     = 0xde;      
    WDTCN     = 0xad; 
	  P0MDOUT   = 0x01;
    P1MDOUT   = 0x40;
    XBR0      = 0x04;
    XBR2      = 0x40;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x08;
}