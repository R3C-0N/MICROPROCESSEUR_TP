//------------------------------------------------------------------------------------
// Main_MP
//------------------------------------------------------------------------------------
//
// AUTH: FJ

// DATE MODIF: 29/03/2021
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include <c8051f020_sfr16.h>  

void Init_Device (void); // Fonction codée dans LIB_Base.c
void Seq_LED(void);      
//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define LED_On 1
#define LED_Off 0

// Eléments présents sur la carte 8051F020
sbit LED = P1^6;         // LED verte: '1' = ON; '0' = OFF
sbit BP = P3^7;           // Bouton Poussoir '1' relaché, '0' pressé

// ---

sbit CTRL = P3^5;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Config_INT_BP (void);	// 2.1
void ISR_BoutonPoussoir();	// 2.2
void CONFIG_Timer_IMP(void);	//3.1
void Config_Timer_UART(void); // 4.1
void Config_UART(void);
char putchar(char);	//4.2
char getkey(void); //5.1
//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------

int UART_offset = 1;
int UART_count = 1;

void main (void) {
 
	char UART_Key;
	
  Init_Device();

  LED = LED_Off;
  EA = 1;           // Enable global interrupts
	
	Config_INT_BP();
	P2MDOUT  |= (1<<4);	// P2^4 en mode push/pull
	P3MDOUT |= (1<<5);	// idem P3^5 (pour CTRL)
	CONFIG_Timer_IMP();
	Config_Timer_UART();
	Config_UART();
	
	
	P5 &= ~(1<<4);	// IMP = 0
	CTRL = 0;				// CTRL = 0
	
    while (1)
	  { 
			if (RI0 == 1) {
					UART_Key = getkey();
					if (UART_Key >= '0' && UART_Key <= '9'){
						SBUF0 = UART_Key;
						switch (UART_Key) {
							case '0' : UART_offset = 1; UART_count = 1;break;
							case '1' : UART_offset = 2; UART_count = 1;break;
							case '2' : UART_offset = 3; UART_count = 1;break;
							case '3' : UART_offset = 4; UART_count = 1;break;
							case '4' : UART_offset = 5; UART_count = 1;break;
							case '5' : UART_offset = 6; UART_count = 1;break;
							case '6' : UART_offset = 7; UART_count = 1;break;
							case '7' : UART_offset = 8; UART_count = 1;break;
							case '8' : UART_offset = 9; UART_count = 1;break;
							case '9' : UART_offset = 10; UART_count = 1;break;
							default : break;
						}
						UART_count=0;
				}
			}
				
       Seq_LED();  // NE PAS ENLEVER		
	}
}

//----------------------
	
// ETAPE 1
void Config_INT_BP (void) {
	P3IF &= ~(1<<7); // Remise à zero au cas où
	P3IF |= (1<<3);		
	EIE2 |= (1<<5); // activation de l'interruption 7
}

void ISR_BoutonPoussoir() interrupt 19
{
	CTRL =1 ;	
	P5 |= (1<<4);		// IMP = 1
	CTRL = 0;
	T2CON = 0x04; // On active le timer 2
	P3IF &= ~0x80;	// On remet le flag à 0
}

// ETAPE 2
void CONFIG_Timer_IMP(void)
{
	CKCON &= ~(1<<5); // On utilise 1/12 de la fréquence système => 1 843 200 Hz 0.000 000 542s => 47918 périodes
	// 1ms = 1843 périodes => 0x0733
	RCAP2 = 0xFFFF -0xBB2E; // 0xBB2E 
	IE |= (1<<5); // On active l'interruption du Timer 2
}

void ISR_Timer2() interrupt 5
{
	if(UART_count == UART_offset){
		CTRL = 1;
		P5 &= ~(1<<4);	// IMP = 0
		CTRL = 0;
		putchar('F');
		putchar('I');
		putchar('N');
		T2CON = 0;	// On arrete le Timer 2
		UART_count = 1;
	}
	else {UART_count++;}
	TF2 = 0;		// On reset le flag Timer 2
	
}

// ETAPE 3
void Config_Timer_UART(void) {
	
	TCON &= ~(1<<6); //Timer 1 stoppé
	TCON &= ~(1<<7); // Flag Timer 1 effacé
	CKCON |= (1<<4); //CONFIG CKCPN | Timer1 utilise la clock système
	
// CONFIG TMOD | On active le Timer1 quand TR1 est à 1, Timer1 compte sur les fronts descendants de T1, Timer 1 fonctionne en mode 2
	TMOD &= ~(1<<7);
	TMOD &= ~(1<<6);
	// Mode 2: 8-bit counter/timer with auto-reload
	TMOD |= (1<<5);
	TMOD &= ~(1<<4);
	
	TH1 = -(12);	// Programmation du registre TH1 (115200*16)= 1843200 ; 22 118 400 / 1843200 = 12 => On compte 12 périodes => 
	
	ET1 = 0;	// desactive interruption Timer1	
	TR1 = 1;	// Active Timer1
}
	

void Config_UART(void){
	// Selection de la source d'horloge Timer1
	RCLK0 = 0;
	TCLK0 = 0;
 	// Configuration de PCON
	PCON |= (1<<7); //BAUD RATE DOUBLE DISABLED
	PCON &= ~(1<<6); //Accès aux bits SM0 0 et SM0 1 
	SCON0 = 0x70;	// Mode 1
	REN0 = 1;	// Activer la réception
	TI0 = 1;
	RI0 = 0;
}

char putchar(char c)
{
	while(TI0==0);
	TI0 = 0;
	SBUF0 = c;
	return c;
}

char getkey(void){
	char c;
	while(RI0==0);
	RI0 = 0;
	c = SBUF0;
	//SBUF0 = c;
	return c;
}
