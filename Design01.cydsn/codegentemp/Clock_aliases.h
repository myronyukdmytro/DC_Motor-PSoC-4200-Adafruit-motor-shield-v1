/*******************************************************************************
* File Name: Clock.h  
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

#if !defined(CY_PINS_Clock_ALIASES_H) /* Pins Clock_ALIASES_H */
#define CY_PINS_Clock_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Clock_0			(Clock__0__PC)
#define Clock_0_PS		(Clock__0__PS)
#define Clock_0_PC		(Clock__0__PC)
#define Clock_0_DR		(Clock__0__DR)
#define Clock_0_SHIFT	(Clock__0__SHIFT)
#define Clock_0_INTR	((uint16)((uint16)0x0003u << (Clock__0__SHIFT*2u)))

#define Clock_INTR_ALL	 ((uint16)(Clock_0_INTR))


#endif /* End Pins Clock_ALIASES_H */


/* [] END OF FILE */
