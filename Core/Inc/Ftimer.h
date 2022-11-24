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

	#include "Drivers.h"


/* ----------------------------------------------------------------------------
 *                           MACROS
 * ----------------------------------------------------------------------------
 */
			
 
 /* ----------------------------------------------------------------------------
 *                           STRUCTURE VARIABLES
 * ----------------------------------------------------------------------------
 */
 
	/*********timer structure **********/
		typedef struct
		{
			
		 uint8_t  ucScanInput_TimerFlag_100msec;  // This flag is used to perfrom the task with the frequncy of 100 ms 	
		 uint8_t  ucScanInput_TimerFlag_1sec 	 ;  // This flag is used to perfrom the task with the frequncy of 1 sec  
		 uint8_t  ucScanInput_TimerFlag_1min 	 ;	// This flag is used to perfrom the task with the frequncy of 1 min  
		 uint32_t uiVar1ms_Counter			;					// Counter used to Count the 1 	 ms 
		 uint32_t uiVar10ms_Counter	 		; 				// Counter used to Count the 10  ms 
		 uint32_t uiVar100ms_Counter		;					// Counter used to Count the 100 ms		
		 uint32_t uiVar1sec_counter			;				  // Counter used to Count the 1 		s
		 uint32_t uiVar1min_counter		  ;					// Counter used to Count the 1		m
		 uint32_t uiVar1hour_counter		;					// Counter used to Count the 1		h 		
		
		 uint8_t  uiVar1day_counter			;
		 uint8_t  uiVar1month_counter		;				
		 uint8_t  uiVar1year_counter		;	
			
		 uint64_t	uiVar1SecUniversalCNT	;				
		
		 char 		ucLocalDateNTime[_DNumber_20];
			
		}stTimerCounter_ALL;

 
/* ---------------------------------------------------------------------------
*                           FUNCTIONS DECLARATION
* ----------------------------------------------------------------------------
*/
		
		
		 void FnWatchdogConfig								( void );
		 void Fn1msTimerConfig								( void );
		 void FnDelayTimerConfig							( void );
		 void FnShortDelay										(	void );
		 void FnDelay_1ms											(__IO uint32_t nTime );
		 void FnDelay_10ms										(__IO uint32_t nTime );
		 void TimingDelay_Decrement           ( void );
		 void FnScanIntervalAndReadAll_1SEC 	( void );
		 void FnScanIntervalAndReadAll_100mSEC( void );
		 void FnScanIntervalAndReadAll_1MIN 	( void );
		 uint8_t FnGPSEventProcess 					  ( void );
		 uint8_t FnGPRSEventProcess					  ( void );
		 void FnEventDataProcess							( void );	
		
		
		
		
/***************END OF FILE**************************/ 

