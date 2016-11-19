/*******************************************************************************
* File Name: Data.h  
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

#if !defined(CY_PINS_Data_H) /* Pins Data_H */
#define CY_PINS_Data_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Data_aliases.h"


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
} Data_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Data_Read(void);
void    Data_Write(uint8 value);
uint8   Data_ReadDataReg(void);
#if defined(Data__PC) || (CY_PSOC4_4200L) 
    void    Data_SetDriveMode(uint8 mode);
#endif
void    Data_SetInterruptMode(uint16 position, uint16 mode);
uint8   Data_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Data_Sleep(void); 
void Data_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Data__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Data_DRIVE_MODE_BITS        (3)
    #define Data_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Data_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Data_SetDriveMode() function.
         *  @{
         */
        #define Data_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Data_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Data_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Data_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Data_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Data_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Data_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Data_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Data_MASK               Data__MASK
#define Data_SHIFT              Data__SHIFT
#define Data_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Data_SetInterruptMode() function.
     *  @{
     */
        #define Data_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Data_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Data_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Data_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Data__SIO)
    #define Data_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Data__PC) && (CY_PSOC4_4200L)
    #define Data_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Data_USBIO_DISABLE              ((uint32)(~Data_USBIO_ENABLE))
    #define Data_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Data_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Data_USBIO_ENTER_SLEEP          ((uint32)((1u << Data_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Data_USBIO_SUSPEND_DEL_SHIFT)))
    #define Data_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Data_USBIO_SUSPEND_SHIFT)))
    #define Data_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Data_USBIO_SUSPEND_DEL_SHIFT)))
    #define Data_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Data__PC)
    /* Port Configuration */
    #define Data_PC                 (* (reg32 *) Data__PC)
#endif
/* Pin State */
#define Data_PS                     (* (reg32 *) Data__PS)
/* Data Register */
#define Data_DR                     (* (reg32 *) Data__DR)
/* Input Buffer Disable Override */
#define Data_INP_DIS                (* (reg32 *) Data__PC2)

/* Interrupt configuration Registers */
#define Data_INTCFG                 (* (reg32 *) Data__INTCFG)
#define Data_INTSTAT                (* (reg32 *) Data__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Data_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Data__SIO)
    #define Data_SIO_REG            (* (reg32 *) Data__SIO)
#endif /* (Data__SIO_CFG) */

/* USBIO registers */
#if !defined(Data__PC) && (CY_PSOC4_4200L)
    #define Data_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Data_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Data_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Data_DRIVE_MODE_SHIFT       (0x00u)
#define Data_DRIVE_MODE_MASK        (0x07u << Data_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Data_H */


/* [] END OF FILE */
