//******************************************************************************
//TP_8051_Lib.asm
//   Ce fichier contient des d�finitions et des routines utiles au TP
//  Microcontr�leur
//  Aucune modification n'est n�cessaire.
//  Il suffit d'ajouter ce fichier � votre Projet
//  TARGET MCU  :  C8051F020 

//******************************************************************************
#include "C8051F020.h"
// Peripheral specific initialization functions,
// Called from the Init_Device() function

//-----------------------------------------------------------------------------
// D�validation du watchdog
//-----------------------------------------------------------------------------
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
}
//-----------------------------------------------------------------------------
// Configuration des Ports d'entr�e-sorties
//-----------------------------------------------------------------------------
void Port_IO_Init()
{
    // P0.0  -  TX0 (UART0), Push-Pull,  Digital
    // P0.1  -  RX0 (UART0), Open-Drain, Digital
    // P0.2  -  CEX0 (PCA),  Push-Pull,  Digital
    // P0.3  -  CEX1 (PCA),  Open-Drain, Digital
    // P0.4  -  CEX2 (PCA),  Open-Drain, Digital
    // P0.5  -  CEX3 (PCA),  Open-Drain, Digital
    // P0.6  -  ECI,         Open-Drain, Digital
    // P0.7  -  T0 (Timer0), Push-Pull,  Digital

    // P1.0  -  INT0 (Tmr0),         Open-Drain, Digital
    // P1.1  -  T1 (Timer1),         Open-Drain, Digital
    // P1.2  -  INT1 (Tmr1),         Open-Drain, Digital
    // P1.3  -  T2 (Timer2),         Open-Drain, Digital
    // P1.4  -  T2EX (Tmr2),         Open-Drain, Digital
    // P1.5  -  SYSCLK,              Push-Pull,  Digital   Visu Horloge Syst�me
    // P1.6  -  General Purpose I/O, Open-Drain, Digital   Port LED
    // P1.7  -  General Purpose I/O, Open-Drain, Digital

    // P2.0  -  General Purpose I/O, Open-Drain, Digital
    // �...
    // P3.7  -  General Purpose I/O, Open-Drain, Digital

    P0MDOUT   = 0x85;
    P1MDOUT   = 0x00;
    P2MDOUT   = 0x00;
    P3MDOUT   = 0x00;
    P74OUT    = 0x01;
    P1MDIN    = 0xFF;

    XBR0      = 0x64;
    XBR1      = 0xFE;
    XBR2      = 0x40;

    P2        = 0;
    P1        = 0;
	  P3        = 0;
		P4        = 0;
}

//-----------------------------------------------------------------------------
// Configuration de l'oscillateur - SYSCLK = Clock externe 22118400Hz 
//-----------------------------------------------------------------------------
void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}
//-----------------------------------------------------------------------------
// Initialisation globale du Microcontr�leur - 
//-----------------------------------------------------------------------------
void Init_Device(void)
{
    Reset_Sources_Init();
    Port_IO_Init();
    Oscillator_Init();
}