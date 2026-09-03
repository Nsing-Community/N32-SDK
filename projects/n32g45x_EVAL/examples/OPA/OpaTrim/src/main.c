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
#include "log.h"
#include "delay.h"
#include "string.h"


typedef struct{
    uint8_t Triming_Data_P;
    uint8_t Triming_Data_N;
}sTriming_Data;

#define  OPAx_VREFOPT_MASK (0x00C00000U)
#define  OPAx_VREFOPT_PMOS (0x00400000U)
#define  OPAx_VREFOPT_NMOS (0x00C00000U)

#define  OPA1_PTrim_MASK  (0x00001F00U)
#define  OPA1_NTrim_MASK  (0x0000001FU)
#define  OPA2_PTrim_MASK  (0x1F000000U)
#define  OPA2_NTrim_MASK  (0x001F0000U)

#define  OPA3_PTrim_MASK  (0x00001F00U)
#define  OPA3_NTrim_MASK  (0x0000001FU)
#define  OPA4_PTrim_MASK  (0x1F000000U)
#define  OPA4_NTrim_MASK  (0x001F0000U)
/** @addtogroup OPAMP_OPA
 * @{
 */
sTriming_Data Triming_Data = {0,0};
USART_InitType USART_InitStructure;


void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPAMP_Configuration(void);

void OPA_TrimPValueSet(OPAMPX OPAMPx, uint8_t PTrimValue);
void OPA_TrimNValueSet(OPAMPX OPAMPx, uint8_t NTrimValue);
void OPA_TrimingProcessHandler(void);

void OPAMP_ConfigOPT(OPAMPX OPAMPx, uint32_t sel)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    *pCs &= (~OPAx_VREFOPT_MASK);
    *pCs |= sel;
}

/**
 * @brief   Main program,Test PGA is work ok? Opa out Pin can view by scope
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();
    /*log init*/
    log_init();
    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    OPA_TrimingProcessHandler();
    while (1)
    {
        
    }
}

/**
 * @brief  Configures the Opa.
 */
void OPAMP_Configuration(void)
{
    OPAMP_Enable(OPAMP1, ENABLE);
    OPAMP_ConfigOPT(OPAMP1,OPAx_VREFOPT_NMOS);
    OPAMP_CalibrationEnable(OPAMP1, ENABLE);
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable OPAMP USART2 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_OPAMP, ENABLE);
    
    /* Enable GPIOA, GPIOB, GPIOC and GPIOD clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure OPAMP1_VP(PA1) as analog inputs */
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.Pin       = GPIO_PIN_1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}


void OPA_TrimPValueSet(OPAMPX OPAMPx, uint8_t PTrimValue)
{
    if(OPAMPx == OPAMP1)
    {
         AFEC->TRIMR3 &= (~(OPA1_PTrim_MASK));
         AFEC->TRIMR3 |= (( (uint32_t)PTrimValue <<8U));
    }
    else if(OPAMPx == OPAMP2)
    {
         AFEC->TRIMR3 &= (~(OPA2_PTrim_MASK));
         AFEC->TRIMR3 |= (( (uint32_t)PTrimValue <<24U));
    }
    else if(OPAMPx == OPAMP3)
    {
         AFEC->TRIMR4 &= (~(OPA3_PTrim_MASK));
         AFEC->TRIMR4 |= (( (uint32_t)PTrimValue <<8U));
    }
    else if(OPAMPx == OPAMP4)
    {
         AFEC->TRIMR4 &= (~(OPA4_PTrim_MASK));
         AFEC->TRIMR4 |= (( (uint32_t)PTrimValue <<24U));
    }
    else
    {
        /*no process*/
    }
}

void OPA_TrimNValueSet(OPAMPX OPAMPx, uint8_t NTrimValue)
{
    if(OPAMPx == OPAMP1)
    {
         AFEC->TRIMR3 &= (~(OPA1_NTrim_MASK));
         AFEC->TRIMR3 |= ( (uint32_t)NTrimValue);
    }
    else if(OPAMPx == OPAMP2)
    {
         AFEC->TRIMR3 &= (~(OPA2_NTrim_MASK));
         AFEC->TRIMR3 |= (( (uint32_t)NTrimValue <<16U));
    }
    else if(OPAMPx == OPAMP3)
    {
         AFEC->TRIMR4 &= (~(OPA3_NTrim_MASK));
         AFEC->TRIMR4 |= ( (uint32_t)NTrimValue);
    }
    else if(OPAMPx == OPAMP4)
    {
         AFEC->TRIMR4 &= (~(OPA4_NTrim_MASK));
         AFEC->TRIMR4 |= (( (uint32_t)NTrimValue <<16U));
    }
    else
    {
        /*no process*/
    }
}


void OPA_TrimingProcessHandler(void)
{
    uint32_t i = 0;
    OPAMP_Configuration();
    /* Start Calibrate NMOS*/
    for(i = 0;i<= (0x1F); i++)
    {
        OPA_TrimNValueSet(OPAMP1,i);  
        systick_delay_us(150);
        if(OPAMP_IsCalOutHigh(OPAMP1) == false)
        {
            Triming_Data.Triming_Data_N = i;
            break;
        }
    }
    /*Switch to Calibrate PMOS */
    OPAMP_ConfigOPT(OPAMP1,OPAx_VREFOPT_PMOS);
    
    /* Start Calibrate PMOS*/
    for(i = 0;i<= (0x1F); i++)
    {
        OPA_TrimPValueSet(OPAMP1,i);  
        systick_delay_us(150);
        if(OPAMP_IsCalOutHigh(OPAMP1) == true)
        {
            Triming_Data.Triming_Data_P = i;
            break;
        }
    }
    OPAMP_Enable(OPAMP1, DISABLE);
    log_debug("Calibration over, Pmos value = 0x%x,Nmos value 0x%x\r\n",Triming_Data.Triming_Data_P,Triming_Data.Triming_Data_N);
    /* Save triming data , load data to Trim regs when power up*/
    
}



#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */
