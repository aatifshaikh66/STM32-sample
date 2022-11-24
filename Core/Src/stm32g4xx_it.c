/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
/*****************************************************************************
 **@Function      : USART2_IRQHandler
 **@Descriptions  : This function handles USART2 interrupt request.
 **@parameters    : None
 **@Return        : None
*****************************************************************************/
void USART1_IRQHandler( void )
{
	
//	 /* Check RXNE flag value in ISR register */
//if(LL_USART_IsActiveFlag_RXNE(_GPS_COM) && 
//	 LL_USART_IsEnabledIT_RXNE(_GPS_COM))
//  {  	
//				/* Read one byte from the receive data register */
//			  uint8_t  ucData;
//				ucData = LL_USART_ReceiveData8(_GPS_COM );
//		
//				#if _ENABLE_DEBUGG_GPS
//				//		_DEBUG_ALL_ENABLE_DIABLE
//				//		 printf("%c",ucData);
//				#endif 
//		

//		if((uint16_t)_GPS_COM_MAXBUFF > stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT)
//		{
//			/***************** DATA STORING PROCESS **************************/
//			/**Temporary buffer to store the data**/	
//			stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXBUFF [
//			stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT++] = ucData; 
//			stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXBUFF [
//			stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT  ] = NULL	 ;	
//		}
//		else
//		{
//			/***************** ERROR CHECKING METHOD **************************/
//			/**If the dataoverflow, then reset the buffer and pointer
//			to avoid the hardfault issue, and this data will be discard**/
//			memset( stVarGPS_All.stVarGPSCOMPort.
//			ucGPSCOMRXBUFF,RESET,_GPS_COM_MAXBUFF)	;
//			stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT = RESET	;
//		}
//		
//		/***************** FRAME TERMINATION CHECKING **************************/
//			 stVarGPS_All.stVarGPSCOMPort.ucGPSRXINTRFlag 	  = SET 	;
//		if(stVarGPS_All.stVarGPSCOMPort.ucGPSStartTimerCnt != SET)
//			 stVarGPS_All.stVarGPSCOMPort.ucGPSStartTimerCnt  = SET  	;
//		
//		/**If the '\n' charachter received then switch the array**/
//		if((char)ucData == _GPS_RX_LF_CHAR)
//		{
//			strcpy((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
//										[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT],
//						 (char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXBUFF);
//			stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT++;
//			
//			memset(stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXBUFF
//			,RESET,stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT)	;
//			stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT = RESET	;
//			
//			/***************** ERROR CHECKING METHOD **************************/
//			if( stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT >= _GPS_ARRAY_SIZE)
//				{ stVarGPS_All.stVarGPSCOMPort.ucGPSOverFlowFlag     = SET  ;
//					stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT = RESET; }
//		}
//		
//	}
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
