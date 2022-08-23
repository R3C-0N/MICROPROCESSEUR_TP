//     _             _     _      _____
//    / \   _ __ ___| |__ (_)  __|___  |
//   / _ \ | '__/ __| '_ \| | / __| / /
//  / ___ \| | | (__| | | | | \__ \/ /
// /_/   \_\_|  \___|_| |_|_| |___/_/

#include <c8051f020.h> // sfr declarations

//  _____ ____    _____
// |_   _|  _ \  |___ /
//   | | | |_) |   |_ \
//   | | |  __/   ___) |
//   |_| |_|     |____/

// Ports Entrées-sorties et Interruptions

// 1 - ‐ Analyse des codes transmis – Configuration et utilisation de broches en sortie

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400 //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

extern  code char Sin_table[];

// Eléments présents sur la carte 8051F020
sbit  LED = P1 ^ 6;         // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;           // Bouton Poussoir '1' relaché, '0' pressé

// Eléments de l'application Pilotage d'un systéme de tri
sbit Tst4 = P3 ^ 4;
sbit Tst5 = P3 ^ 5;
sbit Tst6 = P3 ^ 6;

void main(void) {

    Init_Device();

    //Les signaux sont periodiques, mais le signal sur lequel est la LED a une amplitude trop basse pour que cette derniere s'alume.
    //Ceci est du a une erreur de config du port. Il faut enable le push pull pour avoir 3.3V.

    // Correction Sorties LED et Tst4 mise en Push Pull
    P1MDOUT |= (1 << 6);  // LED P1.6 en PushPull
    P3MDOUT |= (1 << 4);  // TST4 P3.4 en PushPull
    P74OUT |= (1 << 0) | (1 << 1); // P4 en PushPull  (impossible de configurer bit à bit)

    Tst4 = 0;
    LED = LED_Off;

    // Activité 2 - Configuration du Bouton Poussoir P3.7
    // BP actif niveau bas
    // LED allumée si LED est au niveau haut	

    // Configuration de BP (P3.7) en entrée	
    BP = 1;
    P3MDOUT &= ~0x80;  // P3.7 placé en Open Drain 	

    while (1) {
        //   LED = ~LED;
        Tst4 = ~Tst4;

        //Cp de l'état de la led sur tst4
        if (Tst4 == 0) P4 &= ~((1 << 1) | (1 << 6));
        else P4 |= ((1 << 1) | (1 << 6));

        //On fais clignoter la led si bp est a 1
        if (BP != 0)  LED = ~LED;
        else LED = 0;

        //tempo .6s
        fct_tempo(60000);
    }
}

// 2 - Mise en œuvre du bouton‐poussoir – Configuration d’une broche en entrée

void main(void) {

    unsigned char i;
    Init_Device();
    Config_INT7();

    // Correction Sorties LED et Tst4 mise en Push Pull
    P1MDOUT |= (1 << 6);  // LED P1.6 en PushPull
    P3MDOUT |= (1 << 4) | (1 << 6);  // TST4 P3.4 et P3.6 en PushPull
    P74OUT |= (1 << 0) | (1 << 1); // P4 en PushPull  (impossible de configurer bit � bit)

    CP_BCL = 0;
    Tst4 = 0;
    Tst6 = 0;
    LED = LED_Off;

    // Activit� 2 - Configuration du Bouton Poussoir P3.7
    // BP actif niveau bas
    // LED allum�e si LED est au niveau haut	

    // Configuration de BP (P3.7) en entr�e	
    BP = 1;
    P3MDOUT &= ~0x80;  // P3.7 plac� en Open Drain 	

    EA = 1; // !!! bien penser a ça

    while (1) {
        LED = ~LED;
        Tst4 = ~Tst4;
        if (Tst4 == 0) P4 &= ~((1 << 1) | (1 << 6));
        else P4 |= ((1 << 1) | (1 << 6));
        //   if (BP != 0)  LED = ~LED;
        //   else LED = 0;
        for (i = 0;i <= CP_BCL; i++) fct_tempo(60000);
    }
}
//***************************************************************************************
void Config_INT7(void) {
    //Config pour que le bp genere une IT (en l'occurence sur le vecteur 19, me demandez pas pq je comprend r)
    // Registres: P3IF
    P3IF &= ~0x08; // INT7 active front descendant
    P3IF &= ~0x80; // RAZ Flag INT7
    EIE2 |= 0x20;  // INT7 autoris�e
    EIP2 &= ~0x20; //Priorit� basse
}
//***************************************************************************************
void ISR_INT7(void) interrupt 19
{
    // Ici on change le multiplicateur de la fréquence d'oscilation de la led
    // Les ifs du prof sont moches btw
    Tst6 = 1;
    P3IF &= ~0x80; // RAZ Flag INT7
    if (CP_BCL == 1) CP_BCL = 10;
    else CP_BCL = 1;
    Tst6 = 0;
}

//  _____ ____    _  _
// |_   _|  _ \  | || |
//   | | | |_) | | || |_
//   | | |  __/  |__   _|
//   |_| |_|        |_|

// TP4 - Timers

// Le TP 4 j'ai perdu mon code donc j'ai que la correction, je sais plus de quoi ça parlais

// 1 - Analyse et utilisation des codes transmis
// 2 - Configuration et utilisation d’un Timer en mode base de temps avec interruption
// 3 - Configuration et utilisation d’un Timer en mode Compteur d’évènements

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400L //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

// El�ments pr�sents sur la carte 8051F020
sbit  LED = P1 ^ 6;         // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;           // Bouton Poussoir '1' relach�, '0' press�

// GPIO sp�cifques pour ce TP
sbit Flag_BCL = P2 ^ 0;
sbit Flag_T2 = P2 ^ 4;
sbit Flag_T4 = P2 ^ 6;
sbit SIG_OUT = P3 ^ 0;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void); // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void Config_Timer2();
void Config_Timer4();

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void) {

    Init_Device();

    // Configurations des Sorties GPIO
    P2MDOUT = (1 << 0); // P2.0 (Flag_BCL) en Push Pull
    P2MDOUT |= (1 << 4) | (1 << 6);  // P2.4 (Flag_T2) et P2.6 (Flag_T4)  en Push Pull
    P3MDOUT |= (1 << 0); // P3.0 (SIG_OUT) en sortie 

    // Initialisations des sorties	
    LED = LED_Off;
    Flag_BCL = 0;
    Flag_T2 = 0;
    Flag_T4 = 0;
    SIG_OUT = 0;

    //Config Timer 2 en Auto-reload toutes les 5ms
    Config_Timer2();
    //Config Timer 4 en compteur d'evenements	
    Config_Timer4();
    // Validation globale des interruptions	
    EA = 1;

    // Boucle infinie	
    while (1) {
        Flag_BCL = 1;
        Flag_BCL = 0;
        //		  LED = ~LED;
        //     fct_tempo(50000);		  
    }
}
//------------------------------------------------------------------------------------
// Config_Timer2
//------------------------------------------------------------------------------------
void Config_Timer2(void) {
    // Configurer T2CON CKCON RCAP2L RCAP2H TL2 et TH2
    CKCON &= 0xdf;         // T2M: Timer 2 Clock Select
                           // CLK = sysclk/12
    TF2 = 0;		       // RAZ Flag TF2 Overflow Timer2
    EXF2 = 0;              // RAZ Flag EXF2
    EXEN2 = 0;	           // Action entr�e T2EX d�valid�e
    CT2 = 0;               // Mode Timer
    CPRL2 = 0;             // Auto reload of timer 2
                           // On a utilis� l��criture Bit � bit sur T2CON


    RCAP2 = -(((SYSCLK / 12) / 200)); //RCAP2 d�clar� en SFR16 5ms = 200Hz
    T2 = RCAP2;       // pour un premier cycle de bonne dur�e
    TR2 = 1;          // Timer2 d�marr�
    PT2 = 1;	      //INT Timer2 priorit� haute
    ET2 = 1;	      // INT Timer2 autoris�e

}

//------------------------------------------------------------------------------------
// Config_Timer4
//------------------------------------------------------------------------------------
void Config_Timer4(void) {
    // Configurer T4CON CKCON RCAP4L RCAP4H TL4 et TH4
    T4CON &= ~(1 << 2);	//TR4 = 0 -- Timer stopp� pour configurer 
    T4CON |= (1 << 1);  // C/T4 = 1 -- Mode Compteur
                        // Entr�e CLK sur T4

    T4CON &= ~(1 << 7);	// RAZ Flag TF4 Overflow Timer2
    T4CON &= ~(1 << 6);	// RAZ Flag EXF4
    T4CON &= ~(1 << 0);	// CP/RL4 = 0 -- Mode Autorechargement
    T4CON &= ~(1 << 3);	// EXEN4 = 0 -- Action entr�e T4EX d�valid�e

    RCAP4 = 65536 - 50;  // Tous les 50 �v�nements, on change l'�tatde SIG_OUT
    T2 = RCAP2;          // pour un premier cycle de bonne dur�e
    T4CON |= (1 << 2);	 //TR4 = 1 -- Timer4 d�marr� 

    EIP2 |= (1 << 2); //PT4=1 -- Int Timer4 priorit� haute
    EIE2 |= (1 << 2); // ET4=1 -- Interruption T4 autoris�e

}
//------------------------------------------------------------------------------------
// ISR_Timer2
//------------------------------------------------------------------------------------
void ISR_Timer2(void) interrupt 5
{
    static unsigned char	CP_Bcl_5ms;
    Flag_T2 = 1;
    if (TF2) {
        TF2 = 0;		// RAZ Flag TF2 Overflow Timer2
        CP_Bcl_5ms++;
        if (CP_Bcl_5ms >= 10) {
            CP_Bcl_5ms = 0;
            LED = ~LED;
        }
    }
    if (EXF2) EXF2 = 0; // S�curit� si INT EXF2

    Flag_T2 = 0;

}

// ------------------------------------------------------------------------------------
// ISR_Timer2
//------------------------------------------------------------------------------------
void ISR_Timer4(void) interrupt 16
{
    //static unsigned char	CP_Bcl_5ms;
    Flag_T4 = 1;
    if (T4CON & (1 << 7)) {
        T4CON &= ~(1 << 7);		// RAZ Flag TF4 Overflow Timer4
        SIG_OUT = ~SIG_OUT;
    }
    if (T4CON & (1 << 6))  T4CON &= ~(1 << 6);  // S�curit� si INT EXF4
    Flag_T4 = 0;
}

//  _____ ____    ____
// |_   _|  _ \  | ___|
//   | | | |_) | |___ \
//   | | |  __/   ___) |
//   |_| |_|     |____/

// TP 5 - UART

// 1 - Analyse et utilisation des codes transmis
// 2 - Configuration de l’UART0 – Test de fonctionnement de L’UART en transmission
// 3 - Test de fonctionnement de L’UART en réception de caractère – application d’écho de caractère
// 4 - Codage de la fonction Putchar
// 5 - Codage de la fonction _getkey

#include<stdio.h>

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400L //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

#define BAUDRATE 19200L
#define Freq_timer0 (BAUDRATE*16)

#define Preload_Timer1 (SYSCLK/Freq_timer0)
#if Preload_Timer1 > 255 
#error "Valeur Preload Timer0 HORS SPECIFICATIONS"
#endif 

// El�ments pr�sents sur la carte 8051F020
sbit  LED = P1 ^ 6;  // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;    // Bouton Poussoir '1' relach�, '0' press�

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void); // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void CFG_Clock_UART0(void);
void CFG_UART0(void);
char getkey_one_time(void);

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void) {

    char temp_char;
    unsigned int CP_BCL;
    unsigned char CP;
    char xdata buf[20];
    unsigned char i;

    // Configurations globales
    Init_Device();
    CFG_Clock_UART0();
    CFG_UART0();

    // Configurations des Sorties GPIO

    // Initialisations des sorties	
    LED = LED_Off;
    CP_BCL = 0;
    CP = 0;

    // Boucle infinie	
    while (1) {
        LED = ~LED;
        fct_tempo(50000);

        // Pour compiler une activit�, il faut qu'elle soit encadr�e par un "#If 1 // # endif"
        // Inversement toute activit� encadr�e par un "#If 0 // # endif" ne sera pas compil�e	 

        // Activit� 2 - Test config UART - Test Transmission - Envoi continu
#if 1   	
        SBUF0 = 'A';
#endif


        //Activit� 3 - Test config UART - Test r�ception
#if 0  
        if (RI0) {
            temp_char = SBUF0;
            SBUF0 = temp_char + 1;
            RI0 = 0;
        }
#endif
        // Activit� 4  Putchar - utilisation de printf
#if 0		 
        CP++;
        if (CP >= 10) {
            CP = 0;
            printf("Compteur: %u\n", CP_BCL);
            CP_BCL++;
        }

#endif
        // Etape 5 - Codage Getkey - utilisation de gets
#if 0	
        gets(buf, sizeof(buf) - 1);
        for (i = 0;i < sizeof(buf);i++) {
            if (buf[i] != 0) buf[i]++;
        }
        printf("reponse: %s\n", buf);
#endif						 

    }
}
//*****************************************************************************	 
//CFG_clock_UART
//	Utilisation du Timer 1
//
// 
//*****************************************************************************	 
void CFG_Clock_UART0(void) {
    CKCON |= (1 << 4);             // T1M: Timer 1 Clock Select
                                   // Timer CLK = SYSCLK
    TMOD |= (1 << 5);
    TMOD &= ~((1 << 7) | (1 << 6) | (1 << 4));			  // Timer1 configur� en Timer 8 bit avec auto-reload	
    TF1 = 0;				  // Flag Timer effac�
    TH1 = -(Preload_Timer1);
    ET1 = 0;				   // Interruption Timer 1 d�valid�e
    TR1 = 1;				   // Timer1 d�marr�
}
//*****************************************************************************	 
//CFG_uart0_mode1
//
//
// 
//*****************************************************************************	 
void CFG_UART0(void) {
    RCLK0 = 0;   // Source clock Timer 1
    TCLK0 = 0;
    PCON |= (1 << 7); //SMOD0: UART0 Baud Rate Doubler Disabled.
    PCON &= ~(1 << 6); // SSTAT0=0
    SCON0 = 0x70;   // Mode 1 - Check Stop bit - Reception valid�e

//   TI0 = 0;     // Drapeaux TI et RI � z�ro
    RI0 = 0;
    TI0 = 1;  //� cause du codage de putchar

    ES0 = 0;  // Interruption UART autoris�e
}
//*****************************************************************************	 
char putchar(char c) {
    while (TI0 == 0);
    TI0 = 0;
    SBUF0 = c;
    return c;
}

//*****************************************************************************	 
char _getkey(void) {
    char c;
    while (RI0 == 0);
    RI0 = 0;
    c = SBUF0;
    return c;
}

//*****************************************************************************	
// Inutile dans ce TP IRC
char getkey_one_time(void)

{
    char c;
    if (RI0 == 0) return 0;
    else {
        RI0 = 0;
        return SBUF0;
    }
}