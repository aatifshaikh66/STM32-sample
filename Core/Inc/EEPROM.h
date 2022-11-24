/**
  ******************************************************************************
  * @file    CAN/CODES/EEPROM.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    21-Oct-2018
  * @brief   Header for main.c module
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
	#include "stm32g4xx.h"


/* ----------------------------------------------------------------------------
*                           MACROS
* ----------------------------------------------------------------------------
*/


	/****************EEPROM Configuration data ********************/	
	#define _EEPROM_UINT_PAGE_SIZE		(uint32_t)0x000100
	#define _EEPROM_TOTAL_SIZE				(uint32_t)0x01F400
	#define _EEPROM_TOTAL_NO_OF_PAGES	(uint32_t)(EEPROM_TOTAL_SIZE/_EEPROM_UINT_PAGE_SIZE)

	#define _EEPROM_WREN 		  		    (uint8_t)0x06		/* write enble  		*/
	#define _EEPROM_WRDI 			        (uint8_t)0x04		/* write disable 		*/
	#define _EEPROM_RDSR     			    (uint8_t)0x05		/* read sts regi		*/
	#define _EEPROM_WRSR  				    (uint8_t)0x01		/* write sts regi   */
	#define _EEPROM_READ			        (uint8_t)0x03		/* Read Data Bytes  */
	#define _EEPROM_WRITE			        (uint8_t)0x02		/* Write Data Bytes */


	#define _EEPROM_CS_HIGH						LL_GPIO_SetOutputPin	(GPIOA, LL_GPIO_PIN_4);
	#define _EEPROM_CS_LOW						LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);

			
	#define _EEPROM_SIGNATURE_VALUE	  (uint32_t)0x76543210 /*do not changed this value*/


	/****************** configureation paramters Address ********************/
	#define _EEPROM_DEFINED_PAGE00_ADD	 (uint32_t)0x000000
	#define _EEPROM_DEFINED_PAGE01_ADD	 (uint32_t)0x000100


	#define	_EEPROM_UNIT_08_SHIFT													(uint8_t)0x01
	#define	_EEPROM_UNIT_16_SHIFT													(uint8_t)0x02
	#define	_EEPROM_UNIT_32_SHIFT													(uint8_t)0x04
	#define	_EEPROM_UNIT_64_SHIFT													(uint8_t)0x08
	#define _EEPROM_LOW_SECTION_SHIFT											(uint8_t)0x10
	#define _EEPROM_INTER_SECTION_SHIFT										(uint8_t)0x20
	#define _EEPROM_HIGH_SECTION_SHIFT										(uint8_t)0x40

	#define _EEPROM_SIGNATURE_VALUE_ADD										(uint32_t)(_EEPROM_DEFINED_PAGE01_ADD)


/* ---------------------------------------------------------------------------
*                           FUNCTIONS DECLARATION
* ----------------------------------------------------------------------------
*/


void 		 FnSPIXConfigInit			  (void);
uint8_t  FnSPIXRDWR						  (uint8_t);
void 		 FnSPIXWriteEnable		  (void);
void 		 FnSPIXWriteDisable		  (void);
uint8_t  FnSPIXReadStatusPage	  (void);
uint8_t  FnSPIXWriteStatusPage  (void);
void 		 FnSPIXEEPROMWriteBytes (uint8_t uiLength, uint32_t uiAddress, uint32_t uiData);
uint32_t FnSPIXEEPROMReadBytes  (uint8_t uiLength, uint32_t uiAddress);
float 	 FnSPIXEEPROMReadFloat  (uint32_t uiAddress);
void 		 FnSPIXEEPROMWriteFloat (uint32_t uiAddress, float flData);
double 	 FnSPIXEEPROMReadDouble (uint32_t uiAddress);
void 		 FnSPIXEEPROMWriteDouble(uint32_t uiAddress, double ddData);
void 		 FnSPIXEEPROMWriteUint32(uint32_t uiAddress, uint32_t uiData);
uint32_t FnSPIXEEPROMReadUint32 (uint32_t uiAddress);
void 		 FnSPIXEEPROMWriteUint16(uint32_t uiAddress, uint16_t uiData);
uint16_t FnSPIXEEPROMReadUint16 (uint32_t uiAddress); 
void 		 FnSPIXEEPROMWriteUint8 (uint32_t uiAddress, uint8_t ucData);
uint8_t  FnSPIXEEPROMReadUint8  (uint32_t uiAddress);
void 		 FnSPIXEEPROMWriteSignature						(void);
uint32_t FnSPIXEEPROMReadSignature						(void);

void 		 FnSPIXEEPROMLoadConfig								(void);


 /*****************END OF FILE*******************/

