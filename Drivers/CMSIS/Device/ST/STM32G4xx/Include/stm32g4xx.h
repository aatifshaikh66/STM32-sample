/**
  ******************************************************************************
  * @file    stm32g4xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32G4xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32G4xx device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e.
  *                code will be based on direct access to peripheral’s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32g4xx
  * @{
  */

#ifndef __STM32G4xx_H
#define __STM32G4xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */
	
	#define _DNumber_0				(uint8_t)0
	#define _DNumber_1				(uint8_t)1
	#define _DNumber_2				(uint8_t)2
	#define _DNumber_3				(uint8_t)3
	#define _DNumber_4				(uint8_t)4
	#define _DNumber_5				(uint8_t)5
	#define _DNumber_6				(uint8_t)6
	#define _DNumber_7				(uint8_t)7
	#define _DNumber_8				(uint8_t)8
	#define _DNumber_9				(uint8_t)9		

	#define _DNumber_10				(uint8_t)10
	#define _DNumber_11				(uint8_t)11
	#define _DNumber_12				(uint8_t)12
	#define _DNumber_13				(uint8_t)13
	#define _DNumber_14				(uint8_t)14
	#define _DNumber_15				(uint8_t)15
	#define _DNumber_16				(uint8_t)16
	#define _DNumber_17				(uint8_t)17
	#define _DNumber_18				(uint8_t)18
	#define _DNumber_19				(uint8_t)19		

	#define _DNumber_20				(uint8_t)20
	#define _DNumber_21				(uint8_t)21
	#define _DNumber_22				(uint8_t)22
	#define _DNumber_23				(uint8_t)23
	#define _DNumber_24				(uint8_t)24
	#define _DNumber_25				(uint8_t)25
	#define _DNumber_26				(uint8_t)26
	#define _DNumber_27				(uint8_t)27
	#define _DNumber_28				(uint8_t)28
	#define _DNumber_29				(uint8_t)29		

	#define _DNumber_30				(uint8_t)30
	#define _DNumber_31				(uint8_t)31
	#define _DNumber_32				(uint8_t)32
	#define _DNumber_33				(uint8_t)33
	#define _DNumber_34				(uint8_t)34
	#define _DNumber_35				(uint8_t)35
	#define _DNumber_36				(uint8_t)36
	#define _DNumber_37				(uint8_t)37
	#define _DNumber_38				(uint8_t)38
	#define _DNumber_39				(uint8_t)39		

	#define _DNumber_40				(uint8_t)40
	#define _DNumber_41				(uint8_t)41
	#define _DNumber_42				(uint8_t)42
	#define _DNumber_43				(uint8_t)43
	#define _DNumber_44				(uint8_t)44
	#define _DNumber_45				(uint8_t)45
	#define _DNumber_46				(uint8_t)46
	#define _DNumber_47				(uint8_t)47
	#define _DNumber_48				(uint8_t)48
	#define _DNumber_49				(uint8_t)49				

	#define _DNumber_50				(uint8_t)50	
	#define _DNumber_51				(uint8_t)51
	#define _DNumber_52				(uint8_t)52
	#define _DNumber_53				(uint8_t)53
	#define _DNumber_54				(uint8_t)54
	#define _DNumber_55				(uint8_t)55
	#define _DNumber_56				(uint8_t)56
	#define _DNumber_57				(uint8_t)57
	#define _DNumber_58				(uint8_t)58
	#define _DNumber_59				(uint8_t)59

	#define _DNumber_60				(uint8_t)60
	#define _DNumber_61				(uint8_t)61
	#define _DNumber_62				(uint8_t)62
	#define _DNumber_63				(uint8_t)63
	#define _DNumber_64				(uint8_t)64
	#define _DNumber_65				(uint8_t)65
	#define _DNumber_66				(uint8_t)66
	#define _DNumber_67				(uint8_t)67
	#define _DNumber_68				(uint8_t)68
	#define _DNumber_69				(uint8_t)69
	
	#define _DNumber_70				(uint8_t)70
	#define _DNumber_71				(uint8_t)71
	#define _DNumber_72				(uint8_t)72
	#define _DNumber_73				(uint8_t)73
	#define _DNumber_74				(uint8_t)74
	#define _DNumber_75				(uint8_t)75
	#define _DNumber_76				(uint8_t)76
	#define _DNumber_77				(uint8_t)77
	#define _DNumber_78				(uint8_t)78
	#define _DNumber_79				(uint8_t)79

	#define _DNumber_80				(uint8_t)80
	#define _DNumber_81				(uint8_t)81
	#define _DNumber_82				(uint8_t)82
	#define _DNumber_83				(uint8_t)83
	#define _DNumber_84				(uint8_t)84
	#define _DNumber_85				(uint8_t)85
	#define _DNumber_86				(uint8_t)86
	#define _DNumber_87				(uint8_t)87
	#define _DNumber_88				(uint8_t)88
	#define _DNumber_89				(uint8_t)89
	
	#define _DNumber_90				(uint8_t)90
	#define _DNumber_91				(uint8_t)91
	#define _DNumber_92				(uint8_t)92
	#define _DNumber_93				(uint8_t)93
	#define _DNumber_94				(uint8_t)94
	#define _DNumber_95				(uint8_t)95
	#define _DNumber_96				(uint8_t)96
	#define _DNumber_97				(uint8_t)97
	#define _DNumber_98				(uint8_t)98
	#define _DNumber_99				(uint8_t)99				
	
	#define _DNumber_100			(uint8_t)100	
	
	

/**
  * @brief STM32 Family
  */
#if !defined (STM32G4)
#define STM32G4
#endif /* STM32G4 */

/* Uncomment the line below according to the target STM32G4 device used in your
   application
  */

#if !defined (STM32G431xx) && !defined (STM32G441xx) && !defined (STM32G471xx) && \
    !defined (STM32G473xx) && !defined (STM32G474xx) && !defined (STM32G484xx) && \
    !defined (STM32GBK1CB) && !defined (STM32G491xx) && !defined (STM32G4A1xx)
  /* #define STM32G431xx */   /*!< STM32G431xx Devices */
  /* #define STM32G441xx */   /*!< STM32G441xx Devices */
  /* #define STM32G471xx */   /*!< STM32G471xx Devices */
  /* #define STM32G473xx */   /*!< STM32G473xx Devices */
  /* #define STM32G483xx */   /*!< STM32G483xx Devices */
  /* #define STM32G474xx */   /*!< STM32G474xx Devices */
  /* #define STM32G484xx */   /*!< STM32G484xx Devices */
  /* #define STM32G491xx */   /*!< STM32G491xx Devices */
  /* #define STM32G4A1xx */   /*!< STM32G4A1xx Devices */
  /* #define STM32GBK1CB */   /*!< STM32GBK1CB Devices */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number V1.2.1
  */
#define __STM32G4_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32G4_CMSIS_VERSION_SUB1   (0x02U) /*!< [23:16] sub1 version */
#define __STM32G4_CMSIS_VERSION_SUB2   (0x01U) /*!< [15:8]  sub2 version */
#define __STM32G4_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32G4_CMSIS_VERSION        ((__STM32G4_CMSIS_VERSION_MAIN << 24)\
                                       |(__STM32G4_CMSIS_VERSION_SUB1 << 16)\
                                       |(__STM32G4_CMSIS_VERSION_SUB2 << 8 )\
                                       |(__STM32G4_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32G431xx)
  #include "stm32g431xx.h"
#elif defined(STM32G441xx)
  #include "stm32g441xx.h"
#elif defined(STM32G471xx)
  #include "stm32g471xx.h"
#elif defined(STM32G473xx)
  #include "stm32g473xx.h"
#elif defined(STM32G483xx)
  #include "stm32g483xx.h"
#elif defined(STM32G474xx)
  #include "stm32g474xx.h"
#elif defined(STM32G484xx)
  #include "stm32g484xx.h"
#elif defined(STM32G491xx)
  #include "stm32g491xx.h"
#elif defined(STM32G4A1xx)
  #include "stm32g4a1xx.h"
#elif defined(STM32GBK1CB)
  #include "stm32gbk1cb.h"
#else
  #error "Please select first the target STM32G4xx device used in your application (in stm32g4xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32g4xx_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32G4xx_H */
/**
  * @}
  */

/**
  * @}
  */




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
