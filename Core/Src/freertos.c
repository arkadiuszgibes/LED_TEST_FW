/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "hw/pca9633.h"
#include "app/app.h"
#include "i2c.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId initialSequenceHandle;
osThreadId rainbowTaskHandHandle;
osSemaphoreId allowRainbowSemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void initialSequenceTask(void const * argument);
void rainbowLoopTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of allowRainbowSem */
  osSemaphoreDef(allowRainbowSem);
  allowRainbowSemHandle = osSemaphoreCreate(osSemaphore(allowRainbowSem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  // take semaphore, so rainbow task is blocked
  osSemaphoreWait(allowRainbowSemHandle, osWaitForever);

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of initialSequence */
  osThreadDef(initialSequence, initialSequenceTask, osPriorityNormal, 0, 256);
  initialSequenceHandle = osThreadCreate(osThread(initialSequence), NULL);

  /* definition and creation of rainbowTaskHand */
  osThreadDef(rainbowTaskHand, rainbowLoopTask, osPriorityIdle, 0, 256);
  rainbowTaskHandHandle = osThreadCreate(osThread(rainbowTaskHand), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_initialSequenceTask */
/**
  * @brief  Function implementing the initialSequence thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_initialSequenceTask */
void initialSequenceTask(void const * argument)
{
  /* USER CODE BEGIN initialSequenceTask */

	uint8_t seq_cnt = 0;

	// initialize spi device
	PCA9633_Init(&hi2c1);

  /* Infinite loop */
  for(;;)
  {
	  /**
	   * Execute sequence of events
	   */
	  if(seq_cnt == 0){
		  app_red_seq();
	  }else if(seq_cnt == 1){
		  app_green_seq();
	  }else if(seq_cnt == 2){
		  app_blue_seq();
	  }else if(seq_cnt == 3){
		  app_white_seq();
	  }else if(seq_cnt == 4){
		  app_mixed_red_wite_seq();
	  }else if(seq_cnt == 5){
		  app_lightness_seq();
	  }else{

		  /**
		   * No more start sequences so release semaphore
		   * to allow rainbow to shine
		   */
		  // release raibnow thread
		  osSemaphoreRelease(allowRainbowSemHandle);
		  // terminate task
		  osThreadTerminate(initialSequenceHandle);
		  break;
	  }
	  seq_cnt++;

    osDelay(10);
  }
  /* USER CODE END initialSequenceTask */
}

/* USER CODE BEGIN Header_rainbowLoopTask */
/**
* @brief Function implementing the rainbowTaskHand thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_rainbowLoopTask */
void rainbowLoopTask(void const * argument)
{
  /* USER CODE BEGIN rainbowLoopTask */
  /* Infinite loop */

	// wait for semaphore
	if (osSemaphoreWait(allowRainbowSemHandle, osWaitForever) == osOK) {

	  for(;;)
	  {
		  app_rainbow_gen();
	  }
	}
  /* USER CODE END rainbowLoopTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

