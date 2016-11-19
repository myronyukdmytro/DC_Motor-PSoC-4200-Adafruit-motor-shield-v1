/*******************************************************************************
* File Name: Clock.h  
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

#if !defined(CY_PINS_Clock_H) /* Pins Clock_H */
#define CY_PINS_Clock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Clock_aliases.h"


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
} Clock_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Clock_Read(void);
void    Clock_Write(uint8 value);
uint8   Clock_ReadDataReg(void);
#if defined(Clock__PC) || (CY_PSOC4_4200L) 
    void    Clock_SetDriveMode(uint8 mode);
#endif
void    Clock_SetInterruptMode(uint16 position, uint16 mode);
uint8   Clock_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Clock_Sleep(void); 
void Clock_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Clock__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Clock_DRIVE_MODE_BITS        (3)
    #define Clock_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Clock_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Clock_SetDriveMode() function.
         *  @{
         */
        #define Clock_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Clock_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Clock_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Clock_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Clock_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Clock_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Clock_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Clock_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Clock_MASK               Clock__MASK
#define Clock_SHIFT              Clock__SHIFT
#define Clock_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Clock_SetInterruptMode() function.
     *  @{
     */
        #define Clock_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Clock_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Clock_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Clock_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Clock__SIO)
    #define Clock_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Clock__PC) && (CY_PSOC4_4200L)
    #define Clock_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Clock_USBIO_DISABLE              ((uint32)(~Clock_USBIO_ENABLE))
    #define Clock_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Clock_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Clock_USBIO_ENTER_SLEEP          ((uint32)((1u << Clock_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Clock_USBIO_SUSPEND_DEL_SHIFT)))
    #define Clock_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Clock_USBIO_SUSPEND_SHIFT)))
    #define Clock_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Clock_USBIO_SUSPEND_DEL_SHIFT)))
    #define Clock_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Clock__PC)
    /* Port Configuration */
    #define Clock_PC                 (* (reg32 *) Clock__PC)
#endif
/* Pin State */
#define Clock_PS                     (* (reg32 *) Clock__PS)
/* Data Register */
#define Clock_DR                     (* (reg32 *) Clock__DR)
/* Input Buffer Disable Override */
#define Clock_INP_DIS                (* (reg32 *) Clock__PC2)

/* Interrupt configuration Registers */
#define Clock_INTCFG                 (* (reg32 *) Clock__INTCFG)
#define Clock_INTSTAT                (* (reg32 *) Clock__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Clock_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Clock__SIO)
    #define Clock_SIO_REG            (* (reg32 *) Clock__SIO)
#endif /* (Clock__SIO_CFG) */

/* USBIO registers */
#if !defined(Clock__PC) && (CY_PSOC4_4200L)
    #define Clock_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Clock_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Clock_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Clock_DRIVE_MODE_SHIFT       (0x00u)
#define Clock_DRIVE_MODE_MASK        (0x07u << Clock_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Clock_H */


/* [] END OF FILE */
