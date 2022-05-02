;--------------------------------------------------------------------------------------------------------------------------------
;  FILE NAME   :  BASE_SM2.ASM 
;  TARGET MCU  :  C8051F020 
;--------------------------------------------------------------------------------------------------------------------------------
$include (c8051f020.inc)               ; Include register definition file.
;-----------------------------------------------------------------------------
; EQUATES
;-----------------------------------------------------------------------------
GREEN_LED      equ   P1.6              ; Port I/O pin connected to Green LED.
;-----------------------------------------------------------------------------
; DATA Segment
;-----------------------------------------------------------------------------
data_test     segment  DATA
       		  rseg     data_test

tempo_data:       DS   10 
;------------------------------------------------------------------------------
; Put the STACK segment in the main module.
;------------------------------------------------------------------------------
?STACK          SEGMENT IDATA           ; ?STACK goes into IDATA RAM.
                RSEG    ?STACK          ; switch to ?STACK segment.
                DS      20              ; reserve your stack space
                                        ; 20 bytes in this example.
;-----------------------------------------------------------------------------
; XDATA SEGMENT
;-----------------------------------------------------------------------------
Ram_externe    SEGMENT XDATA     ; Reservation de 50 octets en XRAM
               RSEG    Ram_externe  
table_dest0:     DS		 20
table_dest:		 DS      200
;-----------------------------------------------------------------------------
; RESET and INTERRUPT VECTORS
;-----------------------------------------------------------------------------
               ; Reset Vector
               cseg AT 0          ; SEGMENT Absolu
               ljmp Start_pgm     ; Locate a jump to the start of code at 
                                  ; the reset vector.
;-----------------------------------------------------------------------------
; CODE SEGMENT
;-----------------------------------------------------------------------------
Prog_base      segment  CODE

               rseg     Prog_base      ; Switch to this code segment.
               using    0              ; Specify register bank for the following
                                       ; program code.
;******************************************************************************
;Initialisations de la mémoire code - Stockade de constante
;******************************************************************************
alphabet:  DB 'abcdefghijklmnopqrstuvwxyz'
chiffres:  DB '0123456789'
;******************************************************************************
;Initialisations de périphériques - Fonctionnalités Microcontroleur
;******************************************************************************
Start_pgm:
	    
         mov WDTCN, #0DEh    ; Disable WDT
         mov WDTCN, #0ADh
; Configure the XBRn Registers
         mov XBR0, #004h     ; XBAR0: Initial Reset Value
         mov XBR2, #040h     ; XBAR2: Initial Reset Value
; Port configuration (1 = Push Pull Output)
         mov P0MDOUT, #001h  ; Output configuration for P0 
         mov P1MDOUT, #040h  ; Output configuration for P1 
; Oscillator Configuration
         mov OSCXCN, #067h   ; External Oscillator Control Register	
         clr A               ;osc
         djnz ACC, $         ;wait for
         djnz ACC, $         ;at least 1ms
OX_WAIT:
         mov A, OSCXCN
         jnb ACC.7, OX_WAIT  ;poll XTLVLD
         mov OSCICN, #008h   ; Internal Oscillator Control Register
	                         ; On bascule sur l'oscillateur externe 
                             ; à 22118400            
;******************************************************************************
;Autres initialisations  
; Penser à initialiser le pointeur de pile en utilisant le segment ?STACK
;******************************************************************************
			  
;******************************************************************************
; Programme Principal
;******************************************************************************
Main:
         mov   SP,#?STACK-1
		 clr   GREEN_LED		; Initialize LED to OFF

              ; Vous pouvez inserer du code ici
 
fin_pg:  jmp   fin_pg
;******************************************************************************
; Sous programmes
;******************************************************************************

;******************************************************************************
; Ech_DPTR_R7R6
;
; Description: Sous-programme permettant d'échanger le contenu du DPTR avec R6/R7
;  DPH <--> R6 et DPL <--> R7
;
; Paramètres d'entrée: DPTR, R6 et R7                                
; Paramètres de sortie: aucun
; Registres modifiés: DPTR, R6 et R7

;******************************************************************************       		

Ech_DPTR_R7R6:
		; Code à insérer
		
;******************************************************************************
;******************************************************************************
; _ASM_Copy_CODE_to_XRAM
;
; Description: Sous-programme permettant de copier une zone de CODE vers une zone de XDATA
; 
;
; Paramètres d'entrée: 
;	R6(MSB) R7(LSB) contiennent l'adresse du debut de la zone XDATA
;	R4(MSB) R5(LSB) contient l'adresse du debut de la zone CODE
;	R3 contient le nombre d'éléments a copier
; Paramètres de sortie: aucun
; Registres modifiés: DPTR, R5, R6 et R7
; Pile: 1 octet (sauf pour l'appel de la sous -routine)
;******************************************************************************    
_ASM_Copy_CODE_to_XRAM:
	
				               
;-----------------------------------------------------------------------------
; End of file.
END
