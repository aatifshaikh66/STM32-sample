/********************************************************************************
  * @file    ../CODES/GPS.h 
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
//	#include "system.h"
		#include "stm32g4xx.h"

/* ----------------------------------------------------------------------------
 *                           MACROS
 * ----------------------------------------------------------------------------
 */
 
		/************ COM PORT USART DEF ***************/		
		#define _GPS_COM			  	 USART1
		
		
		/************ COM PORT BAUD RATE ***************/				
		#define _GPS_NEW_BAUDRATE_QUECTEL	(uint32_t)115200
		#define _GPS_OLD_BAUDRATE					(uint16_t)9600

			
		/************ COM PORT GPORT *******************/	
		#define _GPS_GPIO_PORTx		GPIOA		
		
		/************ COM PORT PINS ********************/
		#define _GPS_GPIO_PIN1		LL_GPIO_PIN_9
		#define _GPS_GPIO_PIN2		LL_GPIO_PIN_10
				


	  /************ COM PORT RCC ENABLE **************/
		#define _GPS_RESET_HIGH		LL_GPIO_SetOutputPin  (_GPS_RESET_PORT, _GPS_RESET_PIN);
		#define _GPS_RESET_LOW		LL_GPIO_ResetOutputPin(_GPS_RESET_PORT, _GPS_RESET_PIN);


		/************ GPS COM PARAMTER *****************/
    #define _GPS_COM_MAXBUFF	(uint16_t)0x96
		#define _GPS_ARRAY_SIZE		_DNumber_10
		#define _GPS_RX_LF_CHAR		(char    )'\n'
		#define _GPS_RX_COMA_CHAR	(char    )','
		#define _GPS_RX_COMA_STR	(char   *)","	
		#define _GPS_RX_DOT_CHAR  (char		 )'.'
		#define _GPS_RX_DOT_STR   (char		*)"."			
		#define _GPS_RX_SOF				(char 	 )'$'
		#define _GPS_RX_CRC_INDI	(char 	 )'*'
		#define _GPS_RX_LAT_NORTH (char		 )'N'	
		#define _GPS_RX_LAT_SOUTH (char		 )'S'	
		#define _GPS_RX_LONG_EAST (char		 )'E'	
		#define _GPS_RX_LONG_WEST (char		 )'W'
		
		
		#define _GPRMC_COMA_COUNT  _DNumber_12
		#define _GPGGA_COMA_COUNT  _DNumber_14
		#define _GNGSA_COMA_COUNT  _DNumber_17
		
		
	  #define _GPS_SELEC_GGA		 _DNumber_1
	  #define _GPS_SELEC_GSA		 _DNumber_2		
	  #define _GPS_SELEC_RMC		 _DNumber_3		
		
		
		#define _GPS_RX_GPRMC			   (char *)"GPRMC"
		#define _GPS_RX_GPGGA			   (char *)"GPGGA"		      
	  #define _GPS_RX_GPVTG  			 (char *)"GPVTG"
    #define _GPS_RX_GNGSA  			 (char *)"GNGSA"
    #define _GPS_RX_GPGSV  			 (char *)"GPGSV"
    #define _GPS_RX_GAGSV  			 (char *)"GAGSV"
    #define _GPS_RX_IRGSV  			 (char *)"IRGSV"
    #define _GPS_RX_GPGLL  			 (char *)"GPGLL"
    #define _GPS_RX_PSTMANTENNA  (char *)"PSTMANTENNASTATUS"
		
		
		
 /* ----------------------------------------------------------------------------
 *                           STRUCTURE VARIABLES
 * ----------------------------------------------------------------------------
 */
		
			typedef enum
			{
			 enGPSNotReady 							  =  _DNumber_0  ,
			 enGPSReady 								  =  _DNumber_10 ,				
			 enGPSSetTheBaudRateCommand1  =  _DNumber_20 ,
			 enGPSSetTheTimeAndReqFrame1  =  _DNumber_30 ,
			 enGPSSetDefaulttoModule1			=	 _DNumber_40 ,				
			 enGPSSaveTheSettings1				=  _DNumber_50 , 	
			 enGPSSwitchOffTheGPSDevice1	=  _DNumber_60 ,
			 enGPSSwitchOnTheGPSDevice1		=  _DNumber_70 ,				
			 enGPSSetTheBaudRateCommand2  =  _DNumber_90 ,	
			 enGPSSetTheTimeAndReqFrame2  =  _DNumber_100,
			 enGPSSetDefaulttoModule2			=	( _DNumber_100 + _DNumber_10),	
			 enGPSSaveTheSettings2				= ( _DNumber_100 + _DNumber_20),
			 enGPSSwitchOffTheGPSDevice2	= ( _DNumber_100 + _DNumber_20),
			 enGPSSwitchOnTheGPSDevice2		= ( _DNumber_100 + _DNumber_30),	
			 enGPSInitProcessComplete			=	( _DNumber_100 + _DNumber_40),	
						
			}enGPSInitStatus;
		
		
		
		
			/*************** GPS DATE AND TIME STRUCTURE **********/
			typedef struct
			{
				uint8_t  ucHour	; // store the hour value
				uint8_t  ucMin 	; // store the Min  value 
				uint8_t  ucSec 	; // store the sec  value 
				uint16_t ucmSec	; // store the msec value  // not in used
				
				uint8_t  ucDay  ; // store the day  value 
				uint8_t  ucMonth; // store the Month value 
				uint16_t uiYear ; // store the Year value 
				
				char     ucDateNTimeSTR[_SYSTEM_DEFAULT_PARA_LEN_DATE_N_TIME]; // store the complete date and time string after the conversion
		
			}stGPSDateNTime;
			
 
			/*************** GPS Latitude STRUCTURE **************/
			typedef struct
			{
				
				int16_t  uiddmm   ; // store the ddmm value of LAT
				int16_t  uimmmm   ; // store the mmmm value of LAT
				char		 ucDir	  ;	// store the Direction of LAT 
				int16_t	 uiDegree ; // used to get the degree from uiddmm of LAT	 
				double	 dlDecimal; // used to get the decimal from ddmm and mmmm of LAT 
				double	 dlLatitudeVar; // store the final latitude value	 
				char     ucTempBuf[_DNumber_20]; // temporary buffer used during conversions
				char     ucLatitudeSTR[_SYSTEM_DEFAULT_PARA_LEN_LATITUDE_STR]; // store the complete Latitude string after the conversion
				
			}stGPSLatitude;		
			
			
			/*************** GPS Longitude STRUCTURE *************/
			typedef struct
			{
				
				int32_t  uidddmm ; // store the dddmm value of LON 
				int32_t  uimmmm  ; // store the mmmm  value of LON
				char		 ucDir 	 ; // store the Direction of LON
				int16_t	 uiDegree; // used to get the degree from dddmm of LON
				double	 dlDecimal; // used to get the decimal from dddmm and mmmm of LON
				double 	 dlLongitudeVar;	// store the final longitude 
				char     ucTempBuf[_DNumber_20]; // temporary buffer used during conversions
				char     ucLongitudeSTR[_SYSTEM_DEFAULT_PARA_LEN_LONGITUDE_STR]; 	// store the complete Longitude string after the conversion
				
			}stGPSLongitude;				
			
		
		
			/*************** GPS PARAMETER STRUCTURE **************/
		  typedef struct
			{
				uint8_t				 ucGPSPosition     ; 	 // store the GPS postion (fixed or Invalid) from GGA
				uint8_t				 ucNumberOfSatellites ;// store the number of stellite available from GGA
				float					 flSpeedOverGround ;   // store the speed over ground from RMC
				float					 flCourseOverGround;	 // store the course over ground from RMC
				float					 flMSLAltitude		 ;	 // store the Altitude from GGA
				float					 flPDOP						 ;   // store the PDOP available from GSA
				float					 flHDOP						 ;   // store the PDOP available from GSA 
				char 					 ucDecimal[2][20]	 ;   // temporary buffer used for getting the deimal value during conversions 
				stGPSDateNTime stVarGPSDateNTime ;	 // Time structure from GGA
				stGPSLatitude	 stVarGPSLatitude  ;   // LATI structure from GGA 
				stGPSLongitude stVarGPSLongitude ;   // LANG structure from GGA 
				
			}stGPSParameter;
 
			
			/*************** GPS COM PORT STRUCTURE **************/
			typedef struct
			{
			  uint8_t   ucGPSCurrStatus				; // this variable is used for the intialising the GPS  
				uint8_t		ucGPSInitCnt  				; // counter variable is used to perform different operation during the intialising the GPS  
				uint8_t   ucGPSOverFlowFlag			; // this variable indicate that the received frames are overflow.
				uint8_t		ucGPSStartTimerCnt		; // this variable is used to get the time difference between two bytes
				uint8_t 	ucGPSRXINTRFlag				; // this variable is used to indicate the reception interrupt
				uint8_t   ucGPSRxProcessFlag		; // this variable is used to indicate the completeion of a frame, and ready to process	 
				uint16_t 	uiGPSCOMRXCNT   			; // this variable is used to count and store data received at the GPS interrupt.
				uint8_t   ucGPSCOMARRAYSToreCNT	; // this variable is used to count the store frames
				uint8_t   ucGPSCOMARRAYProcessCNT;// this variable is used to count the process frames		
				uint8_t		ucGPSCOMRXBUFF [_GPS_COM_MAXBUFF]; // this array is used to store the received data in the ISR
				uint8_t   ucGPSCOMRXARRAY[_GPS_ARRAY_SIZE][_GPS_COM_MAXBUFF]; // this 2D array is used to store the multiple frames 
				
			}stGPSCOMPort;
 
 
			/*************** GPS COMPLETE STRUCTURE **************/	
			typedef struct
			{
			  stGPSParameter stVarGPSParameter; 
				stGPSCOMPort   stVarGPSCOMPort	;
			}stGPS_All;
		
		
 
 
/* ---------------------------------------------------------------------------
*                           FUNCTIONS DECLARATION
* ----------------------------------------------------------------------------
*/
			void FnGPSComPortConfig			(uint8_t ucCOMPORT);
			void FnGPSSendData				 	(char *str);
			void FnCheckGPSProccessINTR	(void);
			void FnGPSMessageProcess    (void);
			void FnCheckGPSProcessCNT  	(void);		
	    void FnGPSFramePasring 			(const char *ucFrameParse, uint8_t ucSelecPara );					
	 uint8_t FnGPSCOMACheck         (const char *ucGPSRX, uint8_t ucSelecPara );
   uint8_t FnGPSFrameCRCCeck			(const char *ucGPSMainFrame  );
	    void FnSeprateData				  (const char *ucProcessString );		
			
			
/*****END OF FILE****/ 

