/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "asm_func.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

 ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void PrivilegiosSVC (void)
{
    // Obtiene valor del registro de 32 bits del procesador llamado "control".
    // El registro guarda los siguientes estados:
    // bit 2: Uso de FPU en el contexto actual. Usado=1, no usado=0.
    // bit 1: Mapeo del stack pointer(sp). MSP=0, PSP=1.
    // bit 0: Modo de ejecucion en Thread. Privilegiado=0, No privilegiado=1.
    //        Recordar que este valor solo se usa en modo Thread. Las
    //        interrupciones siempre se ejecutan en modo Handler con total
    //        privilegio.
    uint32_t x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x |= 1;
    // bit 0 a modo No privilegiado.
    __set_CONTROL (x);

    // En este punto se estaria ejecutando en modo No privilegiado.
    // Lectura del registro "control" para confirmar.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x &= ~1u;
    // Se intenta volver a modo Privilegiado (bit 0, valor 0).
    __set_CONTROL (x);

    // Confirma que esta operacion es ignorada por estar ejecutandose en modo
    // Thread no privilegiado.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    // En este punto, ejecutando en modo Thread no privilegiado, la unica forma
    // de volver a modo privilegiado o de realizar cualquier cambio que requiera
    // modo privilegiado, es pidiendo ese servicio a un hipotetico sistema
    // opertivo de tiempo real.
    // Para esto se invoca por software a la interrupcion SVC (Supervisor Call)
    // utilizando la instruccion "svc".
    // No hay intrinsics para realizar esta tarea. Para utilizar la instruccion
    // es necesario implementar una funcion en assembler. Ver el archivo
    // asm_func.S.
    asm_svc ();

    // El sistema operativo (el handler de SVC) deberia haber devuelto el modo
    // de ejecucion de Thread a privilegiado (bit 0 en valor 0).
    x = __get_CONTROL ();

    // Fin del ejemplo de SVC
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
  PrivilegiosSVC ();

  #if (EJERCICIO_1 == 1 || EJERCICIO_2 == 1 || EJERCICIO_3 == 1 || EJERCICIO_4 == 1)
	//Variables ejercicios 1,2,3 y 4
	uint32_t vector32Zeros[] ={9,7,5};
	uint32_t vector32In[] ={3,4,0xAB123456};
	uint32_t vector32Out[]={0,0,0};
	//uint16_t vector16In[] ={0x0100,0x4000,0xAB12};
	uint16_t vector16In[] ={3,4,0xAB12};
	uint16_t vector16Out[]={0,0,0};
	uint32_t escalar32 = 4;
	uint16_t escalar16 = 4;
  #endif

  #if (EJERCICIO_0 == 1)
	const uint32_t Resultado = asm_sum (5, 3);
  #endif

  #if (EJERCICIO_1 == 1)
	//Ejercicio 1
	//Realizar una funci??n que inicialice un vector con ceros.
	//Ejercicio en C
	zeros (vector32Zeros, (sizeof(vector32Zeros)/sizeof(vector32Zeros[0])));
	//Ejercicio en Assembly
	vector32Zeros[0] =8;
	vector32Zeros[1] =16;
	vector32Zeros[2] =32;
	asm_zeros (vector32Zeros, (sizeof(vector32Zeros)/sizeof(vector32Zeros[0])));
  #endif

  #if (EJERCICIO_2 == 1)
	//Ejercicio 2
	//Realizar una funci??n que realice el producto de un vector y un escalar
	//(por ejemplo, podr??a servir para cambiar el nivel de amplitud de una se??al).
	//Ejercicio en C
	vector32Out[0] =0;
	vector32Out[1] =0;
	vector32Out[2] =0;
	productoEscalar32 (vector32In, vector32Out, (sizeof(vector32In)/sizeof(vector32In[0])), escalar32);
	//Ejercicio en Assembly
	vector32Out[0] =0;
	vector32Out[1] =0;
	vector32Out[2] =0;
	asm_productoEscalar32 (vector32In, vector32Out, (sizeof(vector32In)/sizeof(vector32In[0])), escalar32);
  #endif

  #if (EJERCICIO_3 == 1)
	//Ejercicio 3
	//Adapte la funci??n del ejercicio 2 para realizar operaciones sobre vectores de 16 bits
	//Ejercicio  en C
	vector16Out[0] =0;
	vector16Out[1] =0;
	vector16Out[2] =0;
	productoEscalar16 (vector16In, vector16Out, (sizeof(vector16In)/sizeof(vector16In[0])), escalar16);
	//Ejercicio en Assembly
	vector16Out[0] =0;
	vector16Out[1] =0;
	vector16Out[2] =0;
	asm_productoEscalar16 (vector16In, vector16Out, (sizeof(vector16In)/sizeof(vector16In[0])), escalar16);
  #endif

  #if (EJERCICIO_4 == 1)
	//Ejercicio 4
	//Adapte la funci??n del ejercicio 3 para saturar el resultado del producto a 12 bits
	//Ejercicio en C
	vector16Out[0] =0;
	vector16Out[1] =0;
	vector16Out[2] =0;
	productoEscalar12 (vector16In, vector16Out, (sizeof(vector16In)/sizeof(vector16In[0])), escalar16);
	//Ejercicio en Assembly
	vector16Out[0] =0;
	vector16Out[1] =0;
	vector16Out[2] =0;
	asm_productoEscalar12 (vector16In, vector16Out, (sizeof(vector16In)/sizeof(vector16In[0])), escalar16);
  #endif

  #if (EJERCICIO_5 == 1)
	//Ejercicio 5
	//Un filtro de ventana m??vil de 10 valores sobre un vector de muestras.
	//Ejercicio en C
	uint16_t vectorIn_5[] = {1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,100,100,100,0,0,0,0,5,5,5,5};
	uint16_t vectorOut_5[] = {0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0  , 0,0,0,0,0,0,0,0,0,0};
	uint16_t vectorOut_5_asm[] = {0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0  , 0,0,0,0,0,0,0,0,0,0};
	filtroVentana10(vectorIn_5, vectorOut_5, (sizeof(vectorIn_5)/sizeof(vectorIn_5[0])));
	//Ejercicio en Assembly
	asm_filtroVentana10(vectorIn_5, vectorOut_5_asm, (sizeof(vectorIn_5)/sizeof(vectorIn_5[0])));
  #endif

  #if (EJERCICIO_6 == 1)
	//Ejercicio 6
	//Recibe un vector de n??meros signados de 32 bits y los ???empaqueta??? en
	//otro vector de 16 bits. Adecua los valores de entrada a la nueva precisi??n.
	//Ejercicio en C
	int32_t vectorIn_6[] = {0x12345678,0x0080FFFF, 0x80000000, 0xFFFFFFFF};
	int16_t vectorOut_6[] = {0x0000,0x0000, 0x0000, 0x0000};
	pack32to16 (vectorIn_6, vectorOut_6, (sizeof(vectorIn_6)/sizeof(vectorIn_6[0])));
	//Ejercicio en Assembly
	vectorOut_6[0] = 0x0000;
	vectorOut_6[1] = 0x0000;
	vectorOut_6[2] = 0x0000;
	vectorOut_6[3] = 0x0000;
	asm_pack32to16 (vectorIn_6, vectorOut_6, (sizeof(vectorIn_6)/sizeof(vectorIn_6[0])));
  #endif

  #if (EJERCICIO_7 == 1)
	//Ejercicio 7
	//Recibe un vector de n??meros signados de 32 bits y devuelve la posici??n
	//del m??ximo del vector.
	//Ejercicio en C
	int32_t vectorIn_7[] = {4,2,1,5,6,2,3,2,3,2,1};
	int32_t ind_maximo_7;
	ind_maximo_7 = max(vectorIn_7, (sizeof(vectorIn_7)/sizeof(vectorIn_7[0])));
	//Ejercicio en Assembly
	ind_maximo_7 = 0;
	ind_maximo_7 = asm_max(vectorIn_7, (sizeof(vectorIn_7)/sizeof(vectorIn_7[0])));
  #endif

  #if (EJERCICIO_8 == 1)
	//Ejercicio 8
	//Recibe un vector de muestras signadas de 32 bits y lo decime
	//descartando una cada N muestras.
	//Ejercicio en C
	int32_t vectorIn_8[] = {1,0,0,2,0,0,3,0,0,4,0,0,5,0,0,6,0,0,7,0,0,8,0,0,9,0,0,10,0,0,11};
	int32_t vectorOut_8[] = {0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0  , 0,0,0,0,0,0,0,0,0,0};
	int32_t vectorOut_8_asm[] = {0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0  , 0,0,0,0,0,0,0,0,0,0};
	downsampleM (vectorIn_8, vectorOut_8, (sizeof(vectorIn_8)/sizeof(vectorIn_8[0])), 3);
	//Ejercicio en Assembly
	asm_downsampleM (vectorIn_8, vectorOut_8_asm, (sizeof(vectorIn_8)/sizeof(vectorIn_8[0])), 3);
  #endif

  #if (EJERCICIO_9 == 1)
	//Ejercicio 9
	//Recibe un vector de muestras no signadas de 16 bits e invierte su orden.
	//Ejercicio en C
	uint16_t vectorIn_9[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	invertir (vectorIn_9, (sizeof(vectorIn_9)/sizeof(vectorIn_9[0])));
	//Ejercicio en Assembly
	asm_invertir (vectorIn_9, (sizeof(vectorIn_9)/sizeof(vectorIn_9[0])));
  #endif

  #if (EJERCICIO_11 == 1)
	//Ejercicio 11
	//Calcula la correlaci??n entre dos vectores.

	int16_t vectorX[] = {1,2,3,4,5,6,7,8};
	int16_t vectorY[] = {1,2,3,4,1,2,3,4};

	uint32_t longitud = (sizeof(vectorX)/sizeof(vectorX[0]));

	//Ejercicio en C
	int16_t vectorCorr[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	corr (vectorX, vectorY, vectorCorr, longitud);
	//Ejercicio en Assembly
	int16_t vectorCorr_asm[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	asm_corr (vectorX, vectorY, vectorCorr_asm, longitud);
	//Se me complico su version con SIMD en Assembly
	/*****************************/
	/*****************************/

	//Nueva version, con preproceso, por ahora solo longitud PAR!!!!!
	int16_t vectorY_inv[] = {1,2,3,4,1,2,3,4};
	//Asumo que VectorX, VectorY tienen la misma longitud
	//Creo un nuevo vector de (3N - 2) con la se??al Y dada vuelta, centrada y completada con ceros
	int16_t vectorY_acon[3*longitud-2];
	zeros (vectorY_acon, 3*longitud-2);
	invertir (vectorY_inv, longitud);
	//Acondiciono
	for (uint32_t i=0; i<longitud;i++){
		vectorY_acon[i+longitud-1] = vectorY_inv[i];
	}

	//Ejercicio bis en C
	int16_t vectorCorr_bis[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	corr_bis (vectorX, vectorY_acon, vectorCorr_bis, longitud);

	//Ejercicio bis en Assembly
	int16_t vectorCorr_bis_asm[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	asm_corr_bis (vectorX, vectorY_acon, vectorCorr_bis_asm, longitud);

	//Ejercicio bis en Assembly con SIMD
	int16_t vectorCorr_bis_SIMD[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	asm_corr_SIMD (vectorX, vectorY_acon, vectorCorr_bis_SIMD, longitud);
  #endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

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
