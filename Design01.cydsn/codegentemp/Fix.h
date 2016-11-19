/*******************************************************************************
* File Name: Fix.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Fix_H) /* Pins Fix_H */
#define CY_PINS_Fix_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Fix_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Fix_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Fix_Read(void);
void    Fix_Write(uint8 value);
uint8   Fix_ReadDataReg(void);
#if defined(Fix__PC) || (CY_PSOC4_4200L) 
    void    Fix_SetDriveMode(uint8 mode);
#endif
void    Fix_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fix_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Fix_Sleep(void); 
void Fix_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Fix__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Fix_DRIVE_MODE_BITS        (3)
    #define Fix_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Fix_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Fix_SetDriveMode() function.
         *  @{
         */
        #define Fix_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Fix_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Fix_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Fix_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Fix_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Fix_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Fix_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Fix_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Fix_MASK               Fix__MASK
#define Fix_SHIFT              Fix__SHIFT
#define Fix_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fix_SetInterruptMode() function.
     *  @{
     */
        #define Fix_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Fix_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Fix_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Fix_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Fix__SIO)
    #define Fix_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Fix__PC) && (CY_PSOC4_4200L)
    #define Fix_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Fix_USBIO_DISABLE              ((uint32)(~Fix_USBIO_ENABLE))
    #define Fix_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Fix_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Fix_USBIO_ENTER_SLEEP          ((uint32)((1u << Fix_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Fix_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fix_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Fix_USBIO_SUSPEND_SHIFT)))
    #define Fix_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Fix_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fix_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Fix__PC)
    /* Port Configuration */
    #define Fix_PC                 (* (reg32 *) Fix__PC)
#endif
/* Pin State */
#define Fix_PS                     (* (reg32 *) Fix__PS)
/* Data Register */
#define Fix_DR                     (* (reg32 *) Fix__DR)
/* Input Buffer Disable Override */
#define Fix_INP_DIS                (* (reg32 *) Fix__PC2)

/* Interrupt configuration Registers */
#define Fix_INTCFG                 (* (reg32 *) Fix__INTCFG)
#define Fix_INTSTAT                (* (reg32 *) Fix__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Fix_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Fix__SIO)
    #define Fix_SIO_REG            (* (reg32 *) Fix__SIO)
#endif /* (Fix__SIO_CFG) */

/* USBIO registers */
#if !defined(Fix__PC) && (CY_PSOC4_4200L)
    #define Fix_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Fix_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Fix_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Fix_DRIVE_MODE_SHIFT       (0x00u)
#define Fix_DRIVE_MODE_MASK        (0x07u << Fix_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Fix_H */


/* [] END OF FILE */
