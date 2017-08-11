#include "stm32f0xx_hal.h"

RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
RTC_AlarmTypeDef sAlarm;
  
uint8_t showtime[50] = {0};
uint8_t showdate[50] = {0};

void SystemClock_Config(void);
static void MX_RTC_Init(void);
void RTC_TimeShow(void);
void RTC_DateShow(void);

void RTC_TimeShow(void)
{
  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  sprintf((char*)showtime,"%0.2d:%0.2d:%0.2d",sTime.Hours, sTime.Minutes, sTime.Seconds);
}

void RTC_DateShow(void)
{
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  sprintf((char*)showdate,"%d:%d:%d",sDate.Date, sDate.Month, sDate.Year);
}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_RTC_Init();

  while (1)
  {
    RTC_DateShow();
    RTC_TimeShow();
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_RTC_Init(void)
{
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  HAL_RTC_Init(&hrtc);

  sTime.Hours = 23;
  sTime.Minutes = 59;
  sTime.Seconds = 30;
  sTime.TimeFormat = RTC_HOURFORMAT12_PM;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  HAL_RTC_SetTime(&hrtc, &sTime, FORMAT_BIN);

  sDate.WeekDay = RTC_WEEKDAY_FRIDAY;
  sDate.Month = RTC_MONTH_JUNE;
  sDate.Date = 0x03;
  sDate.Year = 0x16;

  HAL_RTC_SetDate(&hrtc, &sDate, FORMAT_BIN);
}
 
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
