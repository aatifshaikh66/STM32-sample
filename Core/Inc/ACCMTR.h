/********************************************************************************
  * @file    ../CODES/ftimer.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    21-Oct-2018
  * @brief   Header for xxxxxxxx.c module
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


	#include "stdint.h"
//	#include "Drivers.h"
  #include "lsm6dsl_reg.h"
	#include "stm32g4xx.h"

/* ----------------------------------------------------------------------------
 *                           MACROS
 * ----------------------------------------------------------------------------
 */		
			
			#define _ACCMTR_ERROR							 (int8_t )-1
			#define _ACCMTR_AXIS_SWITCH				 (int8_t )-1
			#define _ACCMTR_NUMBER_OF_READING	 (uint8_t)0x0F	
			
			#define _ACCMTR_POSITIVE_CHANGES	 (uint8_t)0x02
			#define _ACCMTR_NEGATIVE_CHANGES	 (uint8_t)0x03
																										
			#define _ACCMTR_SUDDEN_CHANGE_POSITIVE	(float)250.0f
			#define _ACCMTR_SUDDEN_CHANGE_NEGATIVE	(float)-250.0f				
			
			#define _ACCMTR_ORIENT_HARNESS_FACE_RIGHT_GLASS		_DNumber_1
			#define _ACCMTR_ORIENT_HARNESS_FACE_LEFT_GLASS		_DNumber_2
			#define _ACCMTR_ORIENT_HARNESS_FACE_BACK_GLASS		_DNumber_3
			#define _ACCMTR_ORIENT_HARNESS_FACE_FRONT_GLASS		_DNumber_4
			
			#define _ACCMTR_MAX_ANGLE						 (float)9700.0f
			#define _ACCMTR_MAX_CHECK_ANGLE(x)   (float)( ((x) >= _ACCMTR_MAX_ANGLE)   ? (_ACCMTR_MAX_ANGLE):(x))
			#define _ACCMTR_CONVO_ANGLE(x)	 		 (float)( ( _ACCMTR_MAX_CHECK_ANGLE(x) / \
																										  _ACCMTR_MAX_ANGLE 	) * _DNumber_90 	 )
			#define _ACCMTR_CONVO_ANGLE_POS(x)	 (float)( _DNumber_90 - _ACCMTR_CONVO_ANGLE(x)	 	 )
			#define _ACCMTR_CONVO_ANGLE_NEG(x)	 (float)( _DNumber_90 + _ACCMTR_CONVO_ANGLE((x*-1)))				
			#define _ACCMTR_CONVO_G_TO_ANGLE(x)	 (float)( ((x) >= _DNumber_0) ? 	    \
																								    _ACCMTR_CONVO_ANGLE_POS(x): \
																									  _ACCMTR_CONVO_ANGLE_NEG(x)	)
			
			
			#define _ACCMTR_ENABLE										1
			#define _ACCMTR_DISABLE										0
			#define _ACCMTR_GET_ANGULAR_DISPLACEMENT	_ACCMTR_ENABLE
			
 /* ----------------------------------------------------------------------------
 *                           STRUCTURE VARIABLES
 * ----------------------------------------------------------------------------
 */
			
		/*********** Accelerometer ************/
		typedef struct
		{
			
			uint8_t		ucOrientation	 			 ;
			int16_t		uiHarshBreaking  		 ;
			int16_t		uiHarshacceleration  ;				
			int16_t		uiRashTurn					 ;
			int16_t		uiAngleThreshold		 ; 
			
			uint8_t		ucACCMTRAccelerationEvent		 		;
			uint8_t		ucACCMTRAccelerationEventCNT	  ;
			uint8_t		ucACCMTRAccelerationEventType		;
			uint8_t		ucACCMTRAccelerationEventOccured;
			
			uint8_t		ucACCMTRRashTurnEventCNT	  		;
			uint8_t		ucACCMTRRashTurnEventOccured		;			
			
			uint8_t		ucACCMTRTiltEventOccured			  ;
			
		}stACCMTRPara_All;
			
		
		
		
			
			typedef struct
			{
				
				uint8_t	 	ucDeviceID						;
				uint8_t		ucDeviceReset 				;
				uint8_t		ucAccelerometerMotion	;
				uint8_t		ucAccelerometerTilt		;				
				uint8_t	  ucAccelerometerActive ;
				uint8_t 	ucAccelerometerENnDS  ;
				uint8_t		ucAccelerometerInitial;
				
			}stACCMTRConfig;
 
			
			typedef struct
			{
				
			  stACCMTRPara_All	stVarACCMTRPara_All;
				stACCMTRConfig		stVarACCMTRConfig	 ;
				
				lsm6dsl_ctx_t  	stVarACCMTRSTACKPTR;
				lsm6dsl_reg_t 	stVarACCMTRSTACKREG;
			  axis3bit16_t 		unRawAcceleration	 ;
			  axis3bit16_t 		unRawAngularRate	 ; 
				axis3bit16_t 		unRawTemperature	 ; 
					
				float			flACCMTR2G_Axis1				 ;
				float			flACCMTR2G_Axis2				 ;
		/*	float			flACCMTR2G_Axis3				 ;	*/			
				
				#if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT == _ACCMTR_ENABLE )
							 float flACCMTRAngleArray1	[ _DNumber_10 ];
							 float flACCMTRAngleArray2	[ _DNumber_10 ];
					/*	 float flACCMTRAngleArray3	[ _DNumber_10 ];	*/			
				#endif
				
				float		flACCMTRAccelerationArray1 [ _DNumber_10 ];
				float		flACCMTRAccelerationArray2 [ _DNumber_10 ];
				float		flACCMTRAccelerationCheck1 [ _ACCMTR_NUMBER_OF_READING ];
				float		flACCMTRAccelerationCheck2 [ _ACCMTR_NUMBER_OF_READING ];
				
				#if ( _ACCMTR_GET_ANGULAR_DISPLACEMENT == _ACCMTR_ENABLE )
							 float	flACCMTRAvgAngle1	 ;
							 float	flACCMTRAvgAngle2	 ;
					/*	 float	flACCMTRAvgAngle3	 ;	*/
				#endif
				float			flACCMTRAvgAcceleration1;
				float			flACCMTRAvgAcceleration2;				
				uint8_t		ucACCMTRArrayCNT	   	  ;		
				uint8_t		ucACCMTRArrayCheckCNT	  ;			
				
				
				float 		acceleration_mg	 [_DNumber_3];
				float			angular_rate_mdps[_DNumber_3];
				float			flTemperatureDegree		 ;		


			}stACCMTRVar_All;
			

			
/* ---------------------------------------------------------------------------
*                           FUNCTIONS DECLARATION
* ----------------------------------------------------------------------------
*/

		extern void 	 FnACCMTRI2CInit	 (	void	);
		extern uint8_t FnACCMTRConfigPara(  void  );
		extern  int 	 FnACCLMTRReadData ( uint8_t ucSlaveAddress , uint8_t  ucRegAdd 
									,uint8_t ucDataLen , uint8_t *ucDataBuff );
		extern  int 	 FnACCLMTRWriteData( uint8_t ucSlaveAddress , uint8_t  ucRegAdd 
									,uint8_t ucDataLen , uint8_t *ucDataBuff );
		extern 	void 	 FnACCMTRScanAndRead( void  );
		extern  void   FnCheckAccelerometerEvent( void );
		
		
		
		
		
