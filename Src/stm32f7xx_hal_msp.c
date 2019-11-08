/**
  ******************************************************************************
  * File Name          : stm32f7xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

extern DMA_HandleTypeDef hdma_spi5_tx;
extern DMA_HandleTypeDef hdma_spi5_rx;
extern DMA_HandleTypeDef hdma_adc1;

extern void _Error_Handler(char *, int);
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    /**ADC1 GPIO Configuration
    PA3     ------> ADC1_IN3
    */
    GPIO_InitStruct.Pin = EXP_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EXP_IN_GPIO_Port, &GPIO_InitStruct);

/* DMA controller clock enable */
   __HAL_RCC_DMA2_CLK_ENABLE();


    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream4;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }


    /* DMA interrupt init */
    /* DMA2_Stream4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    */
    HAL_GPIO_DeInit(EXP_IN_GPIO_Port, EXP_IN_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);

    /* ADC1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

	printf("SPI MSP Init\n");

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspInit 0 */

  /* USER CODE END SPI3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI3_CLK_ENABLE();
  
    /**SPI3 GPIO Configuration    
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO
    PC12     ------> SPI3_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI3_MspInit 1 */

  /* USER CODE END SPI3_MspInit 1 */
  }
  else if(hspi->Instance==SPI5)
  {
  /* USER CODE BEGIN SPI5_MspInit 0 */

  /* USER CODE END SPI5_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI5_CLK_ENABLE();
  
    /**SPI5 GPIO Configuration    
    PF7     ------> SPI5_SCK
    PF8     ------> SPI5_MISO
    PF9     ------> SPI5_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* SPI5 DMA Init */
    /* SPI5_TX Init */
    hdma_spi5_tx.Instance = DMA2_Stream4;
    hdma_spi5_tx.Init.Channel = DMA_CHANNEL_2;
    hdma_spi5_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi5_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi5_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi5_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi5_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi5_tx.Init.Mode = DMA_NORMAL;
    hdma_spi5_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi5_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi5_tx) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(hspi,hdmatx,hdma_spi5_tx);

    /* SPI5_RX Init */
    hdma_spi5_rx.Instance = DMA2_Stream3;
    hdma_spi5_rx.Init.Channel = DMA_CHANNEL_2;
    hdma_spi5_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi5_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi5_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi5_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi5_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi5_rx.Init.Mode = DMA_NORMAL;
    hdma_spi5_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi5_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi5_rx) != HAL_OK)
    {
//      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(hspi,hdmarx,hdma_spi5_rx);


	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	/* DMA2_Stream4_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

  }

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{

  if(hspi->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspDeInit 0 */

  /* USER CODE END SPI3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI3_CLK_DISABLE();
  
    /**SPI3 GPIO Configuration    
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO
    PC12     ------> SPI3_MOSI 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12);

  /* USER CODE BEGIN SPI3_MspDeInit 1 */

  /* USER CODE END SPI3_MspDeInit 1 */
  }
  else if(hspi->Instance==SPI5)
  {
	    __HAL_RCC_SPI5_CLK_DISABLE();

	    /**SPI5 GPIO Configuration
	    PF7     ------> SPI5_SCK
	    PF8     ------> SPI5_MISO
	    PF9     ------> SPI5_MOSI
	    */
	    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

	    /* SPI5 DMA DeInit */
	    HAL_DMA_DeInit(hspi->hdmatx);
	    HAL_DMA_DeInit(hspi->hdmarx);

  /* USER CODE BEGIN SPI5_MspDeInit 1 */

  /* USER CODE END SPI5_MspDeInit 1 */
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

	//Save NV Backup memory
	  if(htim_base->Instance==TIM5){

		  printf("Initing timer 5 MSP\n");
		  /* Peripheral clock enable */
		__HAL_RCC_TIM5_CLK_ENABLE();
		/* TIM2 interrupt Init */
		HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
	  /* USER CODE BEGIN TIM2_MspInit 1 */

	  /* USER CODE END TIM2_MspInit 1 */
	  }

  //Event manager
  if(htim_base->Instance==TIM2){

	  /* Peripheral clock enable */
	__HAL_RCC_TIM2_CLK_ENABLE();
	/* TIM2 interrupt Init */
	HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }

		//Tuner timer
	if(htim_base->Instance==TIM3){
		printf("Enabling tuner timer\n");

		  /* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* TIM1 interrupt Init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 4, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM1_MspInit 1 */

	/* USER CODE END TIM1_MspInit 1 */
	}

	//Expression pedal timer
	if(htim_base->Instance==TIM4){
		printf("Enabling expression timer\n");

		  /* Peripheral clock enable */
		__HAL_RCC_TIM4_CLK_ENABLE();
		/* TIM1 interrupt Init */
		HAL_NVIC_SetPriority(TIM4_IRQn, 3, 0);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
	/* USER CODE BEGIN TIM1_MspInit 1 */

	/* USER CODE END TIM1_MspInit 1 */
	}

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

	 if(htim_base->Instance==TIM5)
	  {
	  /* USER CODE BEGIN TIM2_MspDeInit 0 */

	  /* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM5_CLK_DISABLE();

		/* TIM2 interrupt DeInit */
		HAL_NVIC_DisableIRQ(TIM5_IRQn);
	  /* USER CODE BEGIN TIM2_MspDeInit 1 */

	  /* USER CODE END TIM2_MspDeInit 1 */
	  }

	  if(htim_base->Instance==TIM2)
	  {
	  /* USER CODE BEGIN TIM2_MspDeInit 0 */

	  /* USER CODE END TIM2_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_TIM2_CLK_DISABLE();

	    /* TIM2 interrupt DeInit */
	    HAL_NVIC_DisableIRQ(TIM2_IRQn);
	  /* USER CODE BEGIN TIM2_MspDeInit 1 */

	  /* USER CODE END TIM2_MspDeInit 1 */
	  }


	  if(htim_base->Instance==TIM3)
	  {
	  /* USER CODE BEGIN TIM3_MspDeInit 0 */

	  /* USER CODE END TIM3_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_TIM3_CLK_DISABLE();

	    /* TIM2 interrupt DeInit */
	    HAL_NVIC_DisableIRQ(TIM3_IRQn);
	  /* USER CODE BEGIN TIM3_MspDeInit 1 */

	  /* USER CODE END TIM3_MspDeInit 1 */
	  }

	  if(htim_base->Instance==TIM4)
	  {
	  /* USER CODE BEGIN TIM4_MspDeInit 0 */

	  /* USER CODE END TIM4_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_TIM4_CLK_DISABLE();

	    /* TIM2 interrupt DeInit */
	    HAL_NVIC_DisableIRQ(TIM4_IRQn);
	  /* USER CODE BEGIN TIM3_MspDeInit 1 */

	  /* USER CODE END TIM3_MspDeInit 1 */
	  }
}
