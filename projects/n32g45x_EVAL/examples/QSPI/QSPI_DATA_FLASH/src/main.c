/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "spi_flash.h"
#include "qspi_cfg.h"
#include "log.h"


/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT
void delay(uint32_t delay_count)
{
    while(delay_count--);
}

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define FLASH_WriteAddress  0x000000
#define FLASH_ReadAddress   FLASH_WriteAddress
#define FLASH_SectorToErase FLASH_WriteAddress

#define PAGE_SIZE   256
#define TX_BUF_SIZE (PAGE_SIZE)
#define RX_BUF_SIZE (PAGE_SIZE)
uint32_t Tx_Buffer[TX_BUF_SIZE] = {0};
uint32_t Rx_Buffer[RX_BUF_SIZE] = {0};

__IO uint16_t Index = 0x0;
volatile TestStatus TransferStatus1 = PASSED, TransferStatus2 = PASSED, TransferStatus3 = PASSED;
__IO uint32_t FlashID = 0;


TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);


/**
 * @brief  Main program.
 */
int main(void)
{   
    /*SystemInit() function has been called by startup file startup_n32g45x.s*/
    log_init(); 
    log_info(" QSPI DATA FLASH Demo \n");
    
    for (Index = 0; Index < TX_BUF_SIZE; Index++)
    {
        Tx_Buffer[Index] = Index;
    }
    
    /* Relase Deep Power-Down Mode and Read Device ID */
    FlashID = QspiFlashReleaseDeepPDMode();
    if(FlashID != sFLASH_GT25Q40_DID)
    {
        TransferStatus3 = FAILED;
    }
    
    /* Get SPI Flash ID */
    FlashID = QspiFlashReadID();
    /* Check the SPI Flash ID */
    if (FlashID == sFLASH_GT25Q40_ID)
    {
        /* Erase SPI FLASH Sector to write on */
        QspiFlashErase(0x20, FLASH_SectorToErase);
        /* Read data from SPI FLASH memory */
        QspiFlashRead(FLASH_SectorToErase, Rx_Buffer, RX_BUF_SIZE);
        
        /* Check the correctness of erasing operation dada */
        for (Index = 0; Index < RX_BUF_SIZE; Index++)
        {
            if (Rx_Buffer[Index] != 0xFF)
            {
                TransferStatus2 = FAILED;
            }
        }
        /* Write Tx_Buffer data to SPI FLASH memory */
        QspiFlashProgram(FLASH_WriteAddress, Tx_Buffer,  TX_BUF_SIZE);
        /* Read data from SPI FLASH memory */
        QspiFlashRead(FLASH_WriteAddress, Rx_Buffer, RX_BUF_SIZE);
        
        /* Check the correctness of written dada */
        for (Index = 0; Index < RX_BUF_SIZE; Index++)
        {
            if (Rx_Buffer[Index] != Tx_Buffer[Index])
            {
                TransferStatus1 = FAILED;
            }
        }
        
        /* Enter Deep Power-Down Mode */
        QspiFlashEnterDeepPDMode();
        delay(100);
        /* Release Deep Power-Down Mode and Read Device ID */
        FlashID = QspiFlashReleaseDeepPDMode();
        if(FlashID != sFLASH_GT25Q40_DID)
        {
            TransferStatus3 = FAILED;
        }

    }
    else
    {
        TransferStatus3 = FAILED;
    }
    
    if(TransferStatus3 == FAILED)
    {
        log_info(" Get DATA FLASH ID fail \n");
    }
    else if(TransferStatus2 == FAILED)
    {
        log_info(" Erase DATA FLASH fail \n");
    }
    else if(TransferStatus1 == FAILED)
    {
        log_info(" Write DATA FLASH fail \n");
    }
    else
    {
        log_info(" QSPI DATA FLASH pass \n");
    }
    
    while(1)
    {
       
    }
   
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

/**
 * @}
 */
