/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file bsp_eth.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
**/ 

#ifndef __BSP_ETH_H__
#define __BSP_ETH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

#include "misc.h"
#include "n32g45x.h"
#include "n32g45x_rcc.h"
#include "n32g45x_gpio.h"
#include "n32g45x_exti.h"
#include "n32g457_eth.h"


/** ETH MAC address macro definition **/
#define MAC_ADDR0                              ((uint8_t)0x10U)
#define MAC_ADDR1                              ((uint8_t)0x32U)
#define MAC_ADDR2                              ((uint8_t)0x54U)
#define MAC_ADDR3                              ((uint8_t)0x76U)
#define MAC_ADDR4                              ((uint8_t)0x89U)
#define MAC_ADDR5                              ((uint8_t)0xBAU)


/** Select PHY **/
/* Options: PHY_USE_DM9162EP, PHY_USE_LAN8720, PHY_USE_SR8201F, PHY_USE_NET1001A */
#define PHY_USE_DM9162EP

/** ETH External PHY Macro Definition **/
#ifdef  PHY_USE_DM9162EP
#define PHY_ADDR                                ((uint16_t)0x03U)

#define PHY_BCR                                 ((uint16_t)0x00U)   /* Basic Control Register */
#define PHY_BSR                                 ((uint16_t)0x01U)   /* Basic Status Register */

#define PHY_RESET                               ((uint16_t)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                            ((uint16_t)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M                     ((uint16_t)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                     ((uint16_t)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                      ((uint16_t)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M                      ((uint16_t)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION                     ((uint16_t)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION             ((uint16_t)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                           ((uint16_t)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                             ((uint16_t)0x0400U) /* Isolate PHY from MII */
#define PHY_SPEED_MASK                          ((uint16_t)0x2000U) /* PHY Speed mask */
#define PHY_DUPLEX_MASK                         ((uint16_t)0x0100U) /* PHY Duplex mask */

#define PHY_AUTONEGO_COMPLETE                   ((uint16_t)0x0020U) /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS                       ((uint16_t)0x0004U) /* Valid link established */
#define PHY_JABBER_DETECTION                    ((uint16_t)0x0002U) /* Jabber condition detected */

#define PHY_SDSR                                ((uint16_t)0x11U)   /* The offset of the status register indicating speed and duplex mode in auto-negotiation mode */
#define PHY_FULLDUPLEX100M_STS                  ((uint16_t)0x8000U) /* PHY 100M full-duplex status */
#define PHY_HALFDUPLEX100M_STS                  ((uint16_t)0x4000U) /* PHY 100M half-duplex status */
#define PHY_FULLDUPLEX10M_STS                   ((uint16_t)0x2000U) /* PHY 10M full-duplex status */
#define PHY_HALFDUPLEX10M_STS                   ((uint16_t)0x1000U) /* PHY 10M half-duplex status */
#define PHY_SPEEDDUPLEX_MASK                    ((uint16_t)0xF000U) /* PHY Speed Duplex mask */
#endif /* PHY_USE_DM9162EP */

#ifdef  PHY_USE_LAN8720
#define PHY_ADDR                                ((uint16_t)0x01U)

#define PHY_BCR                                 ((uint16_t)0x00U)   /* Basic Control Register */
#define PHY_BSR                                 ((uint16_t)0x01U)   /* Basic Status Register */

#define PHY_RESET                               ((uint16_t)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                            ((uint16_t)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M                     ((uint16_t)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                     ((uint16_t)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                      ((uint16_t)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M                      ((uint16_t)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION                     ((uint16_t)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION             ((uint16_t)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                           ((uint16_t)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                             ((uint16_t)0x0400U) /* Isolate PHY from MII */
#define PHY_SPEED_MASK                          ((uint16_t)0x2000U) /* PHY Speed mask */
#define PHY_DUPLEX_MASK                         ((uint16_t)0x0100U) /* PHY Duplex mask */

#define PHY_AUTONEGO_COMPLETE                   ((uint16_t)0x0020U) /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS                       ((uint16_t)0x0004U) /* Valid link established */
#define PHY_JABBER_DETECTION                    ((uint16_t)0x0002U) /* Jabber condition detected */

#define PHY_SDSR                                ((uint16_t)0x1FU)   /* The offset of the status register indicating speed and duplex mode in auto-negotiation mode */
#define PHY_FULLDUPLEX100M_STS                  ((uint16_t)0x0018U) /* PHY 100M full-duplex status */
#define PHY_HALFDUPLEX100M_STS                  ((uint16_t)0x0008U) /* PHY 100M half-duplex status */
#define PHY_FULLDUPLEX10M_STS                   ((uint16_t)0x0014U) /* PHY 10M full-duplex status */
#define PHY_HALFDUPLEX10M_STS                   ((uint16_t)0x0004U) /* PHY 10M half-duplex status */
#define PHY_SPEEDDUPLEX_MASK                    ((uint16_t)0x001CU) /* PHY Speed Duplex mask */
#endif /* PHY_USE_LAN8720 */

#ifdef  PHY_USE_SR8201F
#define PHY_ADDR                                ((uint16_t)0x01U)

#define PHY_BCR                                 ((uint16_t)0x00U)   /* Basic Control Register */
#define PHY_BSR                                 ((uint16_t)0x01U)   /* Basic Status Register */

#define PHY_RESET                               ((uint16_t)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                            ((uint16_t)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M                     ((uint16_t)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                     ((uint16_t)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                      ((uint16_t)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M                      ((uint16_t)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION                     ((uint16_t)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION             ((uint16_t)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                           ((uint16_t)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                             ((uint16_t)0x0400U) /* Isolate PHY from MII */
#define PHY_SPEED_MASK                          ((uint16_t)0x2000U) /* PHY Speed mask */
#define PHY_DUPLEX_MASK                         ((uint16_t)0x0100U) /* PHY Duplex mask */

#define PHY_AUTONEGO_COMPLETE                   ((uint16_t)0x0020U) /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS                       ((uint16_t)0x0004U) /* Valid link established */
#define PHY_JABBER_DETECTION                    ((uint16_t)0x0002U) /* Jabber condition detected */

#define PHY_SDSR                                ((uint16_t)0x00U)   /* The offset of the status register indicating speed and duplex mode in auto-negotiation mode */
#define PHY_FULLDUPLEX100M_STS                  ((uint16_t)0x2100U) /* PHY 100M full-duplex status */
#define PHY_HALFDUPLEX100M_STS                  ((uint16_t)0x2000U) /* PHY 100M half-duplex status */
#define PHY_FULLDUPLEX10M_STS                   ((uint16_t)0x0100U) /* PHY 10M full-duplex status */
#define PHY_HALFDUPLEX10M_STS                   ((uint16_t)0x0000U) /* PHY 10M half-duplex status */
#define PHY_SPEEDDUPLEX_MASK                    ((uint16_t)0x2100U) /* PHY Speed Duplex mask */
#endif /* PHY_USE_SR8201F */

#ifdef  PHY_USE_RTL8211EG
#define PHY_ADDR                                ((uint16_t)0x04U)

#define PHY_BCR                                 ((uint16_t)0x00U)   /* Basic Control Register */
#define PHY_BSR                                 ((uint16_t)0x01U)   /* Basic Status Register */
#define PHY_GBCR                                ((uint16_t)0x09U)   /* 1000Base-T Basic Control Register */
#define PHY_GBSR                                ((uint16_t)0x0AU)   /* 1000Base-T Basic Status Register */
#define PHY_GESR                                ((uint16_t)0x0FU)   /* 1000Base-T Extended Status Register */

#define PHY_RESET                               ((uint16_t)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                            ((uint16_t)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M                     ((uint16_t)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                     ((uint16_t)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                      ((uint16_t)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M                      ((uint16_t)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION                     ((uint16_t)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION             ((uint16_t)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                           ((uint16_t)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                             ((uint16_t)0x0400U) /* Isolate PHY from GMII */
#define PHY_SPEED_MASK                          ((uint16_t)0x2000U) /* PHY Speed mask */
#define PHY_DUPLEX_MASK                         ((uint16_t)0x0100U) /* PHY Duplex mask */

#define PHY_AUTONEGO_COMPLETE                   ((uint16_t)0x0020U) /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS                       ((uint16_t)0x0004U) /* Valid link established */
#define PHY_JABBER_DETECTION                    ((uint16_t)0x0002U) /* Jabber condition detected */

#define PHY_SDSR                                ((uint16_t)0x11U)   /* The offset of the status register indicating speed and duplex mode in auto-negotiation mode */
#define PHY_FULLDUPLEX1000M_STS                 ((uint16_t)0xA000U) /* PHY 1000M full-duplex status */
#define PHY_HALFDUPLEX1000M_STS                 ((uint16_t)0x8000U) /* PHY 1000M half-duplex status */
#define PHY_FULLDUPLEX100M_STS                  ((uint16_t)0x6000U) /* PHY 100M full-duplex status */
#define PHY_HALFDUPLEX100M_STS                  ((uint16_t)0x4000U) /* PHY 100M half-duplex status */
#define PHY_FULLDUPLEX10M_STS                   ((uint16_t)0x2000U) /* PHY 10M full-duplex status */
#define PHY_HALFDUPLEX10M_STS                   ((uint16_t)0x0000U) /* PHY 10M half-duplex status */
#define PHY_SPEEDDUPLEX_MASK                    ((uint16_t)0xE000U) /* PHY Speed Duplex mask */
#endif /* PHY_USE_RTL8211EG */

#ifdef  PHY_USE_NET1001A
#if USE_ETH1
#define PHY_ADDR                                ((uint16_t)0x01U)
#else
#define PHY_ADDR                                ((uint16_t)0x02U)
#endif

#define PHY_BCR                                 ((uint16_t)0x00U)   /* Basic Control Register */
#define PHY_BSR                                 ((uint16_t)0x01U)   /* Basic Status Register */

#define PHY_RESET                               ((uint16_t)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                            ((uint16_t)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M                     ((uint16_t)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                     ((uint16_t)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                      ((uint16_t)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M                      ((uint16_t)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION                     ((uint16_t)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION             ((uint16_t)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                           ((uint16_t)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                             ((uint16_t)0x0400U) /* Isolate PHY from MII */
#define PHY_SPEED_MASK                          ((uint16_t)0x2000U) /* PHY Speed mask */
#define PHY_DUPLEX_MASK                         ((uint16_t)0x0100U) /* PHY Duplex mask */

#define PHY_AUTONEGO_COMPLETE                   ((uint16_t)0x0020U) /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS                       ((uint16_t)0x0004U) /* Valid link established */
#define PHY_JABBER_DETECTION                    ((uint16_t)0x0002U) /* Jabber condition detected */

#define PHY_SDSR                                ((uint16_t)0x00U)   /* The offset of the status register indicating speed and duplex mode in auto-negotiation mode */
#define PHY_FULLDUPLEX100M_STS                  ((uint16_t)0x2100U) /* PHY 100M full-duplex status */
#define PHY_HALFDUPLEX100M_STS                  ((uint16_t)0x2000U) /* PHY 100M half-duplex status */
#define PHY_FULLDUPLEX10M_STS                   ((uint16_t)0x0100U) /* PHY 10M full-duplex status */
#define PHY_HALFDUPLEX10M_STS                   ((uint16_t)0x0000U) /* PHY 10M half-duplex status */
#define PHY_SPEEDDUPLEX_MASK                    ((uint16_t)0x2100U) /* PHY Speed Duplex mask */
#endif /* PHY_USE_NET1001A */


typedef struct
{
    GPIO_Module   *GPIOx;
    uint16_t       Pin;
    GPIO_SpeedType Speed;
    GPIO_ModeType  Mode;
} ETH_PinType;



void ETH_BSP_GPIOInit(void);
void ETH_BSP_NVICInit(void);
void ETH_BSP_ClockCmd(FunctionalState Cmd);
uint16_t ETH_BSP_GetPhyLinkStatus(uint16_t phyAddr, uint16_t phyReg);
uint32_t ETH_BSP_PHYInit(ETH_InitType* ETH_InitStruct);
ErrorStatus ETH_BSP_Init(void);
void ETH_BSP_DeInit(void);



#ifdef __cplusplus
}
#endif

#endif /*__BSP_ETH_H__ */
