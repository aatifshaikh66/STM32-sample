/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 	#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#endif /* __GNUC__ */
	/* USER CODE END Includes */

	
/* Private typedef -----------------------------------------------------------*/
	#define _FLASH_GPIO_PORT					GPIOB
	#define _FLASH_GPIO_PIN_CS				LL_GPIO_PIN_12		
	#define _FLASH_CMD_RDID					 (uint8_t)0x9F
	#define _FLASH_TYPE_W25Q128			 (uint16_t)0x4018	
	#define _FLASH_CS_HIGH						LL_GPIO_SetOutputPin  (_FLASH_GPIO_PORT, _FLASH_GPIO_PIN_CS);
	#define _FLASH_CS_LOW							LL_GPIO_ResetOutputPin(_FLASH_GPIO_PORT, _FLASH_GPIO_PIN_CS);			
	
	
	#define _ACCMTR_CS_HIGH						LL_GPIO_SetOutputPin  (GPIOA, LL_GPIO_PIN_8);
	#define _ACCMTR_CS_LOW						LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);				
	
	
	/*Accelerometer Structure*/
	stACCMTRVar_All	stVarACCMTRVar_All;
	
	unConvo4  			unVarConvo4;
	
	
/* USER CODE BEGIN PTD */
/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
 PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
					LL_USART_TransmitData8(USART3, (uint8_t) ch);
	while ( LL_USART_IsActiveFlag_TXE(USART3) == RESET ){  }						    
						
  return ch;
}
/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4)
  {  }
	
  LL_PWR_EnableRange1BoostMode();
  
	LL_RCC_HSI_Enable();
   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_PLL_ConfigDomain_SYS
 (LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();

  LL_RCC_PLL_Enable();
  /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {  }

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {  }

  /* Insure 1µs transition state at intermediate medium speed clock based on DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while(DWT->CYCCNT < 100);
  
	/* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

//  LL_Init1msTick(170000000);
  LL_SetSystemCoreClock(170000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);

}
/* USER CODE END PFP */
/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */

void MX_SPI1_Init(void)
{
	
  /* USER CODE BEGIN SPI1_Init 0 */
  /* USER CODE END SPI1_Init 0 */
  LL_SPI_InitTypeDef SPI_InitStruct   = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1 );
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**SPI1 GPIO Configuration
  PA5   ------> SPI1_SCK
  PA6   ------> SPI1_MISO
  PA7   ------> SPI1_MOSI  */
  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	
  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	_ACCMTR_CS_HIGH 

  /* USER CODE BEGIN SPI1_Init 1 */
  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  SPI_InitStruct.TransferDirection 	= LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode 							= LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth 					= LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPhase 				= LL_SPI_PHASE_2EDGE;
  SPI_InitStruct.ClockPolarity 			= LL_SPI_POLARITY_HIGH;	
  SPI_InitStruct.NSS 								= LL_SPI_NSS_SOFT;
  SPI_InitStruct.BitOrder 					= LL_SPI_MSB_FIRST;	
  SPI_InitStruct.BaudRate 					= LL_SPI_BAUDRATEPRESCALER_DIV8;
  SPI_InitStruct.CRCCalculation 		= LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly 						= (uint8_t)7;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
	LL_SPI_Enable(SPI1);	


	// LL_SPI_EnableNSSPulseMgt(SPI1);
  /* USER CODE BEGIN SPI1_Init 2 */
  /* USER CODE END SPI1_Init 2 */
}

/******************************************************************************
 **@Function 			: FnFlashSPIXRdWr
 **@Descriptions	: 
 **@parameters		: 
 **@return				:	
 ****************************************************************************/
uint8_t FnSPI1RdWr( uint8_t ucSendData)   
{ 
	
	uint8_t ucRet = _DNumber_0	;
	/* Write character in Data register.
	TXE flag is cleared by reading data in DR register */	
		while(LL_SPI_IsActiveFlag_TXE (SPI1)  == RESET){ };
		LL_SPI_TransmitData8(SPI1, ucSendData);
	/* Read character in Data register.
	RXNE flag is cleared by reading data in DR register */					 
		while(LL_SPI_IsActiveFlag_RXNE(SPI1)  == RESET){};
		ucRet = LL_SPI_ReceiveData8(SPI1);			
	return  ucRet	;		

}

/* USER CODE END PFP */
/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
void MX_SPI2_Init(void)
{
	
  /* USER CODE BEGIN SPI1_Init 0 */
  /* USER CODE END   SPI1_Init 0 */
  LL_SPI_InitTypeDef SPI_InitStruct   = { RESET };
  LL_GPIO_InitTypeDef GPIO_InitStruct = { RESET };

	
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2 );
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA); 
	
	
	/**SPI1 GPIO Configuration
  PB13   ------> SPI1_SCK
  PB14   ------> SPI1_MISO
  PB15   ------> SPI1_MOSI  */	
  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_14;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 	= LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_12;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	_FLASH_CS_HIGH

  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	_EEPROM_CS_HIGH

  /* USER CODE BEGIN SPI1_Init 1 */
  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  SPI_InitStruct.TransferDirection 	= LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode 							= LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth 					= LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity 			= LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase 				= LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS 								= LL_SPI_NSS_SOFT;
  SPI_InitStruct.BitOrder 					= LL_SPI_MSB_FIRST;	
  SPI_InitStruct.BaudRate 					= LL_SPI_BAUDRATEPRESCALER_DIV16;
  SPI_InitStruct.CRCCalculation 		= LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly 						= (uint8_t)7;
  LL_SPI_Init(SPI2, &SPI_InitStruct);
  LL_SPI_SetStandard
 (SPI2, LL_SPI_PROTOCOL_MOTOROLA);
	LL_SPI_Enable(SPI2);	


	// LL_SPI_EnableNSSPulseMgt(SPI1);
  /* USER CODE BEGIN SPI1_Init 2 */
  /* USER CODE END SPI1_Init 2 */
}

/******************************************************************************
 **@Function 			: FnFlashSPIXRdWr
 **@Descriptions	: 
 **@parameters		: 
 **@return				:	
 ****************************************************************************/
uint8_t FnSPI2RdWr( uint8_t ucSendData)   
{ 
	uint8_t ucRet = _DNumber_0	;
	/* Write character in Data register.
	TXE flag is cleared by reading data in DR register */	
		while(LL_SPI_IsActiveFlag_TXE (SPI2)  == RESET){ };
		LL_SPI_TransmitData8(SPI2, ucSendData);
	/* Read character in Data register.
	RXNE flag is cleared by reading data in DR register */					 
		while(LL_SPI_IsActiveFlag_RXNE(SPI2)  == RESET){};
		ucRet = LL_SPI_ReceiveData8(SPI2);			
	return  ucRet	;		
}


/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{
	
  /* USER CODE BEGIN USART3_Init 0 */
  /* USER CODE END USART3_Init 0 */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct 	= {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**USART3 GPIO Configuration
  PB10   ------> USART3_TX
  PB11   ------> USART3_RX
  */
  GPIO_InitStruct.Pin 		= LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode 		= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 	= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 			 = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate  = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin 			= LL_GPIO_PIN_11;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_Init 1 */
  /* USER CODE END USART3_Init 1 */
	USART_InitStruct.BaudRate 			= (uint32_t)230400;
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.DataWidth 			= LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits 			= LL_USART_STOPBITS_1;
  USART_InitStruct.Parity 				= LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection 	= LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl= LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling 	= LL_USART_OVERSAMPLING_8;
  LL_USART_Init(USART3, &USART_InitStruct);
	
  LL_USART_SetTXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART3);
  LL_USART_ConfigAsyncMode(USART3);

  /* USER CODE BEGIN WKUPType USART3 */
  /* USER CODE END WKUPType USART3 */
  LL_USART_Enable(USART3);
  /* Polling USART3 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART3))) 
		 || (!(LL_USART_IsActiveFlag_REACK(USART3))))  {  }
  /* USER CODE BEGIN USART3_Init 2 */
  /* USER CODE END USART3_Init 2 */

}


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{
	
  /* USER CODE BEGIN USART3_Init 0 */
  /* USER CODE END USART3_Init 0 */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct 	= {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);	
  /**USART3 GPIO Configuration
  PA9    ------> USART3_TX
  PA10   ------> USART3_RX
  */
	
  GPIO_InitStruct.Pin 		= LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode 		= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 	= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 			= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin 			= LL_GPIO_PIN_10;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin 				= LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_6);


  /* USER CODE BEGIN USART3_Init 1 */
  /* USER CODE END USART3_Init 1 */
	USART_InitStruct.BaudRate 			= (uint32_t)115200;
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
   USART_InitStruct.DataWidth 		= LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits 			= LL_USART_STOPBITS_1;
  USART_InitStruct.Parity 				= LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection 	= LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl= LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling 	= LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
	
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

	 NVIC_SetPriority(USART1_IRQn, 
	 NVIC_EncodePriority
	(NVIC_GetPriorityGrouping(),SET, SET));
	 NVIC_EnableIRQ(USART1_IRQn);

  /* USER CODE BEGIN WKUPType USART3 */
  /* USER CODE END WKUPType USART3 */
	LL_USART_EnableIT_RXNE(USART1);					
  LL_USART_Enable(USART1);
  /* Polling USART3 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART1))) 
		 || (!(LL_USART_IsActiveFlag_REACK(USART1))))  {  }
  /* USER CODE BEGIN USART3_Init 2 */
  /* USER CODE END USART3_Init 2 */
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	
	
  /**/
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin 			= LL_GPIO_PIN_7;
  GPIO_InitStruct.Pull 			= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Mode 			= LL_GPIO_MODE_OUTPUT;	
  GPIO_InitStruct.Speed 		= LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.OutputType= LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);

}



/**
  * @brief  The application entry point.
  * @retval int
  */
int main( void )
{
	
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
		NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral  */
  //LL_PWR_DisableUCPDDeadBattery();
  /* Configure the system clock */
	/*****************************/	
		SystemClock_Config();

  /* Initialize all configured peripherals */
	/*****************************/
		 MX_GPIO_Init();
	/*****************************/	
		 MX_SPI1_Init();
	/*****************************/	
		 MX_SPI2_Init();		
	/*****************************/		 
		 MX_USART3_UART_Init();
	/*****************************/		 

		printf("\n\rDEBUGG COM PORT INIT\n\r");	
		LL_RCC_ClocksTypeDef  RCC_Clocks123	;		
		LL_RCC_GetSystemClocksFreq(&RCC_Clocks123);
		printf("ALL CLOCK SET TO =\n\r")	;
		printf("SYSCLK=%u \t", RCC_Clocks123.SYSCLK_Frequency);
		printf("HCLK=%u\n\r" , RCC_Clocks123.HCLK_Frequency  );
		printf("PCLK1 =%u\t" , RCC_Clocks123.PCLK1_Frequency );
		printf("PCLK2 =%u\n\r",RCC_Clocks123.PCLK2_Frequency );

		printf("PLL CLOCK SOURCE=%s\t",
		LL_RCC_PLL_GetMainSource( ) == LL_RCC_PLLSOURCE_NONE	? "NONE" : 
		LL_RCC_PLL_GetMainSource( ) == LL_RCC_PLLSOURCE_HSI 	? "HSI"  :
		LL_RCC_PLL_GetMainSource( ) == LL_RCC_PLLSOURCE_HSE 	? "HSE"  : "UNKNOWN");

		printf("MAIN CLOCK SOUCE=%s\n\r",  
		LL_RCC_GetSysClkSource( ) == LL_RCC_SYS_CLKSOURCE_STATUS_HSI ? "HSI" :
		LL_RCC_GetSysClkSource( ) == LL_RCC_SYS_CLKSOURCE_STATUS_HSE ? "HSE" : 
		LL_RCC_GetSysClkSource( ) == LL_RCC_SYS_CLKSOURCE_STATUS_PLL ? "PLL" : "UNKNOWN");			
  
	
	/* USER CODE END 2 */
  _FLASH_CS_LOW
	 FnSPI2RdWr( _FLASH_CMD_RDID );
	 unVarConvo4.ui_32 = RESET;
   unVarConvo4.uc_8[_DNumber_2] = FnSPI2RdWr((uint8_t)0xAA);
   unVarConvo4.uc_8[_DNumber_1] = FnSPI2RdWr((uint8_t)0xAA);
   unVarConvo4.uc_8[_DNumber_0] = FnSPI2RdWr((uint8_t)0xAA);
  _FLASH_CS_HIGH	
	 printf("Flash ID=%s\n\r", 
	 unVarConvo4.ui_16[0] == _FLASH_TYPE_W25Q128 ? "W25Q128": "Unknown");	
		 
		 
	 FnACCMTRConfigPara( );  	 					
	 
	 FnSPIXEEPROMLoadConfig( ); 	
		
	
	/* Infinite loop */
  while (1)
  {
		
    /* USER CODE END WHILE */
		/* USER CODE END WHILE */		
			 LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_7);		
			 for(volatile uint32_t ucLoop = RESET ; ucLoop <0xFFFFF ; ucLoop++ ){};		
			 LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_7);				 
			 for(volatile uint32_t ucLoop = RESET ; ucLoop <0xFFFFF ; ucLoop++ ){};						
    /* USER CODE BEGIN 3 */  				 				 
			
	}
  /* USER CODE END 3 */
}


/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
		
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

