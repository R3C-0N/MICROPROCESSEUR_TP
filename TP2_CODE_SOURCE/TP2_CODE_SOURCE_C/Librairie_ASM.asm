;-----------------------------------------------------------------------------
;
;  FILE NAME   :  PROG_BASE.ASM 
;  TARGET MCU  :  C8051F020 

;-----------------------------------------------------------------------------

$INCLUDE(C8051F020.INC)  ; Register definition file.
;******************************************************************************
;Declaration des variables et fonctions publiques
;******************************************************************************

PUBLIC _ASM_Copy_CODE_to_XRAM 
;******************************************************************************
;Consignes de segmentation
;******************************************************************************

ASM_Lib     segment  CODE

            rseg     ASM_Lib  ; Switch to this code segment.
            using    0        ; Specify register bank for the following
                                       ; program code.



;******************************************************************************
; Sous programmes
;******************************************************************************
;******************************************************************************
; Ech_DPTR_R7R6
;
; Description: Sous-programme permettant d'�changer le contenu du DPTR avec R6/R7
; 
;
; Param�tres d'entr�e: DPTR, R6 et R7
; Param�tres de sortie: aucun
; Registres modifi�s: DPTR, R6 et R7
; Pile: 1 octet (sauf pour l'appel de la sous -routine)
;******************************************************************************       		

Ech_DPTR_R7R6:
			// Ins�rez votre code assembleur ici....
		ret
;******************************************************************************
;******************************************************************************
; _ASM_Copy_CODE_TO_XRAM
;
; Description: Sous-programme permettant de copier une zone de CODE vers une zone de XDATA
; 
;
; Param�tres d'entr�e: 
;	R6(MSB) R7(LSB) contiennent l'adresse du debut de la zone XDATA
;	R4(MSB) R5(LSB) contient l'adresse du debut de la zone CODE
;	R3 contient le nombre d'�l�ments a copier
; Param�tres de sortie: aucun
; Registres modifi�s: DPTR, R5, R6 et R7
; Pile: 1 octet (sauf pour l'appel de la sous -routine)
;******************************************************************************    
_ASM_Copy_CODE_to_XRAM:
		
		
		// Ins�rez votre code assembleur ici....
		ret
				               
;-----------------------------------------------------------------------------
; End of file.

END



