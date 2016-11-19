/*******************************************************************************
* File Name: Fix.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Fix_ALIASES_H) /* Pins Fix_ALIASES_H */
#define CY_PINS_Fix_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Fix_0			(Fix__0__PC)
#define Fix_0_PS		(Fix__0__PS)
#define Fix_0_PC		(Fix__0__PC)
#define Fix_0_DR		(Fix__0__DR)
#define Fix_0_SHIFT	(Fix__0__SHIFT)
#define Fix_0_INTR	((uint16)((uint16)0x0003u << (Fix__0__SHIFT*2u)))

#define Fix_INTR_ALL	 ((uint16)(Fix_0_INTR))


#endif /* End Pins Fix_ALIASES_H */


/* [] END OF FILE */
