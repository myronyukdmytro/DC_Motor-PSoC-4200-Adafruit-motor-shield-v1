/*******************************************************************************
* File Name: Data.c  
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
#include "Data.h"

static Data_BACKUP_STRUCT  Data_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Data_Sleep
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
*  \snippet Data_SUT.c usage_Data_Sleep_Wakeup
*******************************************************************************/
void Data_Sleep(void)
{
    #if defined(Data__PC)
        Data_backup.pcState = Data_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Data_backup.usbState = Data_CR1_REG;
            Data_USB_POWER_REG |= Data_USBIO_ENTER_SLEEP;
            Data_CR1_REG &= Data_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Data__SIO)
        Data_backup.sioState = Data_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Data_SIO_REG &= (uint32)(~Data_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Data_Wakeup
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
*  Refer to Data_Sleep() for an example usage.
*******************************************************************************/
void Data_Wakeup(void)
{
    #if defined(Data__PC)
        Data_PC = Data_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Data_USB_POWER_REG &= Data_USBIO_EXIT_SLEEP_PH1;
            Data_CR1_REG = Data_backup.usbState;
            Data_USB_POWER_REG &= Data_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Data__SIO)
        Data_SIO_REG = Data_backup.sioState;
    #endif
}


/* [] END OF FILE */
