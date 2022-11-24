/********************************************************************************
  * @file    ../CODES/Ftimer.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    21-Oct-2018
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
 */
	 
			#include "main.h"


/* ----------------------------------------------------------------------------
 *                           MACROS
 * ----------------------------------------------------------------------------
 */




/* ----------------------------------------------------------------------------
 *                           GLOBAL VARIABLES
 * ----------------------------------------------------------------------------
*/
		
	__IO	uint32_t TimingDelay	;	
	

/*****************************************************************************
 **@Function 		  	: 	FnShortDelay
 **@Descriptions		: 	short time loop delay
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnShortDelay(void)
{
  uint32_t nTime = 0x0000;

	for(uint8_t ucWaitNodeId = 0 ; ucWaitNodeId <(uint8_t)0x01 ;ucWaitNodeId++ )
  for(nTime = 0; nTime <0xFFFFFF; nTime++);
	
}

/*****************************************************************************
 **@Function 		  	: 	TimingDelay_Decrement
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void TimingDelay_Decrement(void)
{
	
  if ( TimingDelay != RESET )
		 { 
			 TimingDelay--;
		 }
}

/*****************************************************************************
 **@Function 		  	: 	FnDelay_1ms
 **@Descriptions		: 	
 **@parameters			: 	
 **@return					: 	
*****************************************************************************/  
void FnDelay_1ms(__IO uint32_t nTime)
{ 	
					  TimingDelay  = nTime;
		 while( TimingDelay != 0 )
		      { 
						_IWDG_RELOAD_NILL
					} /* Reload IWDG counter */
}


/*****************************************************************************
 **@Function 		  	: 	FnDelay_10ms
 **@Descriptions		: 	
 **@parameters			: 	
 **@return					: 	
*****************************************************************************/ 
void FnDelay_10ms(__IO uint32_t nTime)
{ 
	for(uint8_t ucTimeRep = 0 ; ucTimeRep < 10 ; ucTimeRep++ )
	 {
						TimingDelay = nTime;
		 while( TimingDelay != 0 )
		      { 
						_IWDG_RELOAD_NILL			
					} 
	 }
}


/*****************************************************************************
 **@Function      	: FnScanIntervalAndReadAll_1SEC
 **@Descriptions  	: 
 **@parameters    	: None
 **@Return        	: None
*****************************************************************************/
void FnScanIntervalAndReadAll_1SEC (void)
{
	
	if(	stVarTimerCounter_ALL.ucScanInput_TimerFlag_1sec == SET	)
	  {			
			
		/*******************  reset unit time scan function  ********************/
		 stVarTimerCounter_ALL.ucScanInput_TimerFlag_1sec = RESET ;
		_IWDG_RELOAD_NILL /*RESET WATCHDOG COUNTER*/
		_SYSTEM_READ_DCIN_ALL
		 #if _USE_DEBUG_COM
				 _DEBUG_ALL_ENABLE_DIABLE
				  printf( "\nN%d.%d G%d.%d.%d I%d v%d T%u.%u.%u-%llu\n\r", 
						stVarGSM_All.stVarGSMNetworkPara.ucGSMNetworkState   , 
						stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate 	 ,
					((stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus1 == enGSMConnectedToServer)? SET:RESET ),
					((stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus2 == enGSMConnectedToServer)? SET:RESET ),
					((stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus3 == enGSMConnectedToServer)? SET:RESET ),
						stVarVehicleConfig_ALL.stVarVehiclePara.ucIgnitionStatus,
						stVarGPS_All.stVarGPSParameter.ucGPSPosition				 ,
						stVarTimerCounter_ALL.uiVar1hour_counter, stVarTimerCounter_ALL.uiVar1min_counter 		 , 
						stVarTimerCounter_ALL.uiVar1sec_counter , stVarTimerCounter_ALL.uiVar1SecUniversalCNT );
		 #endif		
		
		/***********************************************************************************/
				#ifdef _FLASH_ERASE_ENABLE
						static uint8_t 
							ucFLASHEraseCnt  = RESET, ucFLASHEraseFLAG = RESET ;
				 if ((ucFLASHEraseCnt == _DNumber_5)&& (ucFLASHEraseFLAG == RESET))
						{
							ucFLASHEraseFLAG = SET ;
							 #if _USE_DEBUG_FLASH 
										_DEBUG_ALL_ENABLE_DIABLE
										 printf("FLASH CHIP ERASE \n\r");
							 #endif
										FnFlashEraseChip();
							 #if _USE_DEBUG_FLASH 
										_DEBUG_ALL_ENABLE_DIABLE
										 printf("FLASH CHIP ERASE COMPLETE \n\r");
							 #endif	
							
						 FnSetLocalVariableToDefault();		
						 FnFlashTraceAndReadConfig1();
						 FnFlashReadConfig2();					
						 while(SET)
						 _IWDG_RELOAD_NILL;							 
						}
					if(ucFLASHEraseFLAG == RESET )
						 ucFLASHEraseCnt++;
				 #endif

			/*
			//send sms after the 100th second.
			static 
			uint8_t ucSMS = RESET ; ucSMS++;
					if (ucSMS == _DNumber_100)	
					{
						  ucSMS = RESET ;
							FnSendSMSReply("+919222022939","DEVICE 01\n\r");
					}
			*/
		
		
	 /***********************************************************************************/
			/*
			if( stVarVehicleConfig_ALL.stVarVehiclePara.ucRESETCOMMAND == SET 	)	
				{
					
					static uint8_t ucResetCNT = _DNumber_0; ucResetCNT++;
									 	 if (ucResetCNT == _DNumber_5)
												{
													#if  _USE_DEBUG_COM	
															 _DEBUG_ALL_ENABLE_DIABLE
																printf("RESET COMMAND EXECUTE!\n\r");
													#endif
													NVIC_SystemReset();
												}
				}
			 */
		
		/***********************************************************************************/
			if(( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus == enGSMStatusInitProcess )
			 ||( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus == enGSMStatusReady			 ))
				 {
						if( stVarGSM_All.stVarGSMNetworkPara.ucGSMIMEINumberUpdate == RESET )	
							{
								FnGSMSendDefaultParaCMD();
								stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusReady	;
								stVarGSM_All.stVarGSMNetworkPara.ucGSMIMEINumberUpdate = SET ;
							}
				 }
				
		/***********************************************************************************/		
			if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus == enGSMStatusReady 			 )
			  {
				 #ifdef _ENABLE_GSM_CONFIG_QUECTEL		
									if(((stVarTimerCounter_ALL.uiVar1sec_counter+_DNumber_1) % _DNumber_20) == RESET  )
										{		
											if(	stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate == enGSMNetworkNotConnected ) 
												{ stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate  = enGSMCommandInitDone		 ;
													FnGSMSendDefaultNWCMD();	
												}
										}					
									else
				 #endif
					if((( stVarTimerCounter_ALL.uiVar1sec_counter + _DNumber_1 ) % _DNumber_15 ) == RESET )
							{
								
								FnGSMSendFixedSCANCMD();
							}							 
			 }			
				
			 
		/************** Odometer Check ******************/ 
		if((	stVarGPS_All.stVarGPSParameter.ucGPSPosition 			!= _DNumber_0 	)
	   &&(  stVarGPS_All.stVarGPSParameter.flSpeedOverGround 	 >  
					stVarVehicleConfig_ALL.stVarOdometer.flOdometerMinimumSpeed			 ))				
				{
					
								FnOdometreCheckAndUpdate();
					
							  stVarVehicleConfig_ALL.stVarOdometer.ucOdometerTimerCNT++ ;
					 if ( stVarVehicleConfig_ALL.stVarOdometer.ucOdometerTimerCNT > ( _DNumber_100 * _DNumber_3 ))	
							{ stVarVehicleConfig_ALL.stVarOdometer.ucOdometerTimerCNT = 	_DNumber_0 	 ;
							 #if _USE_FLASH_SPI
										FnFlashStoreConfig2( );
							 #endif	
							}
				}
				
					/************** Odometer Check ******************/ 
					if(	stVarGPS_All.stVarGPSParameter.ucGPSPosition 			!= _DNumber_0 	)	
						{
							
					
					
					
						}
				
		/************  Process the primary/ secondary IP  **********/
		#if _USE_GSM_COM  & _USE_FLASH_SPI	
				 FnEventDataProcess();		
		#endif					
			

		#if _USE_GSM_COM				
		/************  Process the Health Packet  **********/							
				 FnGPRSBuildHealthFrame();	 
			 
		/************  Process the GPRS Reply Packet  **********/		 
				 FnSendGPRSCMDData();				
		#endif	
						
		/************** Accelerometer event check ******************/		
		#if _USE_ACCMTR_I2C
				 FnCheckAccelerometerEvent();
		#endif	
		
		/***********************************************************/
		static uint8_t ucIgnitionTamperCheckFlag = RESET ;
		static uint8_t ucIgnitionTamperCnt 			 = RESET ;
		
		/***************Wait for at least 3 minutes
										after the boot-up******************/
		if ( ucIgnitionTamperCheckFlag == RESET )
				 ucIgnitionTamperCnt++;		
		
		if(( ucIgnitionTamperCnt				>= (uint8_t)180 )
		 ||(stVarGPS_All.stVarGPSParameter.ucGPSPosition >= SET )) 
			 {
				 ucIgnitionTamperCheckFlag = SET ;
				 ucIgnitionTamperCnt			 = RESET;
			 }
		if (ucIgnitionTamperCheckFlag  == SET )
		   {  
				 /************** Ignition Status Check ******************/		
				 FnIgnitionCheck();	 
			 
				 /************** Tamper Status Check ******************/		
				 FnTamperCheck();			 			
			 }	
	 }	
}


/*****************************************************************************
 **@Function      	: FnScanIntervalAndReadAll_1SEC
 **@Descriptions  	: 
 **@parameters    	: None
 **@Return        	: None
*****************************************************************************/
void FnScanIntervalAndReadAll_100mSEC( void )
{				
				
		if( stVarTimerCounter_ALL.ucScanInput_TimerFlag_100msec == SET   )
			{	
				/*******************  reset unit time scan function  ********************/
				 stVarTimerCounter_ALL.ucScanInput_TimerFlag_100msec =  RESET ;
				
				
				/******************* *******************/					
				//FnACCMTRConfigPara();				

				
				/******************* GPS INIT PROCESS *******************/	
				#if _USE_GPS_COM								
							FnGPSEventProcess();	
				#endif
				
				/******************* GPRS INIT PROCESS ******************/
				#if _USE_GSM_COM				
						 FnGPRSEventProcess();
				#endif	
											

				#if _USE_IADC_CHANNEL	
				/******************* ADC READ THE BATTERY/ MAIN **********/				
							FnStartiADCConvo();				
				/******************* PANIC LED/ READ PIN CHECK **********/
							FnEmergencyPANICEvent();				
				#endif
				
				
			  #if _USE_ACCMTR_I2C
						 if(( stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerActive == SET )
							&&( stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerENnDS  == SET )
						  &&( stVarTimerCounter_ALL.uiVar1SecUniversalCNT	>= _DNumber_15  ))
									FnACCMTRScanAndRead();
				#endif
				
			}
}

/*****************************************************************************
 **@Function      	: FnScanIntervalAndReadAll_1MIN
 **@Descriptions  	: 
 **@parameters    	: None
 **@Return        	: None
*****************************************************************************/
void FnScanIntervalAndReadAll_1MIN (void)
{
		
	if(	 stVarTimerCounter_ALL.ucScanInput_TimerFlag_1min	 == SET  )
		{ /*******************  reset unit time scan function  ********************/	
			 stVarTimerCounter_ALL.ucScanInput_TimerFlag_1min  = RESET ;
						
			/*************************** RECONNECT THE SERVER 1 ******************************/	 			
			 if(( stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokReconnect1  ==  SET  )
			 /*||( stVarGSM_All.stVarGSMNetworkPara.ucQIOPENCommandSend 	 ==  SET )*/
			 && ( stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus1  	 !=	enGSMConnectedToServer )
			 && ( stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate			 >= enGSMQIACTPositiveRespond))
			    {
							#if _ENABLE_DEBUGG_GSM
									_DEBUG_ALL_ENABLE_DIABLE
									 printf("TCP RECONNECTING SERVER 1!\n\r");
						 #endif


						#ifdef _ENABLE_GSM_CONFIG_QUECTEL	
										 char ucTCPCommand[50]; 
											sprintf( ucTCPCommand, "AT+QIOPEN=%d,\"TCP\",\"%s\",%u",
										 _GSM_IP_STATE_PRIMARY												  ,
										 stVarGSM_All.stVarGSMConfigPara.ucPrimaryIPnDNS,
										 stVarGSM_All.stVarGSMConfigPara.ucPrimaryPort );
										 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );
						#elif defined _ENABLE_GSM_CONFIG_SIM800 	
										char ucTCPCommand[50]; 
											sprintf( ucTCPCommand, "AT+CIPSTART=%d,\"TCP\",\"%s\",%u",
										 _GSM_IP_STATE_PRIMARY												  ,
										 stVarGSM_All.stVarGSMConfigPara.ucPrimaryIPnDNS,
										 stVarGSM_All.stVarGSMConfigPara.ucPrimaryPort );
										 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );
						#endif
				  }
					
			/*************************** RECONNECT THE SERVER 3 ******************************/	 
			 if((  stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokReconnect3 ==  SET  )
			 /*||( stVarGSM_All.stVarGSMNetworkPara.ucQIOPENCommandSend 	 ==  SET )*/ 
			 && (  stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus3  	 !=	enGSMConnectedToServer )
			 && ( stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate			 >= enGSMQIACTPositiveRespond))
			    {
						#if _ENABLE_DEBUGG_GSM
								_DEBUG_ALL_ENABLE_DIABLE
								 printf("TCP RECONNECTING SERVER 3!\n\r");
						#endif
							
						#ifdef _ENABLE_GSM_CONFIG_QUECTEL	
									 char ucTCPCommand[50]; 
									 sprintf( ucTCPCommand, "AT+QIOPEN=%d,\"TCP\",\"%s\",%u",
									 _GSM_IP_STATE_SECONDARY3												   ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryIPnDNS3 ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryPort3  );
									 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );	
						#elif defined _ENABLE_GSM_CONFIG_SIM800 
									 char ucTCPCommand[50]; 
									 sprintf( ucTCPCommand, "AT+CIPSTART=%d,\"TCP\",\"%s\",%u",
									 _GSM_IP_STATE_SECONDARY3												   ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryIPnDNS3 ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryPort3  );
									 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );	
						
						#endif
				  }	
					
			/*************************** RECONNECT THE SERVER 2 ******************************/	 
			 if((  stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokReconnect2 ==  SET  )
			 /*||( stVarGSM_All.stVarGSMNetworkPara.ucQIOPENCommandSend 	 ==  SET )*/ 
			 && (  stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus2  	 !=	enGSMConnectedToServer )
			 && (  stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate			 >= enGSMQIACTPositiveRespond))
			    {
						 #if _ENABLE_DEBUGG_GSM
								 _DEBUG_ALL_ENABLE_DIABLE
									printf("TCP RECONNECTING SERVER 2!\n\r");
						 #endif
						
						 #ifdef _ENABLE_GSM_CONFIG_QUECTEL		
									 char ucTCPCommand[50]; 
									 sprintf( ucTCPCommand, "AT+QIOPEN=%d,\"TCP\",\"%s\",%u",
									 _GSM_IP_STATE_SECONDARY2												   ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryIPnDNS2 ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryPort2  );
									 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );	
						#elif defined _ENABLE_GSM_CONFIG_SIM800 
									 char ucTCPCommand[50]; 
									 sprintf( ucTCPCommand, "AT+CIPSTART=%d,\"TCP\",\"%s\",%u",
									 _GSM_IP_STATE_SECONDARY2												   ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryIPnDNS2 ,
									 stVarGSM_All.stVarGSMConfigPara.ucSecondryPort2  );
									 FnGSMStoreSendingData( ucTCPCommand , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD );	
						
						#endif
				  }	
					
					
			/******************************/	
			#if _USE_GSM_COM  & _USE_FLASH_SPI
				/*********************/ 
			if (((( stVarTimerCounter_ALL.uiVar1min_counter  ) 		% _DNumber_5) == _DNumber_0  )
				  &&( stVarFlash_All.stVarFlashLogs.uiPrimeryLogCnt > _DNumber_10 ))
					  {							
						 if ( stVarVehicleConfig_ALL.stVarVehiclePara.ucIgnitionStatus == SET )
								{											
									#if _ENABLE_DEBUGG_FLASH
											_DEBUG_ALL_ENABLE_DIABLE 
											 printf( "P LOG DIAGNOSE BEGAIN! \n\r") ;
									#endif 
								 stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose  = 
								 stVarFlash_All.stVarFlashLogs.uiPrimeryStartingPointer ;	
								
								#if _ENABLE_DEBUGG_FLASH
										_DEBUG_ALL_ENABLE_DIABLE 
										 printf("P CURRENT ADD----> %x\n\rLOGS DIFFRENCE----> %x\n\r",
										 stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose	 , 
										 stVarFlash_All.stVarFlashLogs.uiPrimeryLogCnt       );
								#endif
								
								while( FnFlashReadUint8 ( _FlASH_PARA_ADD_NEW_ENTRY_STATUS ( 
											 stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose  )) != (uint8_t)0xFF )
										 {
												 stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose	+= _FLASH_DEFAULT_PAGE_SIZE ;
										if(( stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose >= 
											 ( stVarFlash_All.stVarFlashLogs.uiPrimaryStoreCounter - _FLASH_DEFAULT_PAGE_SIZE )))
											 {	
												 stVarFlash_All.stVarFlashLogs.uiPrimeryLogCnt  = RESET ;
												 stVarFlash_All.stVarFlashLogs.uiPrimeryStartingPointer = 
												 stVarFlash_All.stVarFlashLogs.uiPrimaryStoreCounter 	  - 
												 _FLASH_DEFAULT_PAGE_SIZE ;
												 #if _ENABLE_DEBUGG_FLASH
														 _DEBUG_ALL_ENABLE_DIABLE
															printf("P END OF THE LOG REACHED!\n\r");
												 #endif
												 break ;
											 }
											else
											{ 
												stVarFlash_All.stVarFlashLogs.uiPrimeryStartingPointer = 
												stVarFlash_All.stVarFlashLogs.uiPrimaryLogDiagnose		 ;
											}												
										 }
										#if _ENABLE_DEBUGG_FLASH
												_DEBUG_ALL_ENABLE_DIABLE 
												 printf("P UPDATED START POINTER! = %x \n\r",
												 stVarFlash_All.stVarFlashLogs.uiPrimeryStartingPointer);
										#endif
										FnFlashTraceAndStoreConfig1();										 
							 }
						else
							 {
									#if _ENABLE_DEBUGG_FLASH
											_DEBUG_ALL_ENABLE_DIABLE 							 
											 printf("Ignition off, discarding the log diagnose");	
									#endif
							 }							
						 }
			else
					 {
						  #if _ENABLE_DEBUGG_FLASH
									_DEBUG_ALL_ENABLE_DIABLE 
									 printf( "P  LESS NUMBER OF LOGS TO DIAGNOSE!\n\r") ;
							#endif 
					 }
			#endif
		

			/******************************/	
			#if _USE_GSM_COM  & _USE_FLASH_SPI
			/*********************/ 
			if (((( stVarTimerCounter_ALL.uiVar1min_counter  ) % _DNumber_10) == _DNumber_0  )
				  &&( stVarFlash_All.stVarFlashLogs.uiSecondary3LogCnt  > 	 _DNumber_10 ))
					 {
						 #if _ENABLE_DEBUGG_FLASH
								 _DEBUG_ALL_ENABLE_DIABLE
									printf( "S3 LOG DIAGNOSE BEGAIN! \n\r") ;
						 #endif	 
						 stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose  = 
						 stVarFlash_All.stVarFlashLogs.uiSecondary3StartingPointer ;	
						
						 #if _ENABLE_DEBUGG_FLASH
								 _DEBUG_ALL_ENABLE_DIABLE
									printf("S3 CURRENT ADD----> %x\n\rLOGS DIFFRENCE----> %x\n\r" ,
									stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose	, 
									stVarFlash_All.stVarFlashLogs.uiSecondary3LogCnt      );
						 #endif
					 
						 while( FnFlashReadUint8 ( _FlASH_PARA_ADD_NEW_ENTRY_STATUS ( 
									  stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose  )) != (uint8_t)0xFF )
								  {
											 stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose += _FLASH_DEFAULT_PAGE_SIZE ;
									if(( stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose >= 
										 ( stVarFlash_All.stVarFlashLogs.uiSecondary3StoreCounter - _FLASH_DEFAULT_PAGE_SIZE )))
										 {	
											 stVarFlash_All.stVarFlashLogs.uiSecondary3LogCnt  = RESET ;
											 stVarFlash_All.stVarFlashLogs.uiSecondary3StartingPointer = 
											 stVarFlash_All.stVarFlashLogs.uiSecondary3StoreCounter 	 - 
											 _FLASH_DEFAULT_PAGE_SIZE ;
											 
											 #if _ENABLE_DEBUGG_FLASH
													 _DEBUG_ALL_ENABLE_DIABLE
														printf("S3 END OF THE LOG REACHED!\n\r");
											 #endif
											 break ;
										 }
										else
										{ 
											stVarFlash_All.stVarFlashLogs.uiSecondary3StartingPointer = 
											stVarFlash_All.stVarFlashLogs.uiSecondary3LogDiagnose		 ;
										}												
								  }
								#if _ENABLE_DEBUGG_FLASH
										_DEBUG_ALL_ENABLE_DIABLE 
										 printf("S3 UPDATED START POINTER! = %x \n\r",
										 stVarFlash_All.stVarFlashLogs.uiSecondary3StartingPointer);	
								#endif
								FnFlashTraceAndStoreConfig1();
					  } 	
			else
					 {
						  #if _ENABLE_DEBUGG_FLASH
									_DEBUG_ALL_ENABLE_DIABLE 
									 printf( "S3 LESS NUMBER OF LOGS TO DIAGNOSE!\n\r") ;
							#endif 
					 }
			#endif
			
			
			/******************************/	
			#if _USE_GSM_COM  & _USE_FLASH_SPI
			/*********************/ 
			if (((( stVarTimerCounter_ALL.uiVar1min_counter  ) % _DNumber_5 ) == _DNumber_0  )
				  &&( stVarFlash_All.stVarFlashLogs.uiSecondary2LogCnt  > 	 _DNumber_1 ))
					 {
					 #if _ENABLE_DEBUGG_FLASH
							 _DEBUG_ALL_ENABLE_DIABLE
								printf( "S2 LOG DIAGNOSE BEGAIN! \n\r") ;
					 #endif	 
						 stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose  	 = 
						 stVarFlash_All.stVarFlashLogs.uiSecondary2StartingPointer ;	
						
					 #if _ENABLE_DEBUGG_FLASH
							 _DEBUG_ALL_ENABLE_DIABLE
								printf("S2 CURRENT ADD----> %x\n\rLOGS DIFFRENCE----> %x\n\r" ,
										stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose	, 
										stVarFlash_All.stVarFlashLogs.uiSecondary2LogCnt      );
					 #endif
					 
						while( FnFlashReadUint8 ( _FlASH_PARA_ADD_NEW_ENTRY_STATUS ( 
									 stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose  )) != (uint8_t)0xFF )
								 {
											 stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose += _FLASH_DEFAULT_PAGE_SIZE ;
									if(( stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose >= 
										 ( stVarFlash_All.stVarFlashLogs.uiSecondary2StoreCounter - _FLASH_DEFAULT_PAGE_SIZE )))
										 {	
											 stVarFlash_All.stVarFlashLogs.uiSecondary2LogCnt  = RESET ;
											 stVarFlash_All.stVarFlashLogs.uiSecondary2StartingPointer = 
											 stVarFlash_All.stVarFlashLogs.uiSecondary2StoreCounter 	 - 
											 _FLASH_DEFAULT_PAGE_SIZE ;
											 
											 #if _ENABLE_DEBUGG_FLASH
													 _DEBUG_ALL_ENABLE_DIABLE
														printf("S2 END OF THE LOG REACHED!\n\r");
											 #endif
											 break ;
										 }
										else
										{ 
											stVarFlash_All.stVarFlashLogs.uiSecondary2StartingPointer = 
											stVarFlash_All.stVarFlashLogs.uiSecondary2LogDiagnose		 ;
										}												
								 }
								#if _ENABLE_DEBUGG_FLASH
										_DEBUG_ALL_ENABLE_DIABLE 
										 printf("S2 UPDATED START POINTER! = %x \n\r",
										 stVarFlash_All.stVarFlashLogs.uiSecondary2StartingPointer);	
								#endif
								FnFlashTraceAndStoreConfig1();
					  } 	
			else
					 {
						  #if _ENABLE_DEBUGG_FLASH
									_DEBUG_ALL_ENABLE_DIABLE 
									 printf( "S2 LESS NUMBER OF LOGS TO DIAGNOSE!\n\r") ;
							#endif 
						 if(( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive == _DNumber_0 )
						 &&(  stVarFlash_All.stVarFlashLogs.uiSecondary2LogCnt == _DNumber_0 ))
							 {
								  #if _ENABLE_DEBUGG_FLASH
									_DEBUG_ALL_ENABLE_DIABLE 
									 printf( "S2 RECONNECTING STOP!\n\r") ;
									#endif 
								  stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokReconnect2 = RESET ;
							 }
					 }
			#endif	
					
			/****************** DATA Recovery ************/	
			#if _USE_GSM_COM 
			#if 	(	_ENABLE_EMBEDDED_SIM == _TRUE	 )		 
				/**********************CHECK NETWORK**********************/	 
				if ( stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivate < enGSMQIACTPositiveRespond)
					 {
	
						 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus 	= enGSMStatusReady ;	
						 stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivateCNT++ ;
						 
						 /********************************************************************/
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivateCNT == _DNumber_3 )
							 {
								 #if _ENABLE_DEBUGG_GSM
										 _DEBUG_ALL_ENABLE_DIABLE
										  printf("NETWORK NOT STABLE!\nRESETING THE MODULE!\n\r");
								 #endif
								 FnGSMModuleReset(RESET); //enGSMStatusNotReady
								 stVarGSM_All.stVarGSMNetworkPara.ucGSMGPRSActivateCNT = RESET ;
								 stVarGSM_All.stVarGSMNetworkPara.ucModuleResetCnt++;
								 /********************************************************************/
								 if ( stVarGSM_All.stVarGSMNetworkPara.ucModuleResetCnt == _DNumber_2 )
										{
											FnGSMModuleReset(SET);
											stVarGSM_All.stVarGSMNetworkPara.ucModuleResetCnt = RESET ; 
											stVarGSM_All.stVarGSMNetworkPara.ucGSMNetworkState=
										 !stVarGSM_All.stVarGSMNetworkPara.ucGSMNetworkState;
											/********************************************************************/
											if (stVarGSM_All.stVarGSMNetworkPara.ucGSMNetworkState == SET )
												 {
													#if _ENABLE_DEBUGG_GSM
															_DEBUG_ALL_ENABLE_DIABLE
															 printf("SWITCHING NETWORK TO SECONDARY!\n\r");
													#endif
												 }
											else
												 {
													#if _ENABLE_DEBUGG_GSM
															_DEBUG_ALL_ENABLE_DIABLE
															 printf("SWITCHING NETWORK TO PRIMARY!\n\r");
													#endif
												 }												
										 }
							  }
					 }
					 #endif					 
					 #endif
					 
			 /**************************** NORMAL PACKET GENRATOR ****************************/
			 if( stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt == _DNumber_4  )	
				 { 
					 #if _USE_IADC_CHANNEL
								FnCheckBatteryAndCharge();
					 #endif	
				 }
			 if( stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt == _DNumber_1  )	 
				 { 
					 
					if (stVarVehicleConfig_ALL.stVarVehiclePara
							 .ucMainInputVolatageStatus == SET )
							{					
								 stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryStatus = SET ;
								_SYSTEM_BATTERY_CHARGE_ENABLE
									#if  _USE_DEBUG_COM
											 _DEBUG_ALL_ENABLE_DIABLE
												printf("BATTERY CHARGING ON!\n\r");
									#endif
							}								
				 }
			else	 
			 if( stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt ==
					 stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingONTime )
				 { 
					 stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryStatus = RESET ;
					 _SYSTEM_BATTERY_CHARGE_DISABLE
						#if  _USE_DEBUG_COM
								 _DEBUG_ALL_ENABLE_DIABLE
									printf("BATTERY CHARGING OFF!\n\r");
						#endif	
				 }
			else	 
				if( stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt 		 ==
					( stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingONTime  + 
						stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingOFFTime ))
					{	
						stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt = RESET ; 
					}			 
						stVarVehicleConfig_ALL.stVarVehiclePara.ucInternalBatteryChargingCnt++;
					 
		}
}

/*****************************************************************************
 **@Function 		  	: 	FnPrimaryDataProcess
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnEventDataProcess ( void )
{

		/**************************** NORMAL PACKET GENRATOR ****************************/
		if((( stVarTimerCounter_ALL .uiVar1SecUniversalCNT 							 + SET   )  % 
			  	stVarVehicleConfig_ALL.stVarVehiclePara.uiPrimaryTxTime	) == RESET ) 
			    { 
								#if _ENABLE_DEBUGG_GSM
										_DEBUG_ALL_ENABLE_DIABLE
										 printf("A NORMAL FRAME EVENT GENERATED!\n\r");	
								#endif
						
						#if _USE_GSM_COM  & _USE_FLASH_SPI
								 FnGPRSPrimaryEventGenrate( _GSM_FRAME_TYPE_NORMAL_FRAME_NO );
						#endif
					}
		
		      if (( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive	 == SET )
					&&((( stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut		  + SET )  % 
								stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyModeExpTime 	      ) == RESET  ))
							{
								if( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyFrameCount 	 == RESET )
									{ stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyFrameCount		 = _DNumber_1 ;
										stVarVehicleConfig_ALL.stVarEmergency_All.flEmergencyTotalDistance = _DNumber_0 ;
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyOldLongitude	 =
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar		 ;
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyOldLongitude  =
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar		 ;
									}
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyNewLongitude	  =
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar		  ;
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyNewLongitude   =
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar		  ;

								 #if _USE_DEBUG_GSM
										 _DEBUG_ALL_ENABLE_DIABLE
											printf("SENDING LAST EMERGENCY PACKET!\n\r");
								 #endif	
								 FnEmergencyDistanceCalculation();
								 #if _USE_GSM_COM  & _USE_FLASH_SPI	
										 FnGPRSPrimaryEventGenrate	 ( _GSM_FRAME_TYPE_EMERGENCY_RESET_NO );	
										 FnGPRSSecondary2EventGenrate( _GSM_FRAME_TYPE_EMERGENCY_RESET_NO );
								 #endif	
								 stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive = RESET ;
							}
					else			
					if (( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive		  == SET )
					&&((( stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut			   + SET )  % 
								stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyModeTxTime   ) == RESET  ))
						  {
							  if( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyFrameCount    == RESET)
									{ stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyFrameCount	   = _DNumber_1 ;
										stVarVehicleConfig_ALL.stVarEmergency_All.flEmergencyTotalDistance = _DNumber_0 ;
										
										/***Saving the current longitude value into an old variable***/
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyOldLongitude	 =
										/**THIS IS THE CURRENT Longitude Value***/
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar		 ;
										/***Saving the current Latitude value into an old variable***/
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyOldLatitude   =
										/**THIS IS THE CURRENT Longitude Value***/
										stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlLatitudeVar		   ;
									}
										/***Saving the current longitude value into a new variable***/
										stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyNewLongitude	 =
									  /**THIS IS THE CURRENT Longitude Value***/
										stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar	   ;
									  /***Saving the current latitude value into a new variable***/	
									  stVarVehicleConfig_ALL.stVarEmergency_All.dlEmergencyNewLatitude  =
										/**THIS IS THE CURRENT Longitude Value***/
										stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlLatitudeVar		 ;
									
								 #if _USE_DEBUG_GSM
										 _DEBUG_ALL_ENABLE_DIABLE
											printf("SENDING REGULAR EMERGENCY PACKET!\n\r");
								 #endif	
								 FnEmergencyDistanceCalculation();
								 #if _USE_GSM_COM  & _USE_FLASH_SPI			
											FnGPRSSecondary2EventGenrate( _GSM_FRAME_TYPE_EMERGENCY_ALERT_NO  );
								 #endif	
						  }							
							
				   if( stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive  == SET )						 
						 {
									stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut++;
								  printf("EMERGENCY TIEMOUT COUNT = %d REMAINING TIME = %d \n\r",
									stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut	, 
									stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyModeExpTime -
									stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut );	
								
							if ( stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut 	  > 
									 stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyModeExpTime )
								 {
									 stVarVehicleConfig_ALL.stVarEmergency_All.ucEmergencyModeActive	=
									 stVarVehicleConfig_ALL.stVarEmergency_All.uiEmergencyTimeOut			= RESET ;	
								 }
							}

							
					/**************************** NORMAL PACKET GENRATOR ****************************/		
					if(( stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus1 	  ==	enGSMConnectedToServer) 
					&& ( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandComplete1	==  SET	 ))
						 {
								#if _ENABLE_DEBUGG_GSM
										_DEBUG_ALL_ENABLE_DIABLE
										 #ifdef _ENABLE_GSM_CONFIG_QUECTEL	
													 printf("AT+QISACK No P = %d \n\r",
										 #elif defined	_ENABLE_GSM_CONFIG_SIM800
													 printf("AT+CIPACK No P = %d \n\r",	 
										 #endif	
										 stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT1 );
								#endif
							  
								char ucTCPCommand[ _DNumber_20 ]; memset( ucTCPCommand , NULL , sizeof( ucTCPCommand ) 	  );
							  #ifdef _ENABLE_GSM_CONFIG_QUECTEL	
												sprintf( ucTCPCommand, "AT+QISACK=%d", _GSM_IP_STATE_PRIMARY );
								#elif defined	_ENABLE_GSM_CONFIG_SIM800
												sprintf( ucTCPCommand, "AT+CIPACK=%d", _GSM_IP_STATE_PRIMARY );	
							  #endif	
								FnGSMStoreSendingData( ucTCPCommand	 , _GSM_RX_TIMEOUT4 , _GSM_SEND_TYPE_CMD  );
								stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT1++  ;
							 
								if( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT1 >= _DNumber_31 )
										FnGPRSQISACKFailed(RESET);
											
						 }
					
					/**************************** NORMAL PACKET GENRATOR ****************************/
					if(( stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus2 	  ==	enGSMConnectedToServer) 
					&& ( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandComplete2	==  SET	 ))
						 {
								#if _ENABLE_DEBUGG_GSM
										_DEBUG_ALL_ENABLE_DIABLE
										 #ifdef _ENABLE_GSM_CONFIG_QUECTEL	
														 printf("AT+QISACK No S2 = %d \n\r",
										 #elif defined	_ENABLE_GSM_CONFIG_SIM800
														 printf("AT+CIPACK No S2 = %d \n\r",
							       #endif
										 stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT2 );
								#endif
								char ucTCPCommand[ _DNumber_20 ]; memset( ucTCPCommand , NULL , sizeof( ucTCPCommand ) 	  );
								#ifdef _ENABLE_GSM_CONFIG_QUECTEL	
												sprintf( ucTCPCommand, "AT+QISACK=%d", _GSM_IP_STATE_SECONDARY2 ); 
							 #elif defined	_ENABLE_GSM_CONFIG_SIM800
												sprintf( ucTCPCommand, "AT+CIPACK=%d", _GSM_IP_STATE_SECONDARY2 ); 
							 #endif
							  FnGSMStoreSendingData( ucTCPCommand	 , _GSM_RX_TIMEOUT4 , _GSM_SEND_TYPE_CMD  );
								stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT2++  ;

								if( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT2 >= _DNumber_31 )
										FnGPRSQISACKFailed(RESET);				 
						 }

					/**************************** NORMAL PACKET GENRATOR ****************************/
					if(( stVarGSM_All.stVarGSMNetworkPara.ucGSMNetwrokStatus3 		==	enGSMConnectedToServer) 
					&& ( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandComplete3 ==  SET	 ))
						 {
								#if _ENABLE_DEBUGG_GSM
										_DEBUG_ALL_ENABLE_DIABLE
										 #ifdef _ENABLE_GSM_CONFIG_QUECTEL 	
														printf("AT+QISACK No S3 = %d \n\r",
										 #elif defined	_ENABLE_GSM_CONFIG_SIM800
														printf("AT+CIPACK No S3 = %d \n\r",
										 #endif
										 stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT3 );
								#endif
							
								char ucTCPCommand[ _DNumber_20 ]; memset( ucTCPCommand , NULL , sizeof( ucTCPCommand ) );
								#ifdef _ENABLE_GSM_CONFIG_QUECTEL 
												sprintf( ucTCPCommand, "AT+QISACK=%d" , _GSM_IP_STATE_SECONDARY3 ); 
								#elif defined	_ENABLE_GSM_CONFIG_SIM800
												sprintf( ucTCPCommand, "AT+CIPACK=%d" , _GSM_IP_STATE_SECONDARY3 ); 
								#endif
								FnGSMStoreSendingData( ucTCPCommand	  , _GSM_RX_TIMEOUT4 , _GSM_SEND_TYPE_CMD  );
								stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT3++ ;
							
								if( stVarGSM_All.stVarGSMNetworkPara.ucQIACKCommandCNT2 >= _DNumber_31 )
										FnGPRSQISACKFailed(RESET);
						}		
	
}



/*****************************************************************************
 **@Function      	: FnGPRSEventProcess
 **@Descriptions  	: 
 **@parameters    	: None
 **@Return        	: None
*****************************************************************************/
uint8_t FnGPRSEventProcess (void)
{
	/*
	Note:

	 This function called after every interval of 100ms.
	_GSM_CONFIG_GSM_ENABLE_ON  ~ execute on the 500ms after the poweron 
	_GSM_CONFIG_GSM_ENABLE_OFF ~ execute on the 800ms after the poweron 
	_GSM_CONFIG_GSM_ON_SET		 ~ execute on the 1900ms after the poweron  
	_GSM_CONFIG_GSM_ON_RESET	 ~ execute on the 3400ms after the poweron  
	
	#if defined _ENABLE_GSM_CONFIG_QUECTEL 
			GSM ON after  at the 8000ms after the poweron  
	#elif deined _SIMCOM_GSM_MODULE
			GSM ON after  at the 15000ms after the poweron  	

	#elif deined _ENABLE_GSM_CONFIG_FIBICOM:
		Press the PWRKEY for more than 1 second and then release, SIM800C module power on.
	
	*/

	#if _USE_GSM_COM
			/************* GSM Power On function ************************/	
			if(  stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus == enGSMStatusNotReady		  )
				{  
															
						/************* GSM ENABLE HIGH FOR 300ms ************/ 	
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitEnableHigh)
							 { 
							 	#if _USE_DEBUG_GSM
										_DEBUG_ALL_ENABLE_DIABLE 
										 printf("GSM RESET PROCESS BEGAIN!\n\r");
								#endif
								_GSM_CONFIG_GSM_ENABLE_ON  
							 } 
						/************* GSM ENABLE LOW INFINITE *************/ 		
						else 
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitEnableLow )	
							 { 
							 _GSM_CONFIG_GSM_ENABLE_OFF } 
						/************* GSM ON HIGH FOR 1.5s ****************/ 	
						else 
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnHigh		 ) 
							 {
							 _GSM_CONFIG_GSM_ON_SET     }  				 	 
						/************* GSM ON LOW INFINITE  ****************/ 		
						else 
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnLow		 ) 
							 { 
								_GSM_CONFIG_GSM_ON_RESET 	}
						else 
						 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnReady	 )
							 {
									#if _USE_DEBUG_GSM
											_DEBUG_ALL_ENABLE_DIABLE 	
											 printf("GSM ONNNNNNN---------------!\n\r");
									#endif
									stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusPowerOn ;
									stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt    = RESET 							;
									stVarGSM_All.stVarGSMCOMPort.ucGSMRxProcessFlag	 = RESET							;
									stVarGSM_All.stVarGSMCOMPort.ucGSMComTxStatus		 = enNoSendingProcess ;
									/********************* TEST COMMAND *********************/
								 
									 #if _ENABLE_GSM_CONFIG_QUECTEL
												FnGSMStoreSendingData( "AT"	  , _GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD	);
												FnGSMStoreSendingData( "ATE0"	, _GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD	);
												FnGSMStoreSendingData( "AT+QNITZ=0",	_GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD );
									#endif
								 	// FnGSMSendDefaultParaCMD();
							 }
					stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt++;		 
				}	
			
			/************* GSM Init Command Send ************************/		
			else 
			if(	stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus  == enGSMStatusPowerOn			  )	
				{
					 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt  == enGSMInitReadyToSend )
						 { stVarGSM_All.stVarGSMConfigPara.ucGSMResetCnt	 = RESET ; 
								
							 	#if _USE_DEBUG_GSM
										_DEBUG_ALL_ENABLE_DIABLE 
										 printf("GSM SIMTOOLKIT PROCESS BEGAIN!\n\r");
								#endif
						 
							
						#if _USE_EMBEDDED_SIM  
								 #if _ENABLE_GSM_CONFIG_QUECTEL
										/********************* TEST COMMAND *********************/
										FnGSMStoreSendingData( "AT"		 	  ,_GSM_RX_TIMEOUT2, _GSM_SEND_TYPE_CMD); 
										/********************* SIM TOOLKIT *********************/
										FnGSMStoreSendingData( "AT+QSTK=1"	,_GSM_RX_TIMEOUT3, _GSM_SEND_TYPE_CMD);
										/********************* ENVELOP INIT *********************/
										FnGSMStoreSendingData( "AT+STKTR=\"810301210082028281830100\"",
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD ); 
										/********************* SELECT ENVELOP MENU **************/
										 FnGSMStoreSendingData( "AT+STKENV=\"D30782020181900180\"", 
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD ); 
										/********************* SELECT AUTO OFF MENU *************/
										FnGSMStoreSendingData( "AT+STKTR=\"810301240402028281830100900101\"",
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );
										/********************* AUTO SWITCH OFF  *****************/
										 FnGSMStoreSendingData( "AT+STKTR=\"81030124040202828183010090010c\"",
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );											 
										/********************* SELECT ENVELOP MENU **************/
										 FnGSMStoreSendingData( "AT+STKENV=\"D30782020181900180\"",
										 _GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );  
										/********************* SELECT NETWORK MENU **************/
										 FnGSMStoreSendingData( "AT+STKTR=\"810301240402028281830100900102\"",
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );
										/********************* SWITCH TO PRIMARY/ SECONDARY **************/
										if (stVarGSM_All.stVarGSMNetworkPara.ucGSMNetworkState == RESET )
												FnGSMStoreSendingData( "AT+STKTR=\"810301240402028281830100900115\"", //16
												_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );
										else
												FnGSMStoreSendingData( "AT+STKTR=\"810301240402028281830100900116\"", 
												_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );
										/********************* CLEAR THE NETWORK FILE **************/
										FnGSMStoreSendingData( "AT+CRSM=214,28539,0,0,12,\"FFFFFFFFFFFFFFFFFFFFFFFF\"" ,
										_GSM_RX_TIMEOUT5 , _GSM_SEND_TYPE_CMD );
										
										/********************* SET DEFAULT AUTOBAUD **************/
										  FnGSMStoreSendingData( "AT+IPR=0"		 ,_GSM_RX_TIMEOUT2, _GSM_SEND_TYPE_CMD);	
											FnGSMStoreSendingData( "AT&W"				 ,_GSM_RX_TIMEOUT2, _GSM_SEND_TYPE_CMD); 
											
									#elif defined _ENABLE_GSM_CONFIG_SIM800
										/********************* SIM TOOLKIT *********************/
										FnGSMStoreSendingData( "AT"	 					 , _GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD);
										FnGSMStoreSendingData( "ATE0"	 				 , _GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD);
										FnGSMStoreSendingData( "AT+IPR=115200" , _GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD);	
									//FnGSMStoreSendingData( "AT&W"					 , _GSM_RX_TIMEOUT2 , _GSM_SEND_TYPE_CMD); 
										
										
									  FnGSMStoreSendingData( "AT+CRSM=214,28539,0,0,12,\"FFFFFFFFFFFFFFFFFFFFFFFF\"",
																					_GSM_RX_TIMEOUT3, _GSM_SEND_TYPE_CMD);
										FnGSMStoreSendingData( "AT+STKPCIS?"		  ,_GSM_RX_TIMEOUT2, _GSM_SEND_TYPE_CMD);	
									#endif 	
						#endif
		
						/**************************  **********************/
						#if defined _ENABLE_GSM_CONFIG_QUECTEL
										stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusBaudUpdated ;
					 #elif defined _ENABLE_GSM_CONFIG_SIM800		
										stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusHold ;
										stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt		 = RESET ;
					 #elif defined _ENABLE_GSM_CONFIG_FIBICOM		
										stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMBaudPositiveResponse ;
					 #endif
					 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt    = RESET ;
						
							#if _USE_DEBUG_GSM	 
									 #if defined _ENABLE_GSM_CONFIG_QUECTEL 
																_DEBUG_ALL_ENABLE_DIABLE
																printf("\n\rGSM BAUD COMMAND SEND!\n\r");
									 #elif defined _ENABLE_GSM_CONFIG_SIM800
																_DEBUG_ALL_ENABLE_DIABLE
																printf("GSM IS IN HOLD STATE!\n\r");
									 #elif defined _ENABLE_GSM_CONFIG_FIBICOM
																_DEBUG_ALL_ENABLE_DIABLE
																printf("GSM USING DEFAULT BAUDRATE 115200!\n\r");																	
									 #endif
							#endif
					 }
					 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt++;		 
				 }
			
			/********************* SWITCH OFF THE GSM ******************/				 
			else 
			if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus  == enGSMBaudPositiveResponse)
				{
				 #if defined _ENABLE_GSM_CONFIG_QUECTEL 	
								/************* GSM SWITCH ON LOW FOR 200ms  ************/ 	
								 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == _DNumber_20 )
									 { _GSM_CONFIG_GSM_ON_RESET 	}
								/************* GSM SWITCH ON HIGH FOR 800ms ************/ 			
								else 
								 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == _DNumber_22 )
									 { _GSM_CONFIG_GSM_ON_SET 		}
								/************* GSM SWITCH ON LOW FOR 200ms 	************/ 		
								else 
								 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == _DNumber_30 )
									 { _GSM_CONFIG_GSM_ON_RESET 	} 
					
					 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == _DNumber_42 )	
						 { 
									 #if _USE_DEBUG_GSM	
												_DEBUG_ALL_ENABLE_DIABLE
												printf("GSM MODULE RESET!\n\r");
									 #endif
									 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusResetDevice ;
									 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt 		= RESET ;		
						 }
						 
				  #elif defined _ENABLE_GSM_CONFIG_SIM800
 
									/************* GSM ENABLE HIGH FOR 300ms ************/ 	
									 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitEnableHigh)
										 { _GSM_CONFIG_GSM_ENABLE_ON  } 
									/************* GSM ENABLE LOW INFINITE *************/ 		
									else 
									 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitEnableLow )	
										 { _GSM_CONFIG_GSM_ENABLE_OFF } 
									/************* GSM ON HIGH FOR 1.5s ****************/ 	
									else 
									 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnHigh		 ) 
										 { _GSM_CONFIG_GSM_ON_SET     }  				 	 
									/************* GSM ON LOW INFINITE  ****************/ 		
									else 
									 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnLow		 ) 
										 { _GSM_CONFIG_GSM_ON_RESET 	}
									else 
									 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == enGSMInitOnReady	 )
										 {
												#if _USE_DEBUG_GSM
														_DEBUG_ALL_ENABLE_DIABLE 
														 printf("GSM 2ND RESTART!\n\r");
												#endif
													FnGSMStoreSendingData( "AT+CRSM=214,28539,0,0,12,\"FFFFFFFFFFFFFFFFFFFFFFFF\"",
																					_GSM_RX_TIMEOUT3, _GSM_SEND_TYPE_CMD);
													stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus  = enGSMStatusResetDevice;
													stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt 		= RESET ;		
										 }
					#endif
					
					stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt++;
			 }
			/********************* RESET THE GSM DEVICE ****************/						 
			else 
			if(	 stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus == enGSMStatusResetDevice   )
			  {
					#if defined _ENABLE_GSM_CONFIG_QUECTEL 	
								/************* GSM ENABLE HIGH FOR 300ms ************/ 	
										 if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == SET )
											 {_GSM_CONFIG_GSM_ENABLE_ON 
												 FnLowLevlDriverUSARTInit( _GSM_COM     ,  
												_GSM_NEW_BAUDRATE , _GSM_GPIO_PORT1 ,  
												_GSM_GPIO_PORT2   , _GSM_GPIO_PIN1  , _GSM_GPIO_PIN2 , SET );					
											 } 
								/************* GSM ENABLE LOW INFINITE *************/ 		
								else if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == (uint8_t)0x03 )	
											 { _GSM_CONFIG_GSM_ENABLE_OFF	} 
								/************* GSM ON HIGH FOR 1.1s ****************/ 	
								else if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == (uint8_t)0x0E ) 
											 { _GSM_CONFIG_GSM_ON_SET   	} 				 	 
								/************* GSM ON LOW INFINITE  ****************/ 		
								else if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == (uint8_t)0x1D ) 
											 { _GSM_CONFIG_GSM_ON_RESET 	} 
								 
					#elif _ENABLE_GSM_CONFIG_SIM800
								
					#endif
							if( stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt == (uint8_t)0x22 )
									 {
											#if _USE_DEBUG_GSM
													
														#if defined _ENABLE_GSM_CONFIG_QUECTEL 
																_DEBUG_ALL_ENABLE_DIABLE
																printf("GSM FINAL RESET AND READY!\n\r");
														#elif defined _ENABLE_GSM_CONFIG_SIM800
																_DEBUG_ALL_ENABLE_DIABLE
																printf("GSM READY TO USE!\n\r");	
														#endif
											#endif
										 /**************If SIM is Ready Then Reset All the network***********/
											stVarGSM_All.stVarGSMNetworkPara.ucGSMInitStatus = enGSMStatusInitProcess ;
											stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt 	 = SET 								;
											stVarGSM_All.stVarGSMCOMPort.ucGSMRxProcessFlag	 = RESET							;
											stVarGSM_All.stVarGSMCOMPort.ucGSMComTxStatus		 = enNoSendingProcess ;
											FnGSMStoreSendingData( "AT" , _GSM_RX_TIMEOUT3 , _GSM_SEND_TYPE_CMD	 );
											
									 }
						stVarGSM_All.stVarGSMNetworkPara.ucGSMInitCnt++;				 
				 }				 
	#endif		
									 
return RESET;
}



/*****************************************************************************
 **@Function      	: FnGPSEventProcess
 **@Descriptions  	: 
 **@parameters    	: None
 **@Return        	: None
*****************************************************************************/
uint8_t FnGPSEventProcess (void)
{

			#if _USE_GPS_COM 
					#if _ENABLE_GPS_CONFIG_QUECTEL
						if(		stVarGPS_All.stVarGPSCOMPort.ucGPSCurrStatus == enGPSNotReady 								)
						  {		 
								 /******* Send command to change the Baudrate on 9.6k ************/		
								 if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheBaudRateCommand1   )
									 {
										 char ucTemp[30]; sprintf(ucTemp,"$PSTMCFGPORT,0,0,1,%u", _GPS_NEW_BAUDRATE_QUECTEL );
										 FnGPSSendData( ucTemp ); //_GPS_NEW_BAUDRATE_QUECTEL = 115200
									 }
								 /******* Send command to disable unnessary para on 9.6k *********/
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheTimeAndReqFrame1 )
										 FnGPSSendData("$PSTMCFGMSGL,0,2,46,10");
								 /******* Send command to set the antenna on manual mode on 9.6k *******/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetDefaulttoModule1    )
										 FnGPSSendData("$PSTMSETPAR,1244,10107");
								 /******* Send command to change the Baudrate on 9.6k ************/
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSaveTheSettings1 			)
										 FnGPSSendData("$PSTMSAVEPAR");	
								 /********** RESET THE GPS SECTION *******************************/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOffTheGPSDevice1 )
										_GPS_RESET_HIGH
								 /********* Change the Budrate and Activate the GSP **************/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOnTheGPSDevice1 	)
									 { 
										 FnLowLevlDriverUSARTInit( _GPS_COM   ,  
										_GPS_NEW_BAUDRATE_QUECTEL, _GPS_GPIO_PORTx,  
										_GPS_GPIO_PORTx  , _GPS_GPIO_PIN1 , _GPS_GPIO_PIN2 , SET );			
									 _GPS_RESET_LOW }
								 /******* Send command to change the Baudrate on 115.2k **********/			 
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheBaudRateCommand2 )
									 {
										 char ucTemp[30]; sprintf(ucTemp,"$PSTMCFGPORT,0,0,1,%u",_GPS_NEW_BAUDRATE_QUECTEL);
										 FnGPSSendData( ucTemp );//_GPS_NEW_BAUDRATE_QUECTEL = 115200
									 }
								 /******* Send command to disable unnessary para on 115.2k *******/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheTimeAndReqFrame2 )
										 FnGPSSendData("$PSTMCFGMSGL,0,2,46,10");		//$PSTMCFGMSGL,0,1,42,10<CR><LF> // 
								 /******* Send command to set the antenna on manual mode on 115.2k *******/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetDefaulttoModule2    )
										 FnGPSSendData("$PSTMSETPAR,1244,10107");				
								 /******* Send command to change the Baudrate on 115.2k **********/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSaveTheSettings2			  )
										 FnGPSSendData("$PSTMSAVEPAR");	
								 /********** RESET THE GPS SECTION *******************************/	
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOffTheGPSDevice2 )
										 _GPS_RESET_HIGH
								 /****************** Activate the GSP ****************************/					
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOnTheGPSDevice2  )
										 _GPS_RESET_LOW	
								/****************** RESET ALL THE COUNTERS ***********************/
						else if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSInitProcessComplete	  )
									 {						
										 stVarGPS_All.stVarGPSCOMPort.ucGPSCurrStatus = enGPSReady 	;
										 stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt		= _DNumber_0	;
										 #if _USE_DEBUG_GPS
													_DEBUG_ALL_ENABLE_DIABLE
													printf("GPS FINAL RESET AND READY!\n\r");
										 #endif
										 return RESET ;
									 }	
										 stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt++ ;								 
					 }

					#elif defined _ENABLE_GPS_CONFIG_TELIT
						if(		stVarGPS_All.stVarGPSCOMPort.ucGPSCurrStatus == enGPSNotReady 								)
						{		 /******* Send command to change the Baudrate on 9.6k ************/		
								 if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheBaudRateCommand1   )
										 //default baudrate is 9600, new baudrate is 115200
										 FnGPSSendData("$PSTMSETPAR,1102,A");
									 
								 /******* Send command to disable unnessary para on 9.6k *********/
								 else 
								 if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSaveTheSettings1 )
										 FnGPSSendData("$PSTMSAVEPAR*58");	 
						
								/******* Send command to disable unnessary para on 9.6k *********/
								else 
								if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOffTheGPSDevice1 )
									{ FnGPSSendData("$PSTMSRR*49"); FnGPSComPortConfig(SET); }		

								/******* Send command to change the Baudrate on 115.2k ************/			
								else	
								 if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSetTheBaudRateCommand2   )
										 //default baudrate is 115200, new baudrate is 115200
										 FnGPSSendData("$PSTMSETPAR,1102,A");
									 
								 /******* Send command to disable unnessary para on 115.2k *********/
								 else 
								 if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSaveTheSettings2 )
										 FnGPSSendData("$PSTMSAVEPAR*58");	 
						
								/******* Send command to disable unnessary para on 115.2k *********/
								else 
								if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSSwitchOffTheGPSDevice2 )
									{ FnGPSSendData("$PSTMSRR*49"); }				
										
								else 
								if( stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt == enGPSInitProcessComplete	  )
									{						
										 stVarGPS_All.stVarGPSCOMPort.ucGPSCurrStatus = enGPSReady 	;
										 stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt		= _DNumber_0	;
										 #if _USE_DEBUG_GPS
													_DEBUG_ALL_ENABLE_DIABLE
													printf("GPS FINAL RESET AND READY!\n\r");
										 #endif
										 return RESET ;
									}	
										 stVarGPS_All.stVarGPSCOMPort.ucGPSInitCnt++ ;							
						}
					#endif	
		 #endif
		 
		 
	return RESET ;		 
}



/********* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
