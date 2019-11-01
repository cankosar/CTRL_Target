/*
 * sysconfigs.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
#include "stm32f7xx_hal.h"
#include "../inc/sysconfigs.hpp"
#include "../inc/HW_config.hpp"
#include "../inc/HW_handlers.hpp"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void c_sysconfig::init(void){

  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();

  /* Initialize timers */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);

  //Enable backup SRAM
  enable_backup_sram();
}



  void c_sysconfig::MX_TIM2_Init(void)
  {

    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 1000;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 32;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;


    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

  }

  void c_sysconfig::MX_TIM3_Init(void)
  {

    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 10000;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 1600;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;


    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

  }

  void c_sysconfig::MX_GPIO_Init(void)
  {

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0|GPIO_PIN_1|USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

    //Display SPI RST Pin
    GPIO_InitStruct.Pin = DP_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DP_RST_PORT, &GPIO_InitStruct);

    //Display SPI CS Pin
    GPIO_InitStruct.Pin = DP_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DP_CS_PORT, &GPIO_InitStruct);

    //Display SPI DC Pin
    GPIO_InitStruct.Pin = DP_DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DP_DC_PORT, &GPIO_InitStruct);

    //LED Pins
    GPIO_InitStruct.Pin = LED_R_PIN | LED_G_PIN | LED_B_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LED_RGB_PORT, &GPIO_InitStruct);

    //PA Standby Pin
    GPIO_InitStruct.Pin = PA_Standby_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PA_Standby_Port, &GPIO_InitStruct);

     /*Configure GPIO pin : USER_Btn_Pin */
    GPIO_InitStruct.Pin = USER_Btn_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PG0 PG1 USB_PowerSwitchOn_Pin */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|USB_PowerSwitchOn_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /*Configure GPIO pins : LD3_Pin LD2_Pin */
    GPIO_InitStruct.Pin = LD3_Pin|LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    for(int i=0;i<4;i++){
  	  for(int j=0;j<2;j++){
  		  /*Configure GPIO pins : Encoder*/
  		  GPIO_InitStruct.Pin = enc_GPIO_Pin[i][j];
  		  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  		  GPIO_InitStruct.Pull = GPIO_NOPULL;
  		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  		  HAL_GPIO_Init(enc_GPIO_Port[i][j], &GPIO_InitStruct);
  	  }
    }

    for(int i=0;i<6;i++){
  	  /*Configure GPIO pins : Button*/
  	  GPIO_InitStruct.Pin = but_GPIO_Pin[i];
  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  	  HAL_GPIO_Init(but_GPIO_Port[i], &GPIO_InitStruct);
    }


    /*Configure GPIO pin : USB_OverCurrent_Pin */
    GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  }

  /* Backup SRAM initialization */
  void c_sysconfig::enable_backup_sram(void){
  	  //RTC clock enable
  	  __HAL_RCC_RTC_ENABLE();
  	  //Backup RAM enable
  	  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  	  //Backup access
  	  HAL_PWR_EnableBkUpAccess();
  	  //Backup low power mode enable
  	  HAL_PWREx_EnableBkUpReg();
  	  // additional code for Backup RAM enable
  }


  void c_sysconfig::SystemClock_Config(void)
  {

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

      /**Configure the main internal regulator output voltage
      */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

      /**Initializes the CPU, AHB and APB busses clocks
      */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

      /**Activate the Over-Drive mode
      */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

      /**Initializes the CPU, AHB and APB busses clocks
      */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_SAI1
                                |RCC_PERIPHCLK_CLK48;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 96;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
    PeriphClkInitStruct.PLLSAI.PLLSAIQ = 3;
    PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
    PeriphClkInitStruct.PLLSAIDivQ = 1;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI;
    PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
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


#ifdef __cplusplus
}
#endif
