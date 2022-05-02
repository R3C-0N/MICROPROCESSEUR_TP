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
; Description: Sous-programme permettant d'échanger le contenu du DPTR avec R6/R7
; 
;
; Paramètres d'entrée: DPTR, R6 et R7
; Paramètres de sortie: aucun
; Registres modifiés: DPTR, R6 et R7
; Pile: 1 octet (sauf pour l'appel de la sous -routine)
;******************************************************************************       		

Ech_DPTR_R7R6:
			// Insérez votre code assembleur ici....
		ret
;******************************************************************************
;******************************************************************************
; _ASM_Copy_CODE_TO_XRAM
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
		
		
		// Insérez votre code assembleur ici....
		ret
				               
;-----------------------------------------------------------------------------
; End of file.

END



