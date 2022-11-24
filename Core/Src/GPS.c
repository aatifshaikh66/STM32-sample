/********************************************************************************
  * @file    ../CODES/GPS.c 
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
			

/*****************************************************************************
 **@Function 		  	: 	FnGPSSendData
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void FnGPSSendData(char *str)
{
	
	for(uint8_t ucLoop= _DNumber_0 ; ucLoop < (strlen(str)) ; ucLoop ++)
	{
		/* write a character to the USART */
		   LL_USART_TransmitData8(_GPS_COM, (uint8_t)str[ucLoop]);
		/* Loop until transmit data register is empty */
		while (LL_USART_IsActiveFlag_TXE(_GPS_COM) == RESET){};
	}
		/* e.g. write a character to the USART */
		 LL_USART_TransmitData8(_GPS_COM, _DNumber_13);
		 /* Loop until transmit data register is empty */
		while (LL_USART_IsActiveFlag_TXE(_GPS_COM) == RESET){};
	
		/* write a character to the USART */
		LL_USART_TransmitData8(_GPS_COM, _DNumber_10);
	  /* Loop until transmit data register is empty */
		while (LL_USART_IsActiveFlag_TXE(_GPS_COM) == RESET){};
	
}


/*****************************************************************************
 **@Function 		  	: 	FnCheckDebuggProccessINTR
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnCheckGPSProccessINTR(void)
{
						static uint8_t ucGPSMessageCnt = RESET ;
				if( stVarGPS_All.stVarGPSCOMPort.ucGPSStartTimerCnt == SET )
					{
							ucGPSMessageCnt++ ;			
					if( stVarGPS_All.stVarGPSCOMPort.ucGPSRXINTRFlag  == SET )
						{
							ucGPSMessageCnt  = RESET ;
							stVarGPS_All.stVarGPSCOMPort.ucGPSRXINTRFlag = RESET ;
						}
						
					/******** If the Time Duration Between two bytes icreases 3ms
										set the process flag for further process on the frame *********/				
					if( ucGPSMessageCnt >= _DNumber_3 )	
						{
							ucGPSMessageCnt =	RESET ;
							stVarGPS_All.stVarGPSCOMPort.ucGPSStartTimerCnt = RESET ;
							stVarGPS_All.stVarGPSCOMPort.uiGPSCOMRXCNT 			= RESET	;
							stVarGPS_All.stVarGPSCOMPort.ucGPSRxProcessFlag	= SET 	;
						}
					}
}


/*****************************************************************************
 **@Function 		  	: 	FnGPSMessageProcess
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnGPSMessageProcess(void)
{

			/********** check if the GPS Process Flag is set or not ***********/
	if ( stVarGPS_All.stVarGPSCOMPort.ucGPSRxProcessFlag	== SET 	)
		 { 
				  /********** check if the recived GPS frame are being Processed or not ***********/
			if( stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT !=
				  stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT		)
			  {
						#if  _USE_DEBUG_GPS	
									printf("RX[%d]=%s\n\r",stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT,
												(char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
												[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]);
						#endif			 
						/********** check if the recived GPS frame is PRMC frame ***********/
								 if(strstr((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
									[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_RX_GPRMC ) ) 
									{		/********** CHECK THE CRC **********/
										if(FnGPSFrameCRCCeck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
											[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]) != _FALSE )
											{  /********** CHECK THE NUMBER OF COMA **********/
											 if(FnGPSCOMACheck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
												 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]
												 ,_GPS_SELEC_RMC) != _FALSE )
												 {  /********** PARSE THE RMC FRAME **********/
														FnGPSFramePasring((char  *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
														[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_SELEC_RMC);
												 }						
											}
											/********** INCREASE THE PROCESS COUNTER **********/
											FnCheckGPSProcessCNT();
									}
						/********** check if the recived GPS frame is GGA frame ***********/
						else if(strstr((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
									 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_RX_GPGGA) ) 
									 {	/********** CHECK THE CRC **********/
										if(FnGPSFrameCRCCeck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
											[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]) != _FALSE )
											{   /********** CHECK THE NUMBER OF COMA **********/
											 if(FnGPSCOMACheck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
												 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]
												 ,_GPS_SELEC_GGA) != _FALSE )
												 { /********** PARSE THE GGA FRAME **********/
													 FnGPSFramePasring((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
													[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_SELEC_GGA);
												 }																								
											}
											/********** INCREASE THE 
																	PROCESS COUNTER **********/
											FnCheckGPSProcessCNT();
								 	 }
						/********** check if the recived GPS frame is GSA frame ***********/		 
						else if(strstr((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
									 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_RX_GNGSA ) ) 
									{	  /********** CHECK THE CRC **********/
										if(FnGPSFrameCRCCeck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
											[stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]) != _FALSE )
											{  /********** CHECK THE NUMBER OF COMA **********/
											 if(FnGPSCOMACheck((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
												 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT]
												 ,_GPS_SELEC_GSA) != _FALSE )
												 {
													 /********** PARSE THE GSA FRAME **********/ 
													 FnGPSFramePasring((char *)stVarGPS_All.stVarGPSCOMPort.ucGPSCOMRXARRAY
													 [stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT],_GPS_SELEC_GSA);
												 }
											}
											/********** INCREASE THE 
																	PROCESS COUNTER **********/
											FnCheckGPSProcessCNT();
									}	
						/********** if the recived GPS frame unwanted, discard it ***********/			
						else
									{
										  /********** INCREASE THE PROCESS COUNTER **********/
											 FnCheckGPSProcessCNT();
									}					
			 }
			 else if(stVarGPS_All.stVarGPSCOMPort.ucGPSOverFlowFlag == SET  )
						 {
							 stVarGPS_All.stVarGPSCOMPort.ucGPSOverFlowFlag = RESET ;
								// NEED TO PERFROM AN OPERATION ON ALL THE FRAMES
						 }
		 }
}

/*****************************************************************************
 **@Function 		  	: 	FnCheckGPSProcessCNT
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void __INLINE FnCheckGPSProcessCNT (void)
{
	
		  stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT ++ ;
	if( stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT >= _GPS_ARRAY_SIZE )
		{ 
		  stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT = RESET ;					
		}		
	if( stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT ==
		  stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT		  )
		{
			stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYProcessCNT = RESET ;
			stVarGPS_All.stVarGPSCOMPort.ucGPSCOMARRAYSToreCNT   = RESET ;
			stVarGPS_All.stVarGPSCOMPort.ucGPSRxProcessFlag			 = RESET ;
		}
}


/*****************************************************************************
 **@Function 		  	: 	FnGPSFrameCRCCeck
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
uint8_t FnGPSFrameCRCCeck(const char *ucGPSRX)
{
	
    char     *ucTempVaiable, *ucProcessVaiable, ucGPSMainFrame[_GPS_COM_MAXBUFF] ;
		uint16_t  uiCheckSumValueString, uiCheckSumValuecalculate = RESET ; 	
		strcpy(ucGPSMainFrame, ucGPSRX);	
	
		/********** check if the $ char is present or not ***********/
		if((ucProcessVaiable  = strchr(ucGPSMainFrame,_GPS_RX_SOF)) != NULL)
			{  
				/********** Check if the * char is present or not ***********/
			if( ( ucTempVaiable = strchr(ucProcessVaiable,_GPS_RX_CRC_INDI)) != NULL)
				{ 
					  /********** Convert the last two bytes of the string for CRC ***********/
					  ucTempVaiable[_DNumber_0]= _DNumber_0;
					  uiCheckSumValueString = fnAtoBaseX((uint8_t *)(ucTempVaiable+_DNumber_1), _HEX_BASE_CONVO);
						
					  /********** Calculate the CRC of the frame after '$' till '*' ***********/
					      ucProcessVaiable++;
				 while(*ucProcessVaiable) uiCheckSumValuecalculate ^= *ucProcessVaiable++;
					
				 if(uiCheckSumValueString == uiCheckSumValuecalculate)	return _TRUE; 
				 else return _FALSE;
				}
			 else	  return _FALSE;
			}
		 else 	  return _FALSE;
}

/*****************************************************************************
 **@Function 		  	: 	FnGPSCOMACheck
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
uint8_t FnGPSCOMACheck (const char *ucGPSRX, uint8_t ucSelecPara )
{
    /********** Count the number of COMA IN A FRAME ***********/
		 uint16_t uiLoopCnt = RESET, uiCOMACnt = RESET ;
		for( ;  ((uiLoopCnt < strlen(ucGPSRX)) && (uiLoopCnt < _GPS_COM_MAXBUFF )); uiLoopCnt++ )
			   if (ucGPSRX[uiLoopCnt] == _GPS_RX_COMA_CHAR)
						 uiCOMACnt++;

		/********** check the Count matches or not ***********/		 
		 switch ( ucSelecPara )
		 {
			 case _GPS_SELEC_GGA: if (uiCOMACnt == _GPGGA_COMA_COUNT) return _TRUE; else return _FALSE;  
			 case _GPS_SELEC_GSA: if (uiCOMACnt == _GNGSA_COMA_COUNT) return _TRUE; else return _FALSE;
			 case _GPS_SELEC_RMC: if (uiCOMACnt == _GPRMC_COMA_COUNT) return _TRUE; else return _FALSE;
			 default :  return _FALSE; 
		 }
}


/*****************************************************************************
 **@Function 		  	: 	FnGPSFramePasring
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnGPSFramePasring (const char *ucFrameParse, uint8_t ucSelecPara )
{
	
	 char  *ucstrstrPointer, *ucstrtokPointer, *ucSTRING	;
	 char   ucProcessString[_DNumber_40]={NULL} ;
	
	switch (ucSelecPara)
	{
		/********* PARSE THE GGA FRAME ***********/
		case _GPS_SELEC_GGA:
		{
			/**example:
				 $GPGGA,105101.000,1909.55487,N,07251.05941,E,0,00,99.0,-50.52,M,0.0,M,,*74\r\n **/
				 //https://community.oracle.com/thread/3619431?start=0&tstart=0
				/** Locate the last '$' charachter to point 
						the Start of the frame  **/
						ucSTRING = strchr ( ucFrameParse				   , _GPS_RX_SOF		  ); 
			
				/** Locate the first _COMA_CHAR charachter and 
				then pass _COMA_CHAR charachter to seprate the strings **/
				ucstrstrPointer  = strstr	( ucSTRING + _DNumber_6  , _GPS_RX_COMA_STR );
				ucstrtokPointer	 = strtok	( ucstrstrPointer 		   , _GPS_RX_COMA_STR );
			  // string at this point 105101.000 
			
			 /********* SKIP THE FIRST PARAMETER ***********/
				ucstrtokPointer	 = strtok	( NULL, _GPS_RX_COMA_STR );
				// string at this point 1909.55487
			
			 /********* PARSE THE SECOND PARAMETER *********/
		   /********* PARSE THE LATITUDE DATA ************/
			 strcpy( ucProcessString, ucstrtokPointer );
			 FnSeprateData( ucProcessString );		
			 // string at this point 1->1909 2->55487
		
			 /********* GET THE LATITUDE DATA ddmm.mmmm ************/		
			        stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.uiddmm   =  
		   strtol(stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0],NULL,_DNumber_10); 
			        stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.uimmmm   = 
		   strtol(stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_1],NULL,_DNumber_10); ; 
			
			 /********* GET THE LATITUDE DATA Degree and Decimal ************/
			 stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.uiDegree = 
			 stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.uiddmm   / (uint8_t)0x64;
		
			 strcpy(stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucTempBuf ,
						 &stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_2]);
			 strcat(stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucTempBuf , _GPS_RX_DOT_STR); 
			 strcat(stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucTempBuf ,  
							stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_1]);
							stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlDecimal = 
			 strtod(stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucTempBuf ,NULL);
		
		   /********* Create a final string of Latitude ************/
			  stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlLatitudeVar = 
			  stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.uiDegree  + 
			 (stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlDecimal / (double)60 );
			 
			 sprintf(stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucLatitudeSTR,"%lf",
							 stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.dlLatitudeVar) ;
				#if _USE_DEBUG_GPS
						_DEBUG_ALL_ENABLE_DIABLE 
							printf("Latitude =%s\t\t",
							stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucLatitudeSTR);						
				#endif					
			 /********* PARSE THE THIRD PARAMETER *********/
			 /********* check the Latitude Direction N or S ************/			
			       ucstrtokPointer	 = strtok	(NULL, _GPS_RX_COMA_STR	  );
			 if(   strchr( ucstrtokPointer, _GPS_RX_LAT_NORTH ) != NULL )
				     stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucDir =  _GPS_RX_LAT_NORTH ;
			 else  stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucDir =  _GPS_RX_LAT_SOUTH ;
			 #if _USE_DEBUG_GPS
					 _DEBUG_ALL_ENABLE_DIABLE	
						 printf("Latitude direction =%c\n\r",
						 stVarGPS_All.stVarGPSParameter.stVarGPSLatitude.ucDir);	 
			 #endif
			 /********* PARSE THE FOURTH PARAMETER *********/
		   /********* PARSE THE LONGITUDE DATA ************/
			 ucstrtokPointer	 = strtok	( NULL,_GPS_RX_COMA_STR  );
			 strcpy(ucProcessString, ucstrtokPointer		)	;
			 FnSeprateData(ucProcessString );		
			
			 
			 /********* GET THE LONGITITUDE DATA dddmm.mmmm ************/	
			      stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.uidddmm   =
			 strtol(stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0],NULL,_DNumber_10);	
			      stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.uimmmm    = 	
			 strtol(stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_1],NULL,_DNumber_10);

			 /********* GET THE LONGITITUDE DATA Degree and Decimal ************/
			 stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.uiDegree = 
			 stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.uidddmm  / (uint8_t)0x64;

			 strcpy(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucTempBuf ,
  		 &stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_3]);
		
			 strcat(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucTempBuf , _GPS_RX_DOT_STR);
			 
			 strcat(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucTempBuf ,  
			 stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_1]);
			 
							stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlDecimal = 
			 strtod(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucTempBuf ,NULL);

		   /********* Create a final string of Longitude ************/
			 stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar = 
			 stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.uiDegree  + 
			(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlDecimal / (double)60 );
			 sprintf(stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucLongitudeSTR,"%lf",
							 stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.dlLongitudeVar );
				#if _USE_DEBUG_GPS	
						 _DEBUG_ALL_ENABLE_DIABLE
							printf("Longitude =%s\t",
							stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucLongitudeSTR);	
				#endif

			 /********* PARSE THE FIFTH PARAMETER *********/
			 /********* check the Longitude Direction E or W ************/			
			       ucstrtokPointer	 = strtok	(NULL, _GPS_RX_COMA_STR	  );
			 if(   strchr( ucstrtokPointer, _GPS_RX_LONG_EAST ) != NULL )
				     stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucDir =  _GPS_RX_LONG_EAST ;
			 else  stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucDir =  _GPS_RX_LONG_WEST ;
			 #if _USE_DEBUG_GPS
						printf("Longitude direction =%c\n\r",
						stVarGPS_All.stVarGPSParameter.stVarGPSLongitude.ucDir);
			 #endif
			 /********* PARSE THE SIXTH PARAMETER *********/
			 /********* check the GPS position indicator ************/				 
			 ucstrtokPointer	 = strtok	(NULL, _GPS_RX_COMA_STR	  ); 
			 stVarGPS_All.stVarGPSParameter.ucGPSPosition = strtol(ucstrtokPointer,NULL,_DNumber_10);
			 #if _USE_DEBUG_GPS
					 _DEBUG_ALL_ENABLE_DIABLE	
						printf("GPS Position =%d\n\r",
						stVarGPS_All.stVarGPSParameter.ucGPSPosition);
			 #endif
			 /********* PARSE THE SEVENTH PARAMETER *********/
			 /********* check the Number of GPS satellite ************/				 
			 ucstrtokPointer	 = strtok	(NULL, _GPS_RX_COMA_STR	  );
			 stVarGPS_All.stVarGPSParameter.ucNumberOfSatellites = strtol(ucstrtokPointer,NULL,_DNumber_10);
			 #if _USE_DEBUG_GPS
					 _DEBUG_ALL_ENABLE_DIABLE	
						printf("Number of sattelite =%d\t",
						stVarGPS_All.stVarGPSParameter.ucNumberOfSatellites);		
			 #endif	
			 /********* SKIP THE EIGHTH PARAMETER ***********/
			 ucstrtokPointer	 = strtok	(NULL, _GPS_RX_COMA_STR	  );	

			 /********* PARSE THE NINETH PARAMETER *********/
			 /********* check the Altitude value ************/
			 ucstrtokPointer	 = strtok	( NULL, _GPS_RX_COMA_STR	 );
			 stVarGPS_All.stVarGPSParameter.flMSLAltitude =  strtof(ucstrtokPointer,NULL);
			 #if _USE_DEBUG_GPS
					 _DEBUG_ALL_ENABLE_DIABLE	
						printf("altitude =%.2f\n\r",
						stVarGPS_All.stVarGPSParameter.flMSLAltitude);	
			 #endif
		}break;
		
		/********* PARSE THE RMC FRAME ***********/
		case _GPS_SELEC_RMC:
		{
			/**example:
			   $GPRMC,105101.000,V,1909.55487,N,07251.05941,E,12,22,061119,,,N*7E\r\n **/
			
			 /** Locate the last '$' charachter to point 
					 the Start of the frame  **/
			 ucSTRING = strchr(ucFrameParse,_GPS_RX_SOF); 
			 // string at this point $GPRMC,105101.000,V,1909.55487,N,07251.05941,E,12,22,061119,,,N*7E\r\n
			
			 /** Locate the first _COMA_CHAR charachter and 
					 then pass _COMA_CHAR charachter to seprate the strings **/
			 ucstrstrPointer  = strstr	(ucSTRING+_DNumber_6 ,_GPS_RX_COMA_STR);
			 ucstrtokPointer	= strtok	(ucstrstrPointer		 ,_GPS_RX_COMA_STR);
			 // string at this point 105101.000	
			
			 /********* PARSE THE FIRST PARAMETER *********/
		   /********* PARSE THE TIME hhmmss.sss ************/
			 strcpy(ucProcessString, ucstrtokPointer)	;
			 FnSeprateData(ucProcessString);
			 // string at this point 1->105101 2->000
			
			 /** store the time in the main array **/
			 strcpy(stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDateNTimeSTR,
						  stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0]);
			 #if _USE_DEBUG_GPS	
					// _DEBUG_ALL_ENABLE_DIABLE
					//	printf("date =%s\n\r",
					//	stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDateNTimeSTR);		
			 #endif
			  /** copy the first two charachter to extract the Hour**/
				ucProcessString [_DNumber_0] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_0];
				ucProcessString [_DNumber_1] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_1];			
			  ucProcessString [_DNumber_2] = NULL ;  
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucHour = strtol(ucProcessString,NULL,_DNumber_10); 
				/** copy the next two charachter to extract the minute**/	
				ucProcessString [_DNumber_0] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_2];
				ucProcessString [_DNumber_1] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_3];			
			  ucProcessString [_DNumber_2] = NULL ; 	
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucMin = strtol(ucProcessString,NULL,_DNumber_10);
				/** copy the next two charachter to extract the second**/
				ucProcessString [_DNumber_0] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_4];
				ucProcessString [_DNumber_1] = stVarGPS_All.stVarGPSParameter.ucDecimal[_DNumber_0][_DNumber_5];			
			  ucProcessString [_DNumber_2] = NULL ; 	
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucSec = strtol(ucProcessString,NULL,_DNumber_10);

			 /******** mSEC is not in used ***********/
			 /********* SKIP THE NEXT FIVE PARAMETER ***********/
			 for(uint8_t ucLoop  = _DNumber_0 ; ucLoop < _DNumber_5 ;ucLoop++)
				   ucstrtokPointer = strtok	( NULL, _GPS_RX_COMA_STR	 );
					 // string at this point 12,22,061119,,,N*7E\r\n
					 
			 /********* PARSE THE SECOND PARAMETER *********/
		   /********* check the Speed Over Ground ************/	
					/**check if two the next two paramters 
						 are blank or a valid data**/		
			 if(( ucstrtokPointer[_DNumber_2] == _GPS_RX_COMA_CHAR ) 
			 && ( ucstrtokPointer[_DNumber_3] == _GPS_RX_COMA_CHAR ))
				  {
						/**when the GPS device is not in the 
							 satellite range, there will be some 
							 blank space insted of these two paramter **/
						stVarGPS_All.stVarGPSParameter.flSpeedOverGround  = NULL ;
						stVarGPS_All.stVarGPSParameter.flCourseOverGround = NULL ;
						#if _USE_DEBUG_GPS	
								_DEBUG_ALL_ENABLE_DIABLE
								 printf("1.speed and cource = %.2f %.2f\n\r"			 ,
								 stVarGPS_All.stVarGPSParameter.flSpeedOverGround  ,
								 stVarGPS_All.stVarGPSParameter.flCourseOverGround );
						#endif
					}	
			 else
					{
						/**when the GPS device is in the range of 
							 the satellite range, we will get the actual parameter **/	
						ucstrtokPointer = strtok	( NULL, _GPS_RX_COMA_STR	 );	 
						stVarGPS_All.stVarGPSParameter.flSpeedOverGround  = strtof( ucstrtokPointer , NULL );
						ucstrtokPointer = strtok	( NULL, _GPS_RX_COMA_STR	 );	 
						stVarGPS_All.stVarGPSParameter.flCourseOverGround = strtof( ucstrtokPointer , NULL );
						#if _USE_DEBUG_GPS
								_DEBUG_ALL_ENABLE_DIABLE						
								 printf("2.speed and cource  =%.2f %.2f\n\r"				 ,
								 stVarGPS_All.stVarGPSParameter.flSpeedOverGround	 ,
								 stVarGPS_All.stVarGPSParameter.flCourseOverGround );
						#endif
					}		

			 /********* PARSE THE THIRD PARAMETER *********/
		   /********* PARSE THE DATE DDMMYY ************/					
				ucstrtokPointer = strtok	( NULL, _GPS_RX_COMA_STR	 );
				// string at this point 061119,,,N*7E\r\n
				
				/** copy the first two charachter to extract the day**/					
				ucProcessString [_DNumber_0] = ucstrtokPointer[_DNumber_0];
				ucProcessString [_DNumber_1] = ucstrtokPointer[_DNumber_1];			
			  ucProcessString [_DNumber_2] = NULL ; 
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDay   = 
				strtol(ucProcessString,NULL,_DNumber_10);
			  /** copy the next two charachter to extract the month**/	
				ucProcessString [_DNumber_0] = ucstrtokPointer[_DNumber_2];
				ucProcessString [_DNumber_1] = ucstrtokPointer[_DNumber_3];			
			  ucProcessString [_DNumber_2] = NULL ; 	
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucMonth = 
				strtol(ucProcessString,NULL,_DNumber_10);
			  /** copy the next two charachter to extract the years**/	
				ucProcessString [_DNumber_0] = ucstrtokPointer[_DNumber_4];
				ucProcessString [_DNumber_1] = ucstrtokPointer[_DNumber_5];			
			  ucProcessString [_DNumber_2] = NULL ; 	
			  stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.uiYear  = 
				strtol(ucProcessString,NULL,_DNumber_10);			
			
				/** build the combine frame of the time and date **/
				char ucDateBuff[50]; strcpy( ucDateBuff, stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDateNTimeSTR);
				sprintf( stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDateNTimeSTR,
				"%s %s", ucstrtokPointer , ucDateBuff  );
				#if _USE_DEBUG_GPS
						_DEBUG_ALL_ENABLE_DIABLE	
						 printf("Time N Date =%s\n\r",
						 stVarGPS_All.stVarGPSParameter.stVarGPSDateNTime.ucDateNTimeSTR );
				#endif
		}break;
		
		/********* PARSE THE GSA FRAME ***********/
		case _GPS_SELEC_GSA:
		{
			/**example:
				 $GNGSA,A,1,,,,,,,,,,,,,99.0,99.0,99.0*1E\r\n **/
			
			 /** As we required only last two parameter in the GSA frame **/
			 /** Locate the '*' charachter and replace it with NULL			 **/
			 ucstrstrPointer  = strchr  (ucFrameParse,_GPS_RX_CRC_INDI );   *ucstrstrPointer = NULL ;
			 //String at this point $GNGSA,A,1,,,,,,,,,,,,,99.0,99.0,99.0\0
				
			 /** Locate the last _COMA_CHAR charachter and replace it with NULL **/
			 /** To skip the last parameter **/
			 ucstrstrPointer  = strrchr (ucFrameParse,_GPS_RX_COMA_CHAR);   *ucstrstrPointer = NULL ; 
			 //String at this point $GNGSA,A,1,,,,,,,,,,,,,99.0,99.0\0
			 /** Locate the last _COMA_CHAR charachter to point the HDOP parameter **/
			 ucstrstrPointer  = strrchr (ucFrameParse,_GPS_RX_COMA_CHAR); 
			 stVarGPS_All.stVarGPSParameter.flHDOP = 
			 strtof(&ucstrstrPointer[_DNumber_1],NULL); *ucstrstrPointer = NULL ;
			 //String at this point $GNGSA,A,1,,,,,,,,,,,,,99.0\0
			 #if _USE_DEBUG_GPS	
					 _DEBUG_ALL_ENABLE_DIABLE
						printf("HDOP=%.2f\t", stVarGPS_All.stVarGPSParameter.flHDOP);	
			 #endif	
			
			 /** Locate the last _COMA_CHAR charachter to point the PDOP parameter **/
			 ucstrstrPointer  = strrchr (ucFrameParse,_GPS_RX_COMA_CHAR); 
			 stVarGPS_All.stVarGPSParameter.flPDOP = 
			 strtof(&ucstrstrPointer[_DNumber_1],NULL);*ucstrstrPointer = NULL ;
			 //String at this point $GNGSA,A,1,,,,,,,,,,,,\0
			 #if _USE_DEBUG_GPS		
					 _DEBUG_ALL_ENABLE_DIABLE
						printf("PDOP=%.2f\n\r", 
					  stVarGPS_All.stVarGPSParameter.flPDOP);			
			 #endif
	  }break;
  }
}


/*****************************************************************************
 **@Function 		  	: 	FnSeprateData
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/
void FnSeprateData(const char *ucProcessString)
{
	
			/********* Logic to seprate the parameter "xx.yy" ************/ 
			/** This function is used to seprate the data with decimal point **/	
				uint8_t ucDecimalCnt = RESET,ucDecimalCnt1 = RESET    ;
				for(uint8_t ucLoop   = _DNumber_0; ucLoop < strlen(ucProcessString) ; ucLoop++ )
				{   
					/**break the process when the   ucProcessString[ucLoop] == '\n' **/
					if( ucProcessString[ucLoop] == _GPS_RX_LF_CHAR)
						  break;
					
							/** store in the temporary first array 
									till the '.' charachter, then switch the array  **/
								ucDecimalCnt1++;
						if( ucProcessString[ucLoop] != _GPS_RX_DOT_CHAR ) 
							{	
								stVarGPS_All.stVarGPSParameter.ucDecimal 
								[ucDecimalCnt][ucDecimalCnt1 - _DNumber_1]  = ucProcessString[ucLoop] ;
							}
					else{	
							 	/**when the '.' charachter arives, store the NULL 
									 charachter at the end of frist array, and then
										switch the array. **/
								 stVarGPS_All.stVarGPSParameter.ucDecimal 
								[ucDecimalCnt][ucDecimalCnt1 - _DNumber_1]  = NULL ;
								 ucDecimalCnt = _DNumber_1 ; ucDecimalCnt1  = _DNumber_0 ; 
							}	
				}	 
				/*store the NULL charachter at the end of frist array */	
				stVarGPS_All.stVarGPSParameter.ucDecimal
				[ucDecimalCnt][ucDecimalCnt1] = NULL ;						
}

