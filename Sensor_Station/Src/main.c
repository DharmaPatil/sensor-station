/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "fatfs.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include "OLED.h"
#include "interface.h"
#include "time_sync.h"
#include "sd_card.h"
#include "esp8266.h"
#include "sequencer.h"
#include "dht22.h"
#include "ms5611.h"
#include "tgs4161.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c2;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
DMA_HandleTypeDef hdma_tim2_ch3;
DMA_HandleTypeDef hdma_tim2_ch2_ch4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
volatile uint8_t ms_flag = 0;
FATFS fs;

/*
*/

//int fputc(int c, FILE *f) {	
//	HAL_UART_Transmit( &huart1, (uint8_t*)&c, 1, HAL_MAX_DELAY );
//	return c;
//}



#define NTP_PACKET_SIZE 48 
uint8_t buffer_ntp[NTP_PACKET_SIZE];
char buffer_tx[300];

char ozzy[] = "2E 2- 2G 2- 1G 1- 1a 1- 2a 2- 1c 1b 1c 1b 1c 1b 1G 1- 2G 1a 1- 2a 2-";


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C2_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_SYSTICK_Callback(void) {
	ms_flag = 1;
}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	char str[100];
	//Time_Set_Protection(1);
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_I2C2_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */


	/* //////// FLASH MEMORY ////////
	
	int i;
	char text_flash[256] = "Fragment of text in flash memory";
	uint32_t addr = 0x08000000 + 0x4000;
	uint8_t check[2];
	
	HAL_FLASH_Unlock();
	for ( i = 0; i < 64; i++ )
		HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, addr+i*4, *((uint32_t*)text_flash+i) );
	for ( i = 0; i < 20; i++ )
		check[i] = *((uint8_t*)addr + i );

	while (1);
	*/



	//////// DHT22 ////////

	OLED_Init();
	font = &font_medium;

	while (0) {
		float hum, temp;
		float pressure;
		float emf;
		int t1, t2, dt;
		
		
		
		t1 = HAL_GetTick();
		//DHT22_Conversion(1, &temp, &hum);  // 14 ms
		//MS5611_Conversion(&pressure); // 27 ms
		TGS4161_Conversion(&emf); // 20 ms
		t2 = HAL_GetTick();
		dt = t2 - t1;
		
		OLED_Clear();
		//sprintf(str, "Temp: %.1f~C", temp);
		//sprintf(str, "%.2f mmHg", pressure);
		sprintf(str, "%.3f mV", emf);
		OLED_Print( str, 20, 40 );
		//sprintf(str, "Humid: %.1f%%", hum);
		//OLED_Print( str, 20, 20 );
		sprintf(str, "Time: %d ms", dt);
		OLED_Print( str, 20, 0 );
		HAL_Delay(2000);
	}

	
	
	


   /* ////////// SEQUENCER ////////////////

	sprintf( str, "Sequencer" );
	OLED_Print( str, 10, 20 );
	Sequencer_Init();
	Sequencer_Start( ozzy );
	while (1) {
		HAL_Delay(100);
		Sequencer_Tick();
	}
	while (1) {};
	*/
	



	///////  WIFI  TIME SYNCRONIZATION  ////////////


	int tick1, tick2;
	
	OLED_Init();
	OLED_Clear();
	font = &font_medium;

	tick1 = HAL_GetTick();

	WiFi_Init();
	HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET );
	HAL_Delay(500);
	WiFi_Clear_Flags();

	sprintf( buffer_tx, "AT+CWMODE=1\r\n" );
	HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
	//WiFi_Wait_Response(100);
	sprintf( str, "Client mode - %d", WiFi_Wait_Response(100) );
	OLED_Print( str, 0, 40 );
		
	WiFi_Clear_Flags();
	#define AP_NAME "A.S.Tech Zyxel"
	#define AP_PASSWORD "areyougonnadie"	
	//#define AP_NAME "LG_v10"
	//#define AP_PASSWORD "12345678"
	sprintf( buffer_tx, "AT+CWJAP=\"%s\",\"%s\"\r\n", AP_NAME, AP_PASSWORD );
	HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
	uint8_t response = WiFi_Wait_Response(80);
	sprintf( str, "Connect to AP - %d", response );
	OLED_Print( str, 0, 24 );

	if ( response == 0 ) { // connected succesfully

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPMUX=1\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		sprintf( str, "Multi-conn - %d\r\n", WiFi_Wait_Response(100) );
		OLED_Print( str, 0, 8 );

		//HAL_Delay(1000);

		OLED_Clear();

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPSTART=0,\"UDP\",\"91.226.136.155\",123,123,0\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		sprintf( str, "UDP - %d\r\n", WiFi_Wait_Response(100) );
		OLED_Print( str, 0, 40 );

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPSEND=0,48\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		sprintf( str, "Prepare - %d\r\n", WiFi_Wait_Response(100) );
		OLED_Print( str, 0, 24 );
		
		memset( buffer_ntp, 0, sizeof(buffer_ntp) );
		buffer_ntp[0] = 0xE3;
		buffer_ntp[1] = 0;   
		buffer_ntp[2] = 6;
		buffer_ntp[3] = 0xEC; 
		buffer_ntp[12] = 49;
		buffer_ntp[13] = 0x4E;
		buffer_ntp[14] = 49;
		buffer_ntp[15] = 52;
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_ntp, sizeof(buffer_ntp), 100 );
		
		HAL_Delay(1000);

		uint32_t highWord = rx_buffer[(uint8_t)(rx_buffer_pointer-48+40)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+41)];
		uint32_t lowWord  = rx_buffer[(uint8_t)(rx_buffer_pointer-48+42)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+43)];
		uint32_t secsSince1900 = highWord << 16 | lowWord;
		uint32_t seventyYears = 2208988800UL;
		uint32_t epoch = secsSince1900 - seventyYears;
		
		OLED_Clear();
		
		tick2 = HAL_GetTick();
		sprintf( str, "dt: %d \r\n", tick2 - tick1 );
		OLED_Print( str, 0, 24 );
		
		sprintf( str, "Time: %d:%02d:%02d \r\n", (epoch % 86400) / 3600, (epoch % 3600) / 60, epoch % 60 );
		OLED_Print( str, 0, 8 );



		while(1) {
			HAL_Delay(200);
			LED( LED_RED, 1 );
			HAL_Delay(200);
			LED( LED_RED, 0 );	
		}
		
	} else {
		
		sprintf( str, "Reset WiFi" );
		OLED_Print( str, 0, 8 );
		
		HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_RESET );
		HAL_Delay(1000);
		HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET );
		HAL_Delay(1000);
		
		OLED_Clear();
		
		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CWMODE_CUR=2\r\n" ); 
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		sprintf( str, "Switch to AP - %d", WiFi_Wait_Response(100) );
		OLED_Print( str, 0, 40 );
		
		
		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CWSAP=\"ESP_AP\",\"password\",8,3\r\n" ); 
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		sprintf( str, "Create AP - %d", WiFi_Wait_Response(100) );
		OLED_Print( str, 0, 24 );
				
		while(1) {
			HAL_Delay(200);
			LED( LED_RED, 1 );
			HAL_Delay(200);
			LED( LED_RED, 0 );	
		}
		
	}		
	
	
	








/*

	SD_Init();
	printf("FAT_FS \r\n");
	
	printf("Mount: %d\r\n", f_mount(&fs, USER_Path, 1) );
	//printf("Mkfs: %d\r\n", f_mkfs(USER_Path, 1, 0x30000) );
	//printf("Mount: %d\r\n", f_mount(&fs, USER_Path, 0) );
	
	printf("Mount: %d\r\n", f_mount(&fs, USER_Path, 1) );
	
	FIL testFile;
  uint8_t testBuffer[16] = "Successful!!!\r\n";
  UINT testBytes;
	FILINFO fno;
	
	uint8_t filename[] = "log_0.txt";
	
	for ( int i = 0; i < 10; i++ ) {
		filename[4] = '0' + i;
		uint8_t fr = f_stat((const char*)filename, &fno);
		printf("Status(%d): %d\r\n", i, fr );
		if ( fr == FR_OK )
			continue;
			
		printf("Open: %d\r\n", f_open(&testFile, (const char*)filename, FA_WRITE | FA_CREATE_NEW ) );
		printf("Write: %d\r\n", f_write(&testFile, testBuffer, 16, &testBytes) );
		printf("Close: %d\r\n", f_close(&testFile) );	
		break;
	}
	
	printf("Mount: %d\r\n", f_mount(&fs, USER_Path, 0) );
	
	for (int i = 0; i < 6; i++ ) {
		HAL_Delay(100);
		LED( LED_RED, 1 );
		HAL_Delay(100);
		LED( LED_RED, 0 );		
	}
	LED( LED_RED, 1 );
	
	HAL_GPIO_WritePin( USB_ENABLE_GPIO_Port, USB_ENABLE_Pin, GPIO_PIN_SET );
	
	while (1) {};
	
	*/	

	HAL_Delay(100);
	
	Time_Start_Interrupts();

	//char str[100];
	/*
	sprintf(str," Sensor station");
	OLED_Send_String_HD(1,str);
	*/
	//Baro_Test();
	
	HAL_ADCEx_Calibration_Start(&hadc1);
	
	/*
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET);
	
	HAL_Delay(2000);
	
	char res_str[] = "AT+RST\r\n";
	HAL_UART_Transmit( &huart1, (uint8_t*)res_str, strlen(res_str), HAL_MAX_DELAY );
	HAL_UART_Receive( &huart1, (uint8_t*)str, 20, 500 );
	
	//sprintf(str,"AT\n\r");
	//HAL_Delay(500);
	str[20] = 0;
	OLED_Send_String_HD(2,str+8);
	*/
	//HAL_Delay(1000);
	//OLED_Clear();
	HAL_Delay(200);
	
	/*sprintf(str,"-456");

	font = &font_small;
	OLED_Print(str, 0, 0 );

	font = &font_medium;
	OLED_Print(str, 10, 10 );


	font = &font_large;
	OLED_Print(str, 0, 30 );*/


		OLED_Image(image_cloud,15,5);
		OLED_Image(image_status,10,48);

	while(1);

	while(1) {
		font = &font_times;
		sprintf(str,"+23.5");
		OLED_Print(str, 10, 10 );
		HAL_Delay(2000);
		OLED_Clear();
		
		
		HAL_Delay(2000);
		OLED_Clear();
	}

	while(1) {};


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {




		/*
		uint8_t time[3];
		Time_Get_Time(time);
		sprintf(str,"   %02d:%02d:%02d",time[0],time[1],time[2]);
		OLED_Send_String_HD(1,str);
		*/
		
		/*
		LED( LED_GREEN, 1 );
		LED( LED_RED, 1 );
		HAL_Delay(200);
		LED( LED_GREEN, 0 );
		LED( LED_RED, 0 );
		HAL_Delay(200);
		*/
		
		//Baro_Test();

		//static float emf = 0;	
		//emf = CO2_Sensor();

	
		while (!ms_flag) {};
		ms_flag = 0;
		//HAL_Delay(300);	
			
		{
			static uint16_t cnt = 0;
			static float emf_prevous = 0;
			static float emf = 0;	
			emf_prevous = emf;
			emf = CO2_Sensor();
			sprintf(str,"%6d %.4f",cnt,emf);
			//OLED_Send_String(7,str,1);
			cnt++;
		}
		
	
	
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef DateToUpdate;

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initialize RTC and set the Time and Date 
    */
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F2){
  sTime.Hours = 1;
  sTime.Minutes = 0;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 1;
  DateToUpdate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

    HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR1,0x32F2);
  }

}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 89;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 200;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim3);

}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 719;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 99;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim4);

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, WIFI_RESET_Pin|USB_ENABLE_Pin|OLED_SDA_Pin|OLED_SCL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BUTTON_1_Pin BUTTON_2_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin|BUTTON_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : WIFI_RESET_Pin USB_ENABLE_Pin OLED_SDA_Pin OLED_SCL_Pin */
  GPIO_InitStruct.Pin = WIFI_RESET_Pin|USB_ENABLE_Pin|OLED_SDA_Pin|OLED_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
