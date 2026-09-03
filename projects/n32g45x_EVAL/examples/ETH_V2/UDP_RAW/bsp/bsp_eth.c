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
*\*\file bsp_eth.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
**/ 

#include "bsp_eth.h"

#define ETH_INTERFACE ETH_INTERFACE_RMII

/* Local MAC address */
uint8_t aMACAddr[6] = {0};

/* ETH DMA TX RX descriptor physical address */
ETH_DMADescType aDMARxDscrTab[ETH_RXBUFNB];
ETH_DMADescType aDMATxDscrTab[ETH_TXBUFNB];

/* ETH TX RX buffer physical address */
uint8_t aRxBuffer[ETH_RXBUFNB][ETH_RX_BUF_SIZE];
uint8_t aTxBuffer[ETH_TXBUFNB][ETH_TX_BUF_SIZE];

/* Global ETH initialize structure variable */
ETH_InitType sETH_InitParam;

/* ETH RMII pins remap group 0 */
ETH_PinType ETHRMIIPinsRemapG0[] = 
{
    /* ETH_RMII_CRS_DV */
    {GPIOA, GPIO_PIN_7,  GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING},
    /* ETH_RMII_TXD0 */
    {GPIOB, GPIO_PIN_12, GPIO_Speed_50MHz, GPIO_Mode_AF_PP},
    /* ETH_RMII_TXD1 */
    {GPIOB, GPIO_PIN_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP},
    /* ETH_RMII_TXEN */
    {GPIOB, GPIO_PIN_11, GPIO_Speed_50MHz, GPIO_Mode_AF_PP},
    /* ETH_RMII_RXD0 */
    {GPIOC, GPIO_PIN_4,  GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING},
    /* ETH_RMII_RXD1 */
    {GPIOC, GPIO_PIN_5,  GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING},
    /* ETH_RMII_REFCLK */
    {GPIOA, GPIO_PIN_1,  GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING},
    /* ETH_MDC */
    {GPIOC, GPIO_PIN_1,  GPIO_Speed_50MHz, GPIO_Mode_AF_PP},
    /* ETH_MDIO */
    {GPIOA, GPIO_PIN_2,  GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
};

/** ETH_BSP Private Defines **/


/** ETH_BSP Driving Functions Declaration **/

/**
*\*\name    ETH_BSP_GPIOInit.
*\*\fun     Initialization the GPIOs used by the ETH module.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_BSP_GPIOInit(void)
{
    __IO uint32_t index = 0;
    GPIO_InitType GPIO_InitStructure;

    /* Initialize the pins */
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Using ETH with RMII hardware interface */
    for (index = 0; index < sizeof(ETHRMIIPinsRemapG0) / sizeof(ETH_PinType); index++)
    {
        GPIO_InitStructure.Pin        = ETHRMIIPinsRemapG0[index].Pin;
        GPIO_InitStructure.GPIO_Mode  = ETHRMIIPinsRemapG0[index].Mode;
        GPIO_InitStructure.GPIO_Speed = ETHRMIIPinsRemapG0[index].Speed;
        GPIO_InitPeripheral(ETHRMIIPinsRemapG0[index].GPIOx, &GPIO_InitStructure);
    }
}

/**
*\*\name    ETH_BSP_NVICInit.
*\*\fun     Initialization Configuration NVIC.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_BSP_NVICInit(void)
{
    NVIC_InitType NVIC_InitStructure;
    
    /* Configures the priority group */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    /* Configures the ETH global interrupt NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = ETH_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    ETH_BSP_ClockCmd.
*\*\fun     Enables or disables the ETH, GPIO, AFIO, etc. clocks.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_BSP_ClockCmd(FunctionalState Cmd)
{
    /* Enable or disable GPIOx Clock */
    RCC_EnableAPB2PeriphClk((RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB
                           | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD
                           | RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_GPIOF
                           | RCC_APB2_PERIPH_GPIOG), Cmd);

    /* Enable or disable AFIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, Cmd);

    /* Enable or disable ETH Clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ETHMAC, Cmd);
}

/**
*\*\name    ETH_BSP_GetPhyLinkStatus.
*\*\fun     Get PHY link status.
*\*\param   phyAddr:
*\*\          - PHY port address.
*\*\param   phyReg:
*\*\          - PHY register address.
*\*\return  Acquired PHY link state value containing speed core duplex mode
**/
uint16_t ETH_BSP_GetPhyLinkStatus(uint16_t phyAddr, uint16_t phyReg)
{
    uint16_t retVlaue;
    uint32_t regVlaue;
    
    /* Read the PHY register */
    regVlaue = ETH_ReadPHYRegister((uint32_t)phyAddr, (uint32_t)phyReg);

    /* Get link status */
    retVlaue = ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_FULLDUPLEX10M_STS)? ETH_LINK_10FULL :
               ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_HALFDUPLEX10M_STS)? ETH_LINK_10HALF :
               ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_FULLDUPLEX100M_STS)? ETH_LINK_100FULL :
               ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_HALFDUPLEX100M_STS)? ETH_LINK_100HALF :
               0U;
    
    return retVlaue;
}

uint32_t ETH_BSP_PHYInit(ETH_InitType* ETH_InitStruct)
{
    uint32_t rPHYRegVlaue = 0U;
    uint32_t wPHYRegVlaue = 0U;
    __IO uint32_t TickCnt = 0U;
    uint32_t TempDelay    = ETH_PHY_CONFIG_DELAY;
    
    /* Put the PHY in reset mode */
    if (!(ETH_WritePHYRegister(PHY_ADDR, PHY_BCR, PHY_RESET)))
    {
        /* Return ERROR */
        return ETH_ERROR;
    }
    
    /* Delay to assure PHY reset */
    ETH_Delay(TempDelay);

    /* Wait for linked status */
    do
    {
        TickCnt++;
        /* Read the PHY register */
        rPHYRegVlaue = ETH_ReadPHYRegister(PHY_ADDR, PHY_BSR);

        if (TickCnt == PHY_READ_TO)
        {
            /* Return ERROR */
            return ETH_ERROR;
        }
    } while ((rPHYRegVlaue & PHY_LINKED_STATUS) != PHY_LINKED_STATUS);

    /* Read the PHY register */
    rPHYRegVlaue = ETH_ReadPHYRegister(PHY_ADDR, PHY_BCR);

    if (ETH_InitStruct->AutoNegotiation != ETH_AUTONEG_DISABLE)
    {
        wPHYRegVlaue = rPHYRegVlaue;
        /* Enable PHY auto-negotiation */
        wPHYRegVlaue |= PHY_AUTONEGOTIATION;
        /* Write the PHY register */
        if (!(ETH_WritePHYRegister(PHY_ADDR, PHY_BCR, wPHYRegVlaue)))
        {
            /* Return ERROR */
            return ETH_ERROR;
        }

        /* Delay to assure PHY set */
        ETH_Delay(TempDelay);

        /* Reset counter */
        TickCnt = 0;
        /* Wait until the auto-negotiation will be completed */
        do
        {
            TickCnt++;
            /* Read the PHY register */
            rPHYRegVlaue = ETH_ReadPHYRegister(PHY_ADDR, PHY_BSR);

            if (TickCnt == PHY_READ_TO)
            {
                /* Return ERROR */
                return ETH_ERROR;
            }
        } while ((rPHYRegVlaue & PHY_AUTONEGO_COMPLETE) != PHY_AUTONEGO_COMPLETE);

        /* Set the MAC speed and duplex mode parameters by the read link status */
        switch (ETH_BSP_GetPhyLinkStatus(PHY_ADDR, PHY_SDSR))
        {
            case ETH_LINK_10FULL:
                /* 10M */
                ETH_InitStruct->SpeedMode  = ETH_SPEED_MODE_10M;
                /* Full-duplex */
                ETH_InitStruct->DuplexMode = ETH_DUPLEX_MODE_FULL;
                break;
            case ETH_LINK_10HALF:
                /* 10M */
                ETH_InitStruct->SpeedMode  = ETH_SPEED_MODE_10M;
                /* Half-duplex */
                ETH_InitStruct->DuplexMode = ETH_DUPLEX_MODE_HALF;
                break;
            case ETH_LINK_100FULL:
                /* 100M */
                ETH_InitStruct->SpeedMode  = ETH_SPEED_MODE_100M;
                /* Full-duplex */
                ETH_InitStruct->DuplexMode = ETH_DUPLEX_MODE_FULL;
                break;
            case ETH_LINK_100HALF:
                /* 100M */
                ETH_InitStruct->SpeedMode  = ETH_SPEED_MODE_100M;
                /* Half-duplex */
                ETH_InitStruct->DuplexMode = ETH_DUPLEX_MODE_HALF;
                break;
            default:
                /* Return ERROR */
                return ETH_ERROR;
        }
    }
    else
    {
        wPHYRegVlaue = rPHYRegVlaue;
        /* Disable PHY auto-negotiation */
        wPHYRegVlaue &= (~PHY_AUTONEGOTIATION);
        /* Clear the PHY speed bit */
        wPHYRegVlaue &= (~PHY_SPEED_MASK);
        /* Clear the PHY duplex bit */
        wPHYRegVlaue &= (~PHY_DUPLEX_MASK);

        /* Set PHY speed mode */
        if (ETH_InitStruct->SpeedMode == ETH_SPEED_MODE_100M)
        {
            wPHYRegVlaue |= PHY_SPEED_MASK;
        }
        /* Set PHY duplex mode */
        if (ETH_InitStruct->DuplexMode == ETH_DUPLEX_MODE_FULL)
        {
            wPHYRegVlaue |= PHY_DUPLEX_MASK;
        }

        /* Write the PHY register */
        if (!(ETH_WritePHYRegister(PHY_ADDR, PHY_BCR, wPHYRegVlaue)))
        {
            /* Return ERROR */
            return ETH_ERROR;
        }

        /* Delay to assure PHY set */
        ETH_Delay(TempDelay);
    }

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_BSP_Init.
*\*\fun     ETH initialization function, called in the low_level_init() function.
*\*\param   none
*\*\return  SUCCESS or ERROR.
**/
ErrorStatus ETH_BSP_Init(void)
{
    __IO uint32_t TickCnt   = 0U;
    __IO uint32_t TempIndex = 0U;
    
    /* Set the local MAC address */
    aMACAddr[0] = MAC_ADDR0;
    aMACAddr[1] = MAC_ADDR1;
    aMACAddr[2] = MAC_ADDR2;
    aMACAddr[3] = MAC_ADDR3;
    aMACAddr[4] = MAC_ADDR4;
    aMACAddr[5] = MAC_ADDR5;
    
    memset(aRxBuffer, 0, sizeof(aRxBuffer));
    memset(aTxBuffer, 0, sizeof(aTxBuffer));
    memset(aDMARxDscrTab, 0, sizeof(aDMARxDscrTab));
    memset(aDMATxDscrTab, 0, sizeof(aDMATxDscrTab));

    /* Enable related clocks */
    ETH_BSP_ClockCmd(ENABLE);
    /* Configuring GPIOs */
    ETH_BSP_GPIOInit();
    /* Configuring NVIC */
    ETH_BSP_NVICInit();

    /* DeInitializes the ETH peripheral */
    ETH_DeInit();
    /* Set ETH initialization parameters by default */
    ETH_InitStruct(&sETH_InitParam);
    /* Modify ETH initialization parameters */
    /*------------------------   MAC   -----------------------------------*/
    sETH_InitParam.AutoNegotiation             = ETH_AUTONEG_ENABLE;
    sETH_InitParam.LoopbackMode                = ETH_LOOPBACK_MODE_DISABLE;
    sETH_InitParam.RetryTransmission           = ETH_RETRY_TRANSMISSION_DISABLE;
    sETH_InitParam.AutomaticPadCRCStrip        = ETH_AUTO_PAD_CRC_STRIP_DISABLE;
    sETH_InitParam.RxAll                       = ETH_RX_ALL_DISABLE;
    sETH_InitParam.BroadcastFramesReception    = ETH_BROADCAST_FRAMES_RECEPTION_ENABLE;
    sETH_InitParam.PromiscuousMode             = ETH_PROMISCUOUS_MODE_DISABLE;
    sETH_InitParam.MulticastFramesFilter       = ETH_MULTICAST_FRAMES_FILTER_PERFECT;
    sETH_InitParam.UnicastFramesFilter         = ETH_UNICAST_FRAMES_FILTER_PERFECT;
    sETH_InitParam.ChecksumOffload             = ETH_CHECKSUM_OFFLOAD_DISABLE;
    /*------------------------   DMA   -----------------------------------*/
    sETH_InitParam.DropTCPIPChecksumErrorFrame = ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_ENABLE;
    sETH_InitParam.RxStoreForward              = ETH_RX_STORE_FORWARD_ENABLE;
    sETH_InitParam.TxStoreForward              = ETH_TX_STORE_FORWARD_ENABLE;
    sETH_InitParam.ForwardErrorFrames          = ETH_FORWARD_ERROR_FRAMES_DISABLE;
    sETH_InitParam.ForwardUndersizedGoodFrames = ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_DISABLE;
    sETH_InitParam.SecondFrameOperate          = ETH_SECOND_FRAME_OPERATE_ENABLE;
    sETH_InitParam.AddrAlignedBeats            = ETH_ADDR_ALIGNED_BEATS_ENABLE;
    sETH_InitParam.FixedBurst                  = ETH_FIXED_BURST_ENABLE;
    sETH_InitParam.RxDMABurstLen               = ETH_RX_DMA_BURST_LEN_32BEAT;
    sETH_InitParam.TxDMABurstLen               = ETH_TX_DMA_BURST_LEN_32BEAT;

    /* Selects the Ethernet media interface by GPIO*/
    if (ETH_INTERFACE == ETH_INTERFACE_RMII)
    {
        GPIO_ETH_ConfigMediaInterface(GPIO_ETH_RMII_CFG);
    }
    else
    {
        GPIO_ETH_ConfigMediaInterface(GPIO_ETH_MII_CFG);
    }

    /* Software reset */
    ETH_SoftwareReset();
    /* Wait for software reset */
    while (ETH_GetSoftwareResetStatus() == SET)
    {
        TickCnt++;
        if (TickCnt == ETH_SWRESET_TIMEOUT)
        {
            /* Timeout, possibly clock error */
            return ERROR;
        }
    }

    /* Checks whether initializing the ETH was successful */
    if (ETH_Init(&sETH_InitParam, ETH_BSP_PHYInit) != ETH_SUCCESS)
    {
        /* ETH initialization failed */
        return ERROR;
    }

    /* Enable the Ethernet Rx Interrupt */
    ETH_DMAITConfig(ETH_DMA_INT_NIS | ETH_DMA_INT_RX, ENABLE);

    /* Initialize MAC address in ethernet MAC */
    ETH_MACAddressConfig(ETH_MAC_ADDR0, aMACAddr);

    /* Initialize Tx Descriptors list: Chain Mode */
    ETH_DMATxDescChainInit(aDMATxDscrTab, (uint8_t *)aTxBuffer, ETH_TXBUFNB);
    /* Initialize Rx Descriptors list: Chain Mode  */
    ETH_DMARxDescChainInit(aDMARxDscrTab, (uint8_t *)aRxBuffer, ETH_RXBUFNB);

    /* Enable Ethernet Rx interrrupt */
    for(TempIndex = 0; TempIndex < ETH_RXBUFNB; TempIndex++)
    {
        ETH_DMARxDescReceiveITConfig(&aDMARxDscrTab[TempIndex], ENABLE);
    }

    if (sETH_InitParam.ChecksumOffload == ETH_CHECKSUM_OFFLOAD_ENABLE)
    {
        /* Enable the checksum insertion for the Tx frames */
        for(TempIndex = 0; TempIndex < ETH_TXBUFNB; TempIndex++)
        {
            ETH_DMATxDescChecksumInsertionConfig(&aDMATxDscrTab[TempIndex], ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_FULL);
        }
    }

    return SUCCESS;
}

/**
*\*\name    ETH_BSP_DeInit.
*\*\fun     ETH DeInitializes function.
*\*\param   none
*\*\return  none.
**/
void ETH_BSP_DeInit(void)
{
    /* Clear the sETH_InitParam structure variable */
    memset(&sETH_InitParam, 0, sizeof(ETH_InitType));
    /* DISABLE related clocks */
    ETH_BSP_ClockCmd(DISABLE);
}


