/*******************************************************************************
* File Name: pwm4.c  
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
#include "pwm4.h"

static pwm4_BACKUP_STRUCT  pwm4_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: pwm4_Sleep
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
*  \snippet pwm4_SUT.c usage_pwm4_Sleep_Wakeup
*******************************************************************************/
void pwm4_Sleep(void)
{
    #if defined(pwm4__PC)
        pwm4_backup.pcState = pwm4_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            pwm4_backup.usbState = pwm4_CR1_REG;
            pwm4_USB_POWER_REG |= pwm4_USBIO_ENTER_SLEEP;
            pwm4_CR1_REG &= pwm4_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pwm4__SIO)
        pwm4_backup.sioState = pwm4_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        pwm4_SIO_REG &= (uint32)(~pwm4_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: pwm4_Wakeup
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
*  Refer to pwm4_Sleep() for an example usage.
*******************************************************************************/
void pwm4_Wakeup(void)
{
    #if defined(pwm4__PC)
        pwm4_PC = pwm4_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            pwm4_USB_POWER_REG &= pwm4_USBIO_EXIT_SLEEP_PH1;
            pwm4_CR1_REG = pwm4_backup.usbState;
            pwm4_USB_POWER_REG &= pwm4_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pwm4__SIO)
        pwm4_SIO_REG = pwm4_backup.sioState;
    #endif
}


/* [] END OF FILE */
