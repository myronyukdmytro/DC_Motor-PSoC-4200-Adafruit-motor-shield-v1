/*******************************************************************************
* File Name: Fix.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Fix.h"

static Fix_BACKUP_STRUCT  Fix_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Fix_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Fix_SUT.c usage_Fix_Sleep_Wakeup
*******************************************************************************/
void Fix_Sleep(void)
{
    #if defined(Fix__PC)
        Fix_backup.pcState = Fix_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Fix_backup.usbState = Fix_CR1_REG;
            Fix_USB_POWER_REG |= Fix_USBIO_ENTER_SLEEP;
            Fix_CR1_REG &= Fix_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fix__SIO)
        Fix_backup.sioState = Fix_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Fix_SIO_REG &= (uint32)(~Fix_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Fix_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Fix_Sleep() for an example usage.
*******************************************************************************/
void Fix_Wakeup(void)
{
    #if defined(Fix__PC)
        Fix_PC = Fix_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Fix_USB_POWER_REG &= Fix_USBIO_EXIT_SLEEP_PH1;
            Fix_CR1_REG = Fix_backup.usbState;
            Fix_USB_POWER_REG &= Fix_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fix__SIO)
        Fix_SIO_REG = Fix_backup.sioState;
    #endif
}


/* [] END OF FILE */
