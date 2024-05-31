/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */
Alcd_t lcd1={
		.Data_GPIO=GPIOA,
		.Data_GPIO_Start_Pin=0,
		.RS_GPIO=GPIOA,
		.RS_GPIO_Pin=GPIO_PIN_4,
		.EN_GPIO=GPIOA,
		.EN_GPIO_Pin=GPIO_PIN_5,
};

char stringaya[16];

Keypad_Matrix_t kp={
		.Rows = 4,
		.Columns = 4,
		.Row_Port = GPIOB,
		.Column_Port = GPIOB,
		.Row_Start_Pin = 12,
		.Column_Start_Pin = 6
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  Alcd_Init(& lcd1, 2, 0);


  Alcd_PutAt_n(&lcd1, 1, 0, "Youstina", 8);
  HAL_Delay(3000);

  Alcd_Clear(&lcd1);
  uint8_t HH=0;
  uint8_t MM=0;
  uint8_t SS=0;
  uint16_t mm=0;
  uint8_t length;

  /* USER CODE END 2 */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  Keypad_Matrix_init(&kp);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  Keypad_Matrix_refresh(&kp);
	  if(Keypad_Matrix_ReadKey(&kp, 1))
	  {
		  while(1)
		  {
			  Keypad_Matrix_refresh(&kp);
			  if(Keypad_Matrix_ReadKey(&kp, 2))
			  {
				  while(1)
				  {
					  Keypad_Matrix_refresh(&kp);
					  if(Keypad_Matrix_ReadKey(&kp, 1))
					  {
						  break;
					  }
					  if(Keypad_Matrix_ReadKey(&kp, 3))
					  {
					  	mm=0; SS=0; MM=0; HH=0;
					  	break;
					  }
				  }
			  }
			  if(Keypad_Matrix_ReadKey(&kp, 3))
			  {
				 mm=0; SS=0; MM=0; HH=0;
			  }
			  if(mm>=0 && mm<9)
			  {
				  mm++;
			  }
			  if(mm==9)
			  {
				  SS++;
				  mm=0;
			  }
			  if(SS==59)
			  {
				  MM++;
				  SS=0;
			  }
			  if(MM==59)
			  {
				  HH++;
				  MM=0;
			  }
			  if(HH==59 && MM==59 && SS==59 && mm==1000)
			  {
				  HH=0;
			  }
			  HAL_Delay(100);
			  sprintf(stringaya, "%02d:%02d:%02d.%d", HH, MM, SS, mm);
			  length =sprintf(stringaya, "%02d:%02d:%02d.%d", HH, MM, SS, mm);
			  Alcd_PutAt_n(&lcd1,0, 0, stringaya, length);

		  }
	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
