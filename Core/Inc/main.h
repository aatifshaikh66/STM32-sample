/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
		#include "stm32g4xx_ll_rcc.h"
		#include "stm32g4xx_ll_bus.h"
		#include "stm32g4xx_ll_crs.h"
		#include "stm32g4xx_ll_system.h"
		#include "stm32g4xx_ll_exti.h"
		#include "stm32g4xx_ll_cortex.h"
		#include "stm32g4xx_ll_utils.h"
		#include "stm32g4xx_ll_pwr.h"
		#include "stm32g4xx_ll_dma.h"
		#include "stm32g4xx_ll_spi.h"
		#include "stm32g4xx_ll_usart.h"
		#include "stm32g4xx_ll_gpio.h"
		#include "stm32g4xx.h"


		#include "stdio.h"
		#include "stdlib.h"
		#include "string.h"
		#include "stdint.h"		
		#include "math.h"
		#include "ACCMTR.h"
		#include "EEPROM.h"
//		#include "GPS.h"
	
		#if defined(USE_FULL_ASSERT)
		#include "stm32_assert.h"
		#endif /* USE_FULL_ASSERT */


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
		/*********union conversion 4 byte **********/
		typedef union
		{
			uint8_t 	uc_8 [4]; int8_t		sc_8 [4];		
			uint16_t	ui_16[2]; int16_t		si_16[2];		
			uint32_t	ui_32		; int32_t		si_32		;
			float			fl_32		;	
		}unConvo4;

		typedef union
		{
			uint8_t 	uc_8 [8];	int8_t		sc_8 [8];
			uint16_t	ui_16[4];	int16_t		si_16[4];
			uint32_t	ui_32[2];	int32_t		si_32[2];
			uint64_t	ui_64		;	int64_t		si_64		;
			float		fl_32[2]	;	double  dd_64			;			
		}unConvo8;		
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */
	/*Accelerometer Structure*/
		extern stACCMTRVar_All				stVarACCMTRVar_All;
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
