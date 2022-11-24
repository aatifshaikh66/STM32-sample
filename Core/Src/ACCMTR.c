/********************************************************************************
  * @file    ../CODES/GSM.c 
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
						
			#define _ACCMTR_CS_HIGH						LL_GPIO_SetOutputPin  (GPIOA, LL_GPIO_PIN_8);
			#define _ACCMTR_CS_LOW						LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);						


/*****************************************************************************
 **@Function 		  : 	FnPlatform_write
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
void FnACCMTRI2CInit (void)
{

	//LowLevlDriverI2CInit();
	
	#ifdef _USE_DEBUG_ACCMTR
				 _DEBUG_ALL_ENABLE_DIABLE	
					printf ("ACCELEROMETER I2C INIT\n\r");
	#endif

}


/*****************************************************************************
 **@Function 		  : 	FnPlatform_write
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
static int32_t  FnACCMTRPlatformWrite(void  *handle, uint8_t	 Reg, 
			 uint8_t *Bufp, uint16_t  len)
{	
	
		_ACCMTR_CS_LOW
		/* Write character in Data register.
		TXE flag is cleared by reading data in DR register */	
		while(LL_SPI_IsActiveFlag_TXE (SPI1)  == RESET){ };
		LL_SPI_TransmitData8(SPI1, Reg & (uint8_t)0x7F);
		/* Read character in Data register.
		RXNE flag is cleared by reading data in DR register */					 
		while(LL_SPI_IsActiveFlag_RXNE(SPI1)  == RESET){};
		      LL_SPI_ReceiveData8(SPI1);				
			
	for ( uint16_t ucLoop = RESET ; ucLoop < len ; ucLoop++ )	
			{				
				while(LL_SPI_IsActiveFlag_TXE (SPI1)  == RESET){ };
				LL_SPI_TransmitData8(SPI1, Bufp[ucLoop]);				
				
				while(LL_SPI_IsActiveFlag_RXNE(SPI1)  == RESET){};
				      LL_SPI_ReceiveData8(SPI1);	
			}
			
	_ACCMTR_CS_HIGH 			
	return  RESET	;				
}

/*****************************************************************************
 **@Function 		  : 	platform_read
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
static int32_t FnACCMTRPlatformRead(void *handle, uint8_t  Reg,
																	 uint8_t *Bufp, uint16_t len)
{	
	
		_ACCMTR_CS_LOW
		/* Write character in Data register.
		TXE flag is cleared by reading data in DR register */	
		while(LL_SPI_IsActiveFlag_TXE (SPI1)  == RESET){ };
					LL_SPI_TransmitData8(SPI1, Reg | (uint8_t)0x80);
		/* Read character in Data register.
		RXNE flag is cleared by reading data in DR register */					 
		while(LL_SPI_IsActiveFlag_RXNE(SPI1)  == RESET){};
		    uint8_t ucChar =  LL_SPI_ReceiveData8(SPI1);			
			
	for ( uint16_t ucLoop = RESET ; ucLoop < len ; ucLoop++ )	
			{				
				while(LL_SPI_IsActiveFlag_TXE (SPI1)  == RESET){};				
				LL_SPI_TransmitData8(SPI1, (uint8_t)0xAA);												
				while(LL_SPI_IsActiveFlag_RXNE(SPI1)  == RESET){};
				Bufp[ucLoop] = LL_SPI_ReceiveData8(SPI1);	
			}

	_ACCMTR_CS_HIGH 					
	return  RESET	;			
}
	
/*****************************************************************************
 **@Function 		  : 	WritetempHumid
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
uint8_t FnACCMTRConfigPara(void)
{

  
	//GotoLableUP1:
  stVarACCMTRVar_All.stVarACCMTRSTACKPTR
 .write_reg = FnACCMTRPlatformWrite	;
  stVarACCMTRVar_All.stVarACCMTRSTACKPTR
 .read_reg  = FnACCMTRPlatformRead	;
  stVarACCMTRVar_All.stVarACCMTRSTACKPTR
 .handle  	= NULL ;  	

	
	lsm6dsl_device_id_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
	&stVarACCMTRVar_All.stVarACCMTRConfig.ucDeviceID );
		
	
//	#ifdef _USE_DEBUG_ACCMTR
//				 _DEBUG_ALL_ENABLE_DIABLE	
					printf ("ACCELEROMETER ID = %x \n\r",
					stVarACCMTRVar_All.stVarACCMTRConfig.ucDeviceID);
//	#endif
			
	if( LSM6DSL_ID != stVarACCMTRVar_All
		  .stVarACCMTRConfig.ucDeviceID		)
		{
			stVarACCMTRVar_All.stVarACCMTRConfig
			.ucAccelerometerActive = RESET ;
//			#ifdef _USE_DEBUG_ACCMTR
//						 _DEBUG_ALL_ENABLE_DIABLE	
							printf ("ACCELEROMETER IS NOT WORKING\n\r" );
//			#endif	
			//	FnDelay_10ms(_DNumber_1);
				lsm6dsl_device_id_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
				&stVarACCMTRVar_All.stVarACCMTRConfig.ucDeviceID );
						
			return _DNumber_1 ;	
		}
	else
		{
			 stVarACCMTRVar_All.stVarACCMTRConfig
			.ucAccelerometerActive = SET ;
//			#ifdef _USE_DEBUG_ACCMTR
//						 _DEBUG_ALL_ENABLE_DIABLE	
							printf ("ACCELEROMETER IS WORKING\n\r" );
//			#endif	
		}		
	
			// Restore default configuration
			lsm6dsl_reset_set(&stVarACCMTRVar_All
		 .stVarACCMTRSTACKPTR, PROPERTY_ENABLE);
  do {
			lsm6dsl_reset_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
			&stVarACCMTRVar_All.stVarACCMTRConfig.ucDeviceReset);
		 } while (stVarACCMTRVar_All.stVarACCMTRConfig.ucDeviceReset);
	
	// Enable Block Data Update
		 lsm6dsl_block_data_update_set(&stVarACCMTRVar_All
		.stVarACCMTRSTACKPTR, PROPERTY_ENABLE);

	// Set Output Data Rate
		 lsm6dsl_xl_data_rate_set(&stVarACCMTRVar_All
		.stVarACCMTRSTACKPTR, LSM6DSL_XL_ODR_12Hz5);
		 lsm6dsl_gy_data_rate_set(&stVarACCMTRVar_All
		.stVarACCMTRSTACKPTR, LSM6DSL_GY_ODR_12Hz5);

	// Set full scale
		 lsm6dsl_xl_full_scale_set(&stVarACCMTRVar_All
		.stVarACCMTRSTACKPTR, LSM6DSL_2g);
		 lsm6dsl_gy_full_scale_set(&stVarACCMTRVar_All
		.stVarACCMTRSTACKPTR, LSM6DSL_2000dps);
		 
			
	// Configure filtering chain(No aux interface)
	// Accelerometer - analog filter
		 lsm6dsl_xl_filter_analog_set(&stVarACCMTRVar_All
	  .stVarACCMTRSTACKPTR, LSM6DSL_XL_ANA_BW_400Hz);
		

		/* Accelerometer - LPF1 + LPF2 path */   
		lsm6dsl_xl_lp2_bandwidth_set(&stVarACCMTRVar_All
	 .stVarACCMTRSTACKPTR, LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_100);
		
		
		/* Gyroscope - filtering chain */
		lsm6dsl_gy_band_pass_set(&stVarACCMTRVar_All
	 .stVarACCMTRSTACKPTR, LSM6DSL_HP_260mHz_LP1_STRONG);	 

			#if _USE_DEBUG_ACCMTR
					_DEBUG_ALL_ENABLE_DIABLE	
					 printf ("ACCELEROMETER PARA INIT COMPLETE\n\r" );
			#endif		

	return _DNumber_0 ;
}


/*****************************************************************************
 **@Function 		  : 	FnACCMTRScanAndRead
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
void FnACCMTRScanAndRead(void)
{

    lsm6dsl_status_reg_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
  	&stVarACCMTRVar_All.stVarACCMTRSTACKREG.status_reg); 
		
		lsm6dsl_all_sources_t stVarlsm6dsl_all_sources_t;
		lsm6dsl_all_sources_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
		&stVarlsm6dsl_all_sources_t);
	
    if (stVarACCMTRVar_All.stVarACCMTRSTACKREG.status_reg.xlda)
    { 
      /* Read magnetic field data */
      memset(stVarACCMTRVar_All.unRawAcceleration.u8bit, NULL , _DNumber_3 * sizeof(int16_t));
      lsm6dsl_acceleration_raw_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
			stVarACCMTRVar_All.unRawAcceleration.u8bit);
			
			/*convert the raw data into G force*/
			 stVarACCMTRVar_All.flACCMTR2G_Axis1 = LSM6DSL_FROM_FS_2g_TO_mg
		  (stVarACCMTRVar_All.unRawAcceleration.i16bit[_DNumber_0]);
       stVarACCMTRVar_All.flACCMTR2G_Axis2 = LSM6DSL_FROM_FS_2g_TO_mg
		  (stVarACCMTRVar_All.unRawAcceleration.i16bit[_DNumber_1]);
		/* stVarACCMTRVar_All.flACCMTR2G_Axis3 = LSM6DSL_FROM_FS_2g_TO_mg
		  (stVarACCMTRVar_All.unRawAcceleration.i16bit[_DNumber_2]); */
			
		/* convert the raw data and store the angle into an array 	 */
			 #if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT == _ACCMTR_ENABLE )
						  stVarACCMTRVar_All.flACCMTRAngleArray1
						[ stVarACCMTRVar_All.ucACCMTRArrayCNT ] = 
						 _ACCMTR_CONVO_G_TO_ANGLE( stVarACCMTRVar_All.flACCMTR2G_Axis1 * _DNumber_10 ) ;
							stVarACCMTRVar_All.flACCMTRAngleArray2
						[ stVarACCMTRVar_All.ucACCMTRArrayCNT ] = 
						 _ACCMTR_CONVO_G_TO_ANGLE( stVarACCMTRVar_All.flACCMTR2G_Axis2 * _DNumber_10 ) ;
					/*	stVarACCMTRVar_All.flACCMTRAngleArray3
						[ stVarACCMTRVar_All.ucACCMTRArrayCNT ] = 
						 _ACCMTR_CONVO_G_TO_ANGLE( stVarACCMTRVar_All.flACCMTR2G_Axis3 * _DNumber_10 ) ; */
			 #endif	
			 /* store the G force into an array */
						  stVarACCMTRVar_All.flACCMTRAccelerationArray1
					  [ stVarACCMTRVar_All.ucACCMTRArrayCNT ] = 
						  stVarACCMTRVar_All.flACCMTR2G_Axis1 ;
							stVarACCMTRVar_All.flACCMTRAccelerationArray2
					  [ stVarACCMTRVar_All.ucACCMTRArrayCNT ] = 
						  stVarACCMTRVar_All.flACCMTR2G_Axis2 ;
										
										
			 /* take an averag of last _ACCMTR_NUMBER_OF_READING readings*/
			 #if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT 		== _ACCMTR_ENABLE)	
							stVarACCMTRVar_All.flACCMTRAvgAngle1 = 
							stVarACCMTRVar_All.flACCMTRAvgAngle2 = _DNumber_0 	 ;
					/*	stVarACCMTRVar_All.flACCMTRAvgAngle3 = _DNumber_0 	 ; */ 
			 #endif
				 stVarACCMTRVar_All.flACCMTRAvgAcceleration1 =
				 stVarACCMTRVar_All.flACCMTRAvgAcceleration2 = _DNumber_0 ;	
				 for(uint8_t   		 ucLoopCnt4 = _DNumber_0	  ; 
						 ucLoopCnt4 < _DNumber_10 ;  ucLoopCnt4++ )  // _ACCMTR_NUMBER_OF_READING/
				 {	
					#if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT 		   == _ACCMTR_ENABLE	  )	
								 stVarACCMTRVar_All .flACCMTRAvgAngle1 +=  stVarACCMTRVar_All
							  .flACCMTRAngleArray1[ ucLoopCnt4 ] 		 ;
								 stVarACCMTRVar_All .flACCMTRAvgAngle2 +=  stVarACCMTRVar_All
							  .flACCMTRAngleArray2[ ucLoopCnt4 ] 		 ;
						/*	 stVarACCMTRVar_All .flACCMTRAvgAngle3 +=  stVarACCMTRVar_All
							  .flACCMTRAngleArray3[ ucLoopCnt4 ] 		 ;	*/
					#endif
					stVarACCMTRVar_All.flACCMTRAvgAcceleration1  += 
					stVarACCMTRVar_All.flACCMTRAccelerationArray1 [ ucLoopCnt4 ] ;
					 
					stVarACCMTRVar_All.flACCMTRAvgAcceleration2  += 
					stVarACCMTRVar_All.flACCMTRAccelerationArray2 [ ucLoopCnt4 ] ; 
				 }  
					#if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT 	 		 == _ACCMTR_ENABLE )	
								 stVarACCMTRVar_All.flACCMTRAvgAngle1  /= _DNumber_10  ;
								 stVarACCMTRVar_All.flACCMTRAvgAngle2  /= _DNumber_10  ;
						 /*  stVarACCMTRVar_All.flACCMTRAvgAngle3  /= _DNumber_10  ; */
								 stVarACCMTRVar_All.flACCMTRAvgAngle1 	= _DNumber_90  -
							   stVarACCMTRVar_All.flACCMTRAvgAngle1		;
								 stVarACCMTRVar_All.flACCMTRAvgAngle2 	= _DNumber_90  -
							   stVarACCMTRVar_All.flACCMTRAvgAngle2		;
						/*	 stVarACCMTRVar_All.flACCMTRAvgAngle3 	= _DNumber_90  -
							   stVarACCMTRVar_All.flACCMTRAvgAngle3		; */
					#endif
					stVarACCMTRVar_All.flACCMTRAvgAcceleration1   /= _DNumber_10  ;
				  stVarACCMTRVar_All.flACCMTRAvgAcceleration2   /= _DNumber_10  ;
				 
				/* increament the array pointer */
				 stVarACCMTRVar_All.ucACCMTRArrayCNT ++;
		 if( stVarACCMTRVar_All.ucACCMTRArrayCNT >= _DNumber_10)
			 { stVarACCMTRVar_All.ucACCMTRArrayCNT  = _DNumber_0 ;
				 stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerInitial = SET ; }	
				 
			 /*store the average acceleration into an array*/
				stVarACCMTRVar_All.flACCMTRAccelerationCheck1
			 [stVarACCMTRVar_All.ucACCMTRArrayCheckCNT]	 = 
				stVarACCMTRVar_All.flACCMTRAvgAcceleration1 ;

				stVarACCMTRVar_All.flACCMTRAccelerationCheck2
			 [stVarACCMTRVar_All.ucACCMTRArrayCheckCNT]	 = 
				stVarACCMTRVar_All.flACCMTRAvgAcceleration2 ;		
				 
				 
				 stVarACCMTRVar_All.ucACCMTRArrayCheckCNT ++;
		 if( stVarACCMTRVar_All.ucACCMTRArrayCheckCNT >= _ACCMTR_NUMBER_OF_READING )
			 { 
				 stVarACCMTRVar_All.ucACCMTRArrayCheckCNT  = _DNumber_0 ;	 
			 }	
				
			  /*
					#if _USE_DEBUG_ACCMTR
								_DEBUG_ALL_ENABLE_DIABLE printf ( "X/Y-AXIS ---> X_%.2f  Y_%.2f \n\r" ,
								 stVarACCMTRVar_All.flACCMTRAvgAcceleration2, stVarACCMTRVar_All.flACCMTRAvgAcceleration1 ); 	
				
			   #endif 
			  */		 
					
					 /* increament the array pointer */
					 if( stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerInitial 			 == SET
					 &&  stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventOccured != SET )
					for( uint8_t ucLoopCnt12 = _DNumber_0 ; ucLoopCnt12 
										< _ACCMTR_NUMBER_OF_READING ; ucLoopCnt12++ )
						 {							 
								float fltempVar =  stVarACCMTRVar_All.flACCMTRAccelerationCheck1
									[ucLoopCnt12] -  stVarACCMTRVar_All.flACCMTRAvgAcceleration1 ;
								 if( fltempVar >= _ACCMTR_SUDDEN_CHANGE_POSITIVE 
									|| fltempVar <= _ACCMTR_SUDDEN_CHANGE_NEGATIVE  )
									{
										
										#if _USE_DEBUG_ACCMTR
												_DEBUG_ALL_ENABLE_DIABLE
												 printf ("Y SUDDEN CHANGE OLD = %.2f CUR = %.2f  DIFF = %.2f\n\r" ,
												 stVarACCMTRVar_All.flACCMTRAccelerationCheck1[ ucLoopCnt12 ],
												 stVarACCMTRVar_All.flACCMTRAvgAcceleration1  , fltempVar   );		
										#endif 
										
										 if( fltempVar >= _ACCMTR_SUDDEN_CHANGE_POSITIVE )
												 stVarACCMTRVar_All.stVarACCMTRPara_All
												.ucACCMTRAccelerationEventType = _ACCMTR_POSITIVE_CHANGES ;									
										else stVarACCMTRVar_All.stVarACCMTRPara_All
												.ucACCMTRAccelerationEventType = _ACCMTR_NEGATIVE_CHANGES ;
												 stVarACCMTRVar_All.stVarACCMTRPara_All
											  .ucACCMTRAccelerationEvent 		 = SET ;  break   ; 	
									}
											fltempVar  =  stVarACCMTRVar_All.flACCMTRAccelerationCheck2
									[ucLoopCnt12]  -  stVarACCMTRVar_All.flACCMTRAvgAcceleration2  ;
								 if( fltempVar  >= _ACCMTR_SUDDEN_CHANGE_POSITIVE 
									|| fltempVar  <= _ACCMTR_SUDDEN_CHANGE_NEGATIVE  )
									{
										#if _USE_DEBUG_ACCMTR
												_DEBUG_ALL_ENABLE_DIABLE
												 printf ("X SUDDEN CHANGE OLD = %.2f CUR = %.2f  DIFF = %.2f\n\r" ,
												 stVarACCMTRVar_All.flACCMTRAccelerationCheck2[ucLoopCnt12],
												 stVarACCMTRVar_All.flACCMTRAvgAcceleration2  , fltempVar );		
										#endif
										 if( fltempVar >= _ACCMTR_SUDDEN_CHANGE_POSITIVE )
												 stVarACCMTRVar_All.stVarACCMTRPara_All
												.ucACCMTRAccelerationEventType = _ACCMTR_POSITIVE_CHANGES ;									
										else stVarACCMTRVar_All.stVarACCMTRPara_All
												.ucACCMTRAccelerationEventType = _ACCMTR_NEGATIVE_CHANGES ;
												 stVarACCMTRVar_All.stVarACCMTRPara_All
												.ucACCMTRAccelerationEvent 		 = 	SET ;  break ; 	
									}										
						 } 
						 
					if ( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEvent == SET	)
						 { stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEvent	= RESET ;
						 
								stVarACCMTRVar_All.stVarACCMTRPara_All
							 .ucACCMTRAccelerationEventCNT ++ ;
								if( stVarACCMTRVar_All.stVarACCMTRPara_All
							 .ucACCMTRAccelerationEventCNT >= _DNumber_5 )
								{  	
									 stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventCNT	   = RESET;
									 stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventOccured = SET	;
									
									if( stVarACCMTRVar_All.stVarACCMTRPara_All.
										   ucACCMTRAccelerationEventType == _ACCMTR_POSITIVE_CHANGES )
										{
											#if _USE_DEBUG_ACCMTR
													_DEBUG_ALL_ENABLE_DIABLE
													 printf ("HARSH ACCELERATION!\n\r");											
											#endif
											#if _USE_GSM_COM  & _USE_FLASH_SPI
													 FnGPRSPrimaryEventGenrate(_GSM_FRAME_TYPE_HARSH_ACCEL_NO);
											#endif
										}
									else
									{
									 #if _USE_DEBUG_ACCMTR
											 _DEBUG_ALL_ENABLE_DIABLE
												printf ("HARSH BREAK!\n\r");											
									 #endif
									 #if _USE_GSM_COM  & _USE_FLASH_SPI	
												FnGPRSPrimaryEventGenrate(_GSM_FRAME_TYPE_HARSH_BREAKING_NO);
									 #endif
									}  }	
						  }
						 else 
						 if  ( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEvent				== RESET
							&&   stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventOccured != SET 	   )
								 {
									 stVarACCMTRVar_All.stVarACCMTRPara_All
									.ucACCMTRAccelerationEventCNT			= RESET		;
								 }	

							if(( stVarACCMTRVar_All.flACCMTRAvgAngle1 > (float) 45.0f 
							 ||	 stVarACCMTRVar_All.flACCMTRAvgAngle1 < (float)-45.0f
							 ||  stVarACCMTRVar_All.flACCMTRAvgAngle2 > (float) 45.0f 
							 ||	 stVarACCMTRVar_All.flACCMTRAvgAngle2 < (float)-45.0f )
							 &&  stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerInitial  == SET ) 
								{									
									if(	stVarACCMTRVar_All.stVarACCMTRPara_All
										 .ucACCMTRTiltEventOccured != SET )
										{	
											stVarACCMTRVar_All.stVarACCMTRPara_All
										 .ucACCMTRTiltEventOccured  = SET ;
											#if _USE_DEBUG_ACCMTR
													_DEBUG_ALL_ENABLE_DIABLE
													 printf ("VEHICLE IS IN TILT POSITION!\n\r");											
											#endif 
											#if _USE_GSM_COM  & _USE_FLASH_SPI
													 FnGPRSPrimaryEventGenrate(_GSM_FRAME_TYPE_TILT_NO);
											#endif
										}	
								}  
								else
								{
									 stVarACCMTRVar_All.stVarACCMTRPara_All
									.ucACCMTRTiltEventOccured	 = RESET ;	
								}
      }
    if( stVarACCMTRVar_All.stVarACCMTRSTACKREG.status_reg.gda )
			{
				/* Read magnetic field data */
				memset(stVarACCMTRVar_All.unRawAngularRate.u8bit,  NULL , _DNumber_3 * sizeof(int16_t));
				lsm6dsl_angular_rate_raw_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
				stVarACCMTRVar_All.unRawAngularRate.u8bit);
					
				 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_0] = LSM6DSL_FROM_FS_2000dps_TO_mdps
				(stVarACCMTRVar_All.unRawAngularRate.i16bit[_DNumber_0]);
				 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_1] = LSM6DSL_FROM_FS_2000dps_TO_mdps
				(stVarACCMTRVar_All.unRawAngularRate.i16bit[_DNumber_1]);
				 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_2] = LSM6DSL_FROM_FS_2000dps_TO_mdps
				(stVarACCMTRVar_All.unRawAngularRate.i16bit[_DNumber_2]);
			
					/*	#if _USE_DEBUG_ACCMTR
								_DEBUG_ALL_ENABLE_DIABLE
								 printf("Angular rate [mdps]:%4.2f      %4.2f     %4.2f\r\n",
								 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_0] ,
								 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_1] ,
								 stVarACCMTRVar_All.angular_rate_mdps[_DNumber_2] );
						#endif */
				
				
				if((( stVarACCMTRVar_All.angular_rate_mdps[ _DNumber_2 ] >  60000.0f  )
					||( stVarACCMTRVar_All.angular_rate_mdps[ _DNumber_2 ] <  RESET
					&&  stVarACCMTRVar_All.angular_rate_mdps[ _DNumber_2 ] < -60000.0f ))
				  &&( stVarACCMTRVar_All.stVarACCMTRConfig.ucAccelerometerInitial  == SET ))
					 {
						 if ( stVarACCMTRVar_All.stVarACCMTRPara_All
								 .ucACCMTRRashTurnEventOccured != SET )
						 {
							 stVarACCMTRVar_All.stVarACCMTRPara_All
							.ucACCMTRRashTurnEventOccured		= SET ; 
								#if _USE_DEBUG_ACCMTR
										_DEBUG_ALL_ENABLE_DIABLE
										 printf ("RASH TURN!\n\r");											
								#endif
							  #if _USE_GSM_COM  & _USE_FLASH_SPI
										 FnGPRSPrimaryEventGenrate(_GSM_FRAME_TYPE_RASH_TURN_NO);
							  #endif 
						 }
					 }
      }
			
		/*
    if ( stVarACCMTRVar_All.stVarACCMTRSTACKREG.status_reg.tda  )
    {  
      // Read temperature data 
      memset( stVarACCMTRVar_All.unRawTemperature.u8bit,  NULL , _DNumber_3 * sizeof(int16_t) );
      lsm6dsl_temperature_raw_get(&stVarACCMTRVar_All.stVarACCMTRSTACKPTR, 
			stVarACCMTRVar_All.unRawTemperature.u8bit);
      stVarACCMTRVar_All.flTemperatureDegree   = 
			LSM6DSL_FROM_LSB_TO_degC(stVarACCMTRVar_All.unRawTemperature.i16bit[0] );
		#if _USE_DEBUG_ACCMTR
			  _DEBUG_ALL_ENABLE_DIABLE
      printf("Temperature [degC]:%.2f\r\n\n", stVarACCMTRVar_All.flTemperatureDegree );
		#endif	
    }
		*/	
		
		
		
}

			
/****************************************************************************
 **@Function 		  : 	FnCheckAccelerometerEvent
 **@Descriptions	: 	
 **@parameters		: 	None
 **@return				: 	None
*****************************************************************************/
void FnCheckAccelerometerEvent( void )
{

		if( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventOccured == SET )
			{
						stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventCNT ++;
				if( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRAccelerationEventCNT >= _DNumber_10 )
					{ 
						 stVarACCMTRVar_All.stVarACCMTRPara_All
						.ucACCMTRAccelerationEventCNT 		= RESET	  ;
						 stVarACCMTRVar_All.stVarACCMTRPara_All
						.ucACCMTRAccelerationEventOccured = RESET		;		
						 #if _USE_DEBUG_ACCMTR
								 _DEBUG_ALL_ENABLE_DIABLE
									printf ("HARSH EVENT RESET!\n\r");											
						 #endif	
					}
			}
			
			
		if( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRRashTurnEventOccured == SET )
			{
						stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRRashTurnEventCNT ++;
				if( stVarACCMTRVar_All.stVarACCMTRPara_All.ucACCMTRRashTurnEventCNT >= _DNumber_10 )
					{ 
						 stVarACCMTRVar_All.stVarACCMTRPara_All
						.ucACCMTRRashTurnEventOccured = RESET ;
							
						 stVarACCMTRVar_All.stVarACCMTRPara_All.
						 ucACCMTRRashTurnEventCNT			= RESET ;
						
						 #if _USE_DEBUG_ACCMTR
								 _DEBUG_ALL_ENABLE_DIABLE
									printf ("RASH TURN EVENT RESET!\n\r");											
						 #endif	
						
					}	
			}					
}



/*****************END OF FILE*******************/
