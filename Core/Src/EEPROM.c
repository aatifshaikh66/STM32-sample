/******************************************************************************
**@file     :   EEPROM.c
* 
**@brief    :   This file provide functions to read write eeprom
******************************************************************************
*/

/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
 */

	#include "main.h"
	#include "stm32g4xx.h"	
	
/* ----------------------------------------------------------------------------
 *                           GLOBAL VARIABLES
 * ----------------------------------------------------------------------------
 */

	uint8_t Dummy ;

/******************************************************************************
 **@Function 			: FnSPI2RDWR
 **@Descriptions	: read write data to spix.
 **@parameters		: uiSendData: command or data to write
 **@return				:	data read from spix
 ****************************************************************************/
uint8_t FnSPIXRDWR( uint8_t ucSendData)   
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
	
	return ucRet;	
			
}
 /*****************************************************************************
 **@Function 			: FnSPI2WriteEnable
 **@Descriptions	: Send Write enable Inst to EEPROM.
 **@parameters		: None
 **@return				: None
*****************************************************************************/
void FnSPIXWriteEnable(void)
{	
		_EEPROM_CS_LOW
		 FnSPIXRDWR(_EEPROM_WREN);	
		_EEPROM_CS_HIGH
}
 /*****************************************************************************
 **@Function 			: FnSPI2WriteDisable
 **@Descriptions	: Send Write Disable Inst to EEPROM.
 **@parameters		: None
 **@return				: None
*****************************************************************************/
void FnSPIXWriteDisable(void)
{
	_EEPROM_CS_LOW
	  FnSPIXRDWR(_EEPROM_WRDI);	
	_EEPROM_CS_HIGH
}
 /*****************************************************************************
 **@Function 			: FnSPI2ReadStatusPage
 **@Descriptions	: Reads the Page status of the EEPROM.
 **@parameters		: None
 **@return				: Page status
*****************************************************************************/
uint8_t FnSPIXReadStatusPage(void)
{
	_EEPROM_CS_LOW
	 Dummy= FnSPIXRDWR(_EEPROM_RDSR);	
	 Dummy= FnSPIXRDWR((uint8_t)0xAA);		
	_EEPROM_CS_HIGH
	return Dummy			;	
}




/*****************************************************************************
 **@Function 			: FnSPI2ReadStatusPage
 **@Descriptions	: Reads the Page status of the EEPROM.
 **@parameters		: None
 **@return				: Page status
*****************************************************************************/
uint8_t FnSPIXWriteStatusPage(void)
{
 _EEPROM_CS_LOW	
	Dummy= FnSPIXRDWR(_EEPROM_WRSR);	
	Dummy= FnSPIXRDWR((uint8_t)0x00);	/*write a proper status value*/	
 _EEPROM_CS_HIGH
	return Dummy	;	
}



 /*****************************************************************************
 **@Function 			: fnEEPROM_Write
 **@Descriptions	: Write Data to Address Location
 **@parameters		: uiLength ->Number of bytes return into a memory
                    uiAddress->Address
                    uiData	 -> Data 
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteBytes(uint8_t uiLength, uint32_t uiAddress, uint32_t uiData)
{

		unConvo4 VarConvo;
		VarConvo.ui_32 = uiAddress ;	
 	 
		FnSPIXWriteEnable()	;    
		while(((FnSPIXReadStatusPage() >> SET) & SET ) == RESET){};				
			
	 _EEPROM_CS_LOW			
		Dummy = FnSPIXRDWR(_EEPROM_WRITE);
		Dummy = FnSPIXRDWR( VarConvo.uc_8[1]);
		Dummy = FnSPIXRDWR( VarConvo.uc_8[0]);

		VarConvo.ui_32= 0;		
		VarConvo.ui_32= uiData;	
		for(uint8_t  ucLoop=0; ucLoop < uiLength;ucLoop++)
					Dummy = FnSPIXRDWR(VarConvo.uc_8[ucLoop]);
			
	 _EEPROM_CS_HIGH

	 while((FnSPIXReadStatusPage() & SET) == SET){}; 			

}

/*****************************************************************************
 **@Function 			: FnSPI2EEPROMReadBytes
 **@Descriptions	: Read Data From Address Location
 **@parameters		: uiLength ->Number of bytes return into a memory
                    uiAddress->Address
 **@return				: None
*****************************************************************************/
uint32_t FnSPIXEEPROMReadBytes(uint8_t uiLength, uint32_t uiAddress)
{

		unConvo4 VarConvo;
		VarConvo.ui_32 = uiAddress ;		
		LL_SPI_ReceiveData8(SPI2);				

	 _EEPROM_CS_LOW		
		Dummy = FnSPIXRDWR(_EEPROM_READ);
		Dummy = FnSPIXRDWR( VarConvo.uc_8[1]);
		Dummy = FnSPIXRDWR( VarConvo.uc_8[0]);

		VarConvo.ui_32=RESET ;
		for(uint8_t uiLoop=0;uiLoop<uiLength;uiLoop++)
		 VarConvo.uc_8[uiLoop] = FnSPIXRDWR((uint8_t)0xAA);
		_EEPROM_CS_HIGH		
				
		
		_EEPROM_CS_LOW		
		 while((FnSPIXReadStatusPage() & SET) == SET){}; 			
		_EEPROM_CS_HIGH					
		return VarConvo.ui_32 ;
}


 /*****************************************************************************
 **@Function 			: FnSPI2EEPROMWriteFloat
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteFloat(uint32_t uiAddress, float flData)
{
			unConvo4 VarConvoData;
			VarConvoData.fl_32 = flData;
			for(int8_t iLoop=3,iLoop1= 0 ;iLoop>=0; iLoop--,iLoop1++ )
			FnSPIXEEPROMWriteBytes((uint8_t)0x01,uiAddress+iLoop1,VarConvoData.uc_8[iLoop]); 
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadFloat
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: float
*****************************************************************************/
float FnSPIXEEPROMReadFloat(uint32_t uiAddress)
{
			unConvo4 VarConvoData 			;
			VarConvoData.fl_32 = 0			;
			for(int8_t iLoop=3,iLoop1= 0 ;iLoop>=0; iLoop--,iLoop1++ )
			VarConvoData.uc_8[iLoop] = FnSPIXEEPROMReadBytes((uint8_t)0x01,uiAddress+iLoop1 );
			return VarConvoData.fl_32		;	
}



 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMWriteDouble
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteDouble(uint32_t uiAddress, double ddData)
{
		unConvo8 VarConvoData			 ;
		VarConvoData.dd_64 = ddData	 ;
		for(int8_t iLoop=7,iLoop1= 0 ;iLoop>-1; iLoop--,iLoop1++ )
		FnSPIXEEPROMWriteBytes((uint8_t)0x01,uiAddress+iLoop1,VarConvoData.uc_8[iLoop]); 
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadDouble
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: double
*****************************************************************************/
double FnSPIXEEPROMReadDouble(uint32_t uiAddress)
{
		unConvo8 VarConvoData 	 ;
		VarConvoData.dd_64 = 0	 ;
		for(int8_t iLoop=7,iLoop1= 0 ;iLoop>-1; iLoop--,iLoop1++ )
		VarConvoData.uc_8[iLoop] = FnSPIXEEPROMReadBytes((uint8_t)0x01,uiAddress+iLoop1 );
		return VarConvoData.dd_64;	
}



 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMWriteUint32
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteUint32(uint32_t uiAddress, uint32_t uiData)
{
		FnSPIXEEPROMWriteBytes((uint8_t)0x04,uiAddress,uiData); 
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadUint32
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: float
*****************************************************************************/
uint32_t FnSPIXEEPROMReadUint32(uint32_t uiAddress)
{
		return  FnSPIXEEPROMReadBytes((uint8_t)0x04,uiAddress );	
}


/*****************************************************************************
 **@Function 			: FnSPIXEEPROMWriteUint16
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteUint16(uint32_t uiAddress, uint16_t uiData)
{
		FnSPIXEEPROMWriteBytes((uint8_t)0x02,uiAddress,uiData); 
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadUint16
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: uint16_t
*****************************************************************************/
uint16_t FnSPIXEEPROMReadUint16(uint32_t uiAddress)
{
		return  FnSPIXEEPROMReadBytes((uint8_t)0x04,uiAddress );	
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMWriteUint8
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteUint8(uint32_t uiAddress, uint8_t ucData)
{
		FnSPIXEEPROMWriteBytes((uint8_t)0x01,uiAddress,ucData); 
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadUint8
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: uint8_t
*****************************************************************************/
uint8_t FnSPIXEEPROMReadUint8(uint32_t uiAddress)
{
		return  FnSPIXEEPROMReadBytes((uint8_t)0x01,uiAddress );	
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMWriteSignature
 **@Descriptions	: write Data From Address Location
 **@parameters		:	uiAddress->Address
 **@return				: None
*****************************************************************************/
void FnSPIXEEPROMWriteSignature(void)
{
		FnSPIXEEPROMWriteUint32(_EEPROM_SIGNATURE_VALUE_ADD,_EEPROM_SIGNATURE_VALUE);
}


 /*****************************************************************************
 **@Function 			: FnSPIXEEPROMReadSignature
 **@Descriptions	: write Data From Address Location
 **@parameters		:	None
 **@return				: None
*****************************************************************************/
uint32_t FnSPIXEEPROMReadSignature(void)
{
		return FnSPIXEEPROMReadUint32(_EEPROM_SIGNATURE_VALUE_ADD);
}


/*****************************************************************************
 **@Function 			: FnSPIXEEPROMLoadConfig
 **@Descriptions	: write Data From Address Location
 **@parameters		:	void
 **@return				: void
*****************************************************************************/
void FnSPIXEEPROMLoadConfig(void)
{
	
	if( FnSPIXEEPROMReadSignature() == _EEPROM_SIGNATURE_VALUE )
	{
		//#ifdef _USE_DEBUG_COM
						printf("EEPROM SIGNATURE MATCHED, LOADING ALL CONFIGURATION.\n\r");
		//#endif
	}
	else
	{
			//#ifdef _USE_DEBUG_COM
								printf("EEPROM SIGNATURE DOESN'T MATCHED!\n\rRESETTING ALL CONFIGURATIONS to DEFAULT!\n\r");
								printf("SIG=%x\n\r",FnSPIXEEPROMReadSignature());
			//#endif
			FnSPIXEEPROMWriteSignature();	
	}
}


 /*****************END OF FILE*******************/


