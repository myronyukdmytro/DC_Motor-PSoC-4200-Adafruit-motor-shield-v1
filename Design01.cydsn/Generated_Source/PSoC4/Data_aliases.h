/*******************************************************************************
* File Name: Data.h  
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

#if !defined(CY_PINS_Data_ALIASES_H) /* Pins Data_ALIASES_H */
#define CY_PINS_Data_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Data_0			(Data__0__PC)
#define Data_0_PS		(Data__0__PS)
#define Data_0_PC		(Data__0__PC)
#define Data_0_DR		(Data__0__DR)
#define Data_0_SHIFT	(Data__0__SHIFT)
#define Data_0_INTR	((uint16)((uint16)0x0003u << (Data__0__SHIFT*2u)))

#define Data_INTR_ALL	 ((uint16)(Data_0_INTR))


#endif /* End Pins Data_ALIASES_H */


/* [] END OF FILE */
